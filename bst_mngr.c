//
// Created by vlad on 12.04.23.
//

#include "bst_mngr.h"
#include "aux_funcs.h"

int insert(Node** const ptr, const char** const key, unsigned int info);
Node* find(const Node* const node, const char** key);
void D_Print_Traverse(const Node* node);

int D_Add(Node** const ptr){
    char* key = NULL;
    char buf[BUF_SIZE];
    buf[0] = '\0';
    unsigned int info = 0;

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

    printf("Enter info:\n");
    if (getInt(&info) == RES_EOF){
        return RES_EOF;
    }

    int res = insert(ptr, &key, info);
    if (res == RES_ERR){
        printf("Error in D_Add()\n");
        return RES_ERR;
    }
    printf("OK\n");
    return RES_OK;
}

int D_Delete(Node** const ptr){};

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

    Node* starting_node = NULL;
    if (strlen(buf)){
        buf[strlen(buf)-1] = '\0';
        key = strdup(buf);
        starting_node = find(ptr, &key);
        free(key);

        if (!starting_node){
            printf("Element with this key doesn't exist\n");
        }
    }

    if (starting_node){
        starting_node = starting_node->next;
    } else {
        starting_node = *ptr;
        printf("Starting traverse from root\n");
    }

    D_Print_Traverse(starting_node);
    printf("OK\n");
    return RES_OK;
}

void D_Print_Traverse(const Node* node){
    if (!node){
        return;
    }

    while (node->left){
        node = node->left;
    }
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
        getchar();
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
    }
    buf[strlen(buf)-1] = '\0';
    key = strdup(buf);

    Node* res = find(ptr, &key);
    if (!res){
        printf("Elemen't with this key doesn't exist\n");
    } else {
        printf("key: %s; info: %u\n", res->key, res->info->info);
    }
    free(key);
    return RES_OK;
}

int insert(Node** const ptr, const char** const key, unsigned int info){
    Node* par = NULL;
    Node* cur = *ptr;
    int res = 0;
    while (cur){
        par = cur;
        res = strcmp(*key, cur->key);
        if (res < 0){
            cur = cur->left;
        } else if (res > 0){
            cur = cur->right;
        } else {
            cur->info->info = info;
            free(*key);
            return RES_OK;
        }
    }

    Item* new_item = (Item*) malloc(sizeof(Item));
    if (!new_item){
        printf("Error in insert()\n");
        return RES_ERR;
    }
    new_item->key = *key;
    new_item->info = info;

    Node* new_node = (Node*) malloc(sizeof (Node));
    if (!new_node){
        printf("Error in insert()\n");
        return RES_ERR;
    }
    new_node->key = *key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->info = new_item;

    if (!par){
        *ptr = new_node;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;
        return RES_OK;
    }

    new_node->parent = par;
    if (res < 0){
        par->left = new_node;
        new_node->next = par;
    } else {
        par->right = new_node;
        par->next = new_node;
        new_node->next = par->next;
    }
    return RES_OK;
}

Node* find(const Node* const ptr, const char** key){
    Node* cur = ptr;
    while (cur){
        int res = strcmp(*key, cur->key);
        if (res == 0){
            return cur;
        } else if (cur < 0){
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return NULL;
}
