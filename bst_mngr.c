//
// Created by vlad on 12.04.23.
//

#include "bst_mngr.h"
#include "aux_funcs.h"

int insert(Node** const ptr, const char* const key, unsigned int info);
Node* find(const Node* const node, const char* key, Node** const prev);
Node** find_most_different_key(const Node* root, const char* const key, int* len);
Node* find_min_node(const Node* root);
Node* find_max_node(const Node* root);
int calc_distance(const Node* src, const Node* dest);
int find_level(const Node* node);
Node* find_common_ancestor(const Node* n1, const Node* n2);
Node* find_prev(const Node* node);
int delete(Node** const ptr, Node* node);

void D_Print_Traverse(const Node* node);
void D_Recursive_Traverse(const Node* node, int tabs);

int D_Add(Node** const ptr){
    char* key = NULL;
    char buf[BUF_SIZE];
    buf[0] = '\0';
    unsigned int info = 0;

    scanf("%*[^\n]");
    getchar();
    printf("Enter key:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    key = strdup(buf);

    printf("Enter info:\n");
    if (getInt(&info) == RES_EOF){
        return RES_EOF;
    }

    int res = insert(ptr, key, info);
    if (res == RES_ERR){
        printf("Error in D_Add()\n");
        return RES_ERR;
    }
    printf("OK\n");
    return RES_OK;
}

int D_Delete(Node** const ptr){
    char* key = NULL;
    char buf[BUF_SIZE];
    buf[0] = '\0';

    scanf("%*[^\n]");
    getchar();
    printf("Enter key:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    key = strdup(buf);

    Node* node_to_del = find(*ptr, key, NULL);
    if (!node_to_del){
        printf("Element with this key doesn't exist\n");
        return RES_OK;
    }

    int res = delete(ptr, node_to_del);
    return res;
};

int D_Traverse(Node** const ptr){
    char* key = NULL;
    char buf[BUF_SIZE];
    buf[0] = '\0';

    scanf("%*[^\n]");
    getchar();
    printf("Enter key:\n");
    if (!fgets(buf, BUF_SIZE-1, stdin)) {
        return RES_EOF;
    }
    buf[strlen(buf)-1] = '\0';

    Node* starting_node = NULL;
    Node* prev = NULL;
    if (strlen(buf)){
        //buf[strlen(buf)-1] = '\0';
        key = strdup(buf);
        starting_node = find(*ptr, key, &prev);
    }

    if (starting_node){
        starting_node = starting_node->next;
    } else if (prev){
        if (strcmp(prev->key, key) < 0){
            starting_node = prev->next;
        } else {
            starting_node = prev;
        }
        if (starting_node){
            printf("Element with this key doesn't exist. Starting from element with key \"%s\"\n", starting_node->key);
        }
    } else {
        starting_node = *ptr;
    }

    free(key);
    D_Print_Traverse(starting_node);
    printf("OK\n");
    return RES_OK;
}

void D_Print_Traverse(const Node* node){
    if (!node){
        return;
    }

    node = find_min_node(node);
    while (node){
        printf("key: %s; info: %u\n", node->key, node->info->info);
        node = node->next;
    }
}

int D_Find(Node** const ptr){
    char* key = NULL;
    char buf[BUF_SIZE];
    buf[0] = '\0';

    scanf("%*[^\n]");
    getchar();
    printf("Enter key:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    key = strdup(buf);

    Node* res = find(*ptr, key, NULL);
    if (!res){
        printf("Elemen't with this key doesn't exist\n");
    } else {
        printf("key: %s; info: %u\n", res->key, res->info->info);
    }
    free(key);
    return RES_OK;
}

int D_Show(Node** const ptr){
    D_Recursive_Traverse(*ptr, 0);
    printf("OK\n");
}

void D_Recursive_Traverse(const Node* node, int tabs){
    if (!node){
        return;
    }
    for (int i = 0; i < tabs; ++i) {
        printf("\t");
    }
    printf("+---");
    printf("%s\n", node->key);
    D_Recursive_Traverse(node->left, tabs+1);
    D_Recursive_Traverse(node->right, tabs+1);
}

int D_Find_Most_Different_Key(Node** const ptr){
    if (!(*ptr)){
        printf("Tree is empty\n");
        return RES_OK;
    }

    char* key = NULL;
    char buf[BUF_SIZE];
    buf[0] = '\0';

    scanf("%*[^\n]");
    getchar();
    printf("Enter key:\n");
    while (!strlen(buf)){
        getchar();
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
    }
    buf[strlen(buf)-1] = '\0';
    key = strdup(buf);

    int arrlen = 0;
    Node** arr = find_most_different_key(ptr, key, &arrlen);
    if (arrlen){
        for (int i = 0; i < arrlen; ++i) {
            printf("key: %s; info: %u\n", arr[i]->key, arr[i]->info->info);
        }
    }

    free(key);
    return RES_OK;
}

int D_Input_From_File(Node** const ptr){
    char buf[BUF_SIZE];
    buf[0] = '\0';

    scanf("%*[^\n]");
    getchar();
    printf("Enter file name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
    }
    buf[strlen(buf)-1] = '\0';

    //printf("filename: %s\n", buf);

    FILE* f = fopen(buf, "r");
    if (!f){
        printf("This file doesn't exist\n");
        return RES_OK;
    }

    while (!feof(f)){
        fgets(buf, BUF_SIZE-1, f);
        buf[strlen(buf)-1] = '\0';
        char* key = strdup(buf);
        fgets(buf, BUF_SIZE-1, f);
        unsigned int info = atoi(buf);
        if (!info){
            printf("Wrong input format. Skipping line \"%s\"\n", buf);
        }

        int res = insert(ptr, key, info);
        if (res == RES_ERR){
            printf("Error in D_Input_From_File()\n");
            return RES_ERR;
        }
    }
    return RES_OK;
}

void erase(Node** const ptr){
    if (!(*ptr)){
        return;
    }
    Node* prev = find_min_node(*ptr);
    Node* cur = NULL;
    if (prev){
        cur = prev->next;
    }

    while (cur){
        free(prev->info->key);
        free(prev->info);
        free(prev);
        prev = cur;
        cur = cur->next;
    }
    free(prev->info->key);
    free(prev->info);
    free(prev);
    *ptr = NULL;
}

Node* find_min_node(const Node* root){
    while (root && root->left){
        root = root->left;
    }
    return root;
}

Node* find_max_node(const Node* root){
    while (root && root->right){
        root = root->right;
    }
    return root;
}

Node** find_most_different_key(const Node* const root, const char* const key, int* len){
    Node* prev = NULL;
    Node* res = find(root, key, prev);
    Node* min_node = find_min_node(root);
    Node* max_node = find_max_node(root);

    if (!res){
        printf("Element with this key doesn't exist. Finding most different keys from key \"%s\"\n", prev->key);
        res = prev;
    }

    if (min_node == max_node){
        printf("There's only one element in tree\n");
        return RES_OK;
    }

    int dist1 = calc_distance(min_node, res);
    int dist2 = calc_distance(max_node, res);

    Node** arr = NULL;
    if (dist1 == dist2){
        arr = (Node**) malloc(2*sizeof (Node*));
        if (!arr){
            printf("Error in find_most_different_key()\n");
            return NULL;
        }
        arr[0] = min_node;
        arr[1] = max_node;
        *len = 2;
    } else {
        arr = (Node**) malloc(sizeof (Node*));
        if (!arr){
            printf("Error in find_most_different_key()\n");
            return NULL;
        }

        if (dist1 > dist2){
            arr[0] = min_node;
        } else {
            arr[0] = max_node;
        }
        *len = 1;
    }
    return arr;
}

int insert(Node** const ptr, const char* const key, unsigned int info){
    Node* par = NULL;
    Node* cur = *ptr;
    int res = 0;
    while (cur){
        par = cur;
        res = strcmp(key, cur->key);
        if (res < 0){
            cur = cur->left;
        } else if (res > 0){
            cur = cur->right;
        } else {
            cur->info->info = info;
            free(key);
            return RES_OK;
        }
    }

    Item* new_item = (Item*) malloc(sizeof(Item));
    if (!new_item){
        printf("Error in insert()\n");
        return RES_ERR;
    }
    new_item->key = key;
    new_item->info = info;

    Node* new_node = (Node*) malloc(sizeof (Node));
    if (!new_node){
        printf("Error in insert()\n");
        return RES_ERR;
    }
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->info = new_item;

    if (!par){
        *ptr = new_node;
        new_node->parent = NULL;
        new_node->next = NULL;
        return RES_OK;
    }

    new_node->parent = par;
    if (res < 0){
        par->left = new_node;
        new_node->next = par;
        Node* prev = find_prev(new_node);
        if (prev){
            prev->next = new_node;
        }
    } else {
        par->right = new_node;
        new_node->next = par->next;
        par->next = new_node;
    }
    return RES_OK;
}

Node* find_prev(const Node* node){
    if (node->left){
        return find_max_node(node->left);
    }
    Node* par = node->parent;
    while (par && (par->left == node)){
        node = par;
        par = node->parent;
    }
    return par;
}

Node* find(const Node* const ptr, const char* key, Node** const prev){
    Node* pr = NULL;
    Node* cur = ptr;
    while (cur){
        int res = strcmp(key, cur->key);
        if (res == 0){
            if (prev){
                *prev = pr;
            }
            return cur;
        } else if (cur < 0){
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    if (prev){
        *prev = pr;
    }
    return NULL;
}

int delete(Node** const ptr, Node* const node){
    if (!node){
        printf("Node* is null\n");
        return RES_ERR;
    }

    Node* prev = find_prev(node);
    if (prev){
        prev->next = node->next;
    }

    Node* real_del = NULL;
    if (!(node->left) || !(node->right)){
        real_del = node;
    } else {
        real_del = node->next;
    }

    Node* under_tree = NULL;
    if (real_del->left){
        under_tree = real_del->left;
    } else {
        under_tree = real_del->right;
    }
    Node* par = real_del->parent;

    if (under_tree){
        under_tree->parent = par;
    }

    if (!par){
        *ptr = under_tree;
    } else if (par->left == real_del){
        par->left = under_tree;
    } else {
        par->right = under_tree;
    }

    if (real_del != node){
        free(node->key);
        node->key = real_del->key;
        free(node->info);
        node->info = real_del->info;
    }
    free(real_del);
    return RES_OK;
}

int calc_distance(const Node* src, const Node* dest){
    Node* common_ancestor = find_common_ancestor(src, dest);
    int ans = find_level(src)+ find_level(dest)- find_level(common_ancestor);
    return ans;
}

int find_level(const Node* node){
    int res = 0;
    while (node->parent){
        node = node->parent;
        ++res;
    }
    return res;
}

Node* find_common_ancestor(const Node* n1, const Node* n2){
    Node* res = find(n1, n2->key, NULL);
    if (res){
        return n1;
    }
    res = find(n2, n1->key, NULL);
    if (res){
        return n2;
    }

    while (n1){
        Node* prev = n1;
        n1 = n1->parent;
        if (strcmp(n1->key, n2->key) == 0){
            return n1;
        }

        if (n1->right && n1->left){
            if (n1->left == prev){
                res = find(n1->right, n2->key, NULL);
            } else {
                res = find(n1->left, n2->key, NULL);
            }
            if (res){
                return n1;
            }
        }
    }
}
