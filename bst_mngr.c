//
// Created by vlad on 12.04.23.
//

#include "bst_mngr.h"

void print_traverse(const Node* root, const char* buf){
    Node* starting_node = NULL;
    char* key = NULL;
    if (strlen(buf)){
        key = strdup(buf);
        starting_node = find(root, key);
    }
    free(key);

    if (starting_node){
        if (starting_node->left){
            starting_node = starting_node->left;
        } else if (starting_node->right) {
            starting_node = starting_node->right;
        } else {
            starting_node = starting_node->thread;
        }
    } else {
        printf("Element with this key key doesn't exist. Starting traverse from root.\n");
        starting_node = root;
    }

    if (!starting_node){
        return;
    }

    while (starting_node){
        printf("key: %s; info: %u\n", starting_node->key, starting_node->info->info);
        if (starting_node->left){
            starting_node = starting_node->left;
        } else if (starting_node->right) {
            starting_node = starting_node->right;
        } else {
            starting_node = starting_node->thread;
        }
    }
}

void print_show(const Node* node){
    int* tabs = NULL;
    int arrlen = 0;

    while (node){
        if (arrlen){
            for (int i = 0; i < arrlen; ++i) {
                switch (tabs[i]) {
                    case 0:
                        printf("    ");
                        break;
                    case 1:
                        printf("│   ");
                        break;
                    case 2:
                        printf("└───");
                        break;
                    case 3:
                        printf("├───");
                        break;
                    default:
                        printf("Error in print_show()\n");
                        return;
                }
            }
        }
        printf("%s: %u\n", node->key, node->info->info);

        if (!(node->left) && !(node->right)){
            node = node->thread;
            int i = arrlen-1;
            while (arrlen != 0 && i >= 0 && tabs[i] != 1 && tabs[i] != 3){
                --i;
            }

            if (arrlen && i >= 0){
                arrlen = i+1;
                tabs = (int*) realloc(tabs, arrlen*sizeof(int));
                if (!tabs){
                    printf("Error in print_show()\n");
                    return;
                }
                tabs[arrlen-1] = 2;
            } else if (tabs) {
                free(tabs);
                tabs = NULL;
            }
            continue;
        }

        ++arrlen;
        tabs = (int*) realloc(tabs, arrlen*sizeof(int));
        if (!tabs){
            printf("Error in print_show()\n");
            return;
        }

        if (node->right && node->left){
            tabs[arrlen-1] = 3;
        } else {
            tabs[arrlen-1] = 2;
        }

        if (arrlen >= 2){
            if (tabs[arrlen-2] == 3){
                tabs[arrlen-2] = 1;
            } else if (tabs[arrlen-2] == 2){
                tabs[arrlen-2] = 0;
            }
        }

        if (node->left){
            node = node->left;
        } else {
            node = node->right;
        }
    }
}

int timing(int min_elems, int max_elems, int step, int trees){
    char** keys_for_funcs = NULL;
    int ind_for_funcs = 0;
    char* new_key = NULL;
    Node* root = NULL;
    int res = 0;
    Node* find_res = NULL;
    double avg_time[4] = {0, 0, 0}; //add, find, delete
    double cur_time[4] = {0, 0, 0}; //add, find, delete
    clock_t begin = 0, end = 0;
    FILE* add_file = fopen(add_timing_filename, "w");
    FILE* find_file = fopen(find_timing_filename, "w");
    FILE* delete_file = fopen(delete_timing_filename, "w");

    for (int i = min_elems; i <= max_elems; i += step) {
        for (int j = 0; j < 3; ++j) {
            cur_time[j] = 0;
        }
        keys_for_funcs = (char**) malloc(i*sizeof(char*));
        if (!keys_for_funcs){
            printf("Error in timing()\n");
            return RES_ERR;
        }
        for (int j = 0; j < i; ++j) {
            keys_for_funcs[j] = NULL;
        }

        srand(time(0));
        res = add_rand_elems(i, &root, keys_for_funcs);
        if (res == RES_ERR){
            printf("Error in timing()\n");
            return RES_ERR;
        }
        for (int j = 0; j < trees; ++j) {
            new_key = gen_rand_str(BUF_SIZE-1);
            begin = clock();
            res = insert(&root, new_key, 1);
            if (res == RES_ERR){
                printf("Error in timing()\n");
                return RES_ERR;
            }
            end = clock();
            cur_time[0] += (end-(double)begin)/CLOCKS_PER_SEC;

            while (keys_for_funcs[ind_for_funcs] == NULL){
                ind_for_funcs = rand()%i;
            }

            printf("cur_ind_for_funcs: %s\n", keys_for_funcs[ind_for_funcs]);

            begin = clock();
            find_res = find(root, keys_for_funcs[ind_for_funcs]);
            if (!find_res){
                printf("Error in timing()\n");
                return RES_ERR;
            }
            end = clock();
            cur_time[1] += (end-(double)begin)/CLOCKS_PER_SEC;

            begin = clock();
            res = delete(&root, keys_for_funcs[ind_for_funcs]);
            if (res == RES_ERR){
                printf("Error in timing()\n");
                return RES_ERR;
            }
            keys_for_funcs[ind_for_funcs] = NULL;
            end = clock();
            cur_time[2] += (end-(double)begin)/CLOCKS_PER_SEC;
        }
        erase(&root);
        free(keys_for_funcs);
        keys_for_funcs = NULL;

        for (int j = 0; j < 3; ++j) {
            avg_time[j] = cur_time[j]/trees;
        }
        printf("Avg time (%d elems):\n Add: %f mcs; Find: %f mcs; Delete: %f mcs\n",
               i, avg_time[0]*1000000, avg_time[1]*1000000, avg_time[2]*1000000);
        fprintf(add_file, "%d %f\n", i, avg_time[0]*1000000);
        fprintf(find_file, "%d %f\n", i, avg_time[1]*1000000);
        fprintf(delete_file, "%d %f\n", i, avg_time[2]*1000000);
    }

    fclose(add_file);
    fclose(find_file);
    fclose(delete_file);
    return RES_OK;
}

int add_rand_elems(int elems, Node** const root, char** const keys){
    char* new_key = NULL;
    int res;
    for (int i = 0; i < elems; ++i) {
        do {
            new_key = gen_rand_str(BUF_SIZE-1);
        } while (i != 0 && 0 == strcmp(new_key, keys[i-1]));

        res = insert(root, new_key, 1);
        if (res == RES_ERR){
            printf("Error in add_rand_elems()\n");
            return RES_ERR;
        }

        keys[i] = new_key;
    }
    return RES_OK;
}

char* gen_rand_str(int len){
    char* str = (char*)malloc((len+1)*sizeof(char));
    if (!str){
        printf("Error in gen_rand_str()\n");
        return NULL;
    }

    for (int i = 0; i < len; ++i) {
        str[i] = rand()%26+'A';
    }
    str[len] = '\0';
    return str;
}

void erase(Node** const ptr){
    if (!(*ptr)){
        return;
    }

    Node* cur = *ptr;
    Node* next = NULL;

    while (cur){
        free(cur->info->key);
        free(cur->info);
        next = cur->left;
        if (!next){
            next = cur->right;
        }
        if (!next){
            next = cur->thread;
        }
        free(cur);
        cur = next;
    }
    *ptr = NULL;
}

const Node* find_min_node(const Node* root){
    while (root && root->left){
        root = root->left;
    }
    return root;
}

const Node* find_max_node(const Node* root){
    while (root && root->right){
        root = root->right;
    }
    return root;
}

Node** find_most_different_key(const Node* const root, const char* const key, int* len){
    Node* res = find(root, key);
    Node* min_node = (Node*)find_min_node(root);
    Node* max_node = (Node*)find_max_node(root);

    if (!res){
        printf("Element with this key doesn't exist.\n");
        *len = 0;
        return NULL;
    }

    if (min_node == max_node){
        printf("There's only one element in tree\n");
        *len = 0;
        return NULL;
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

int insert(Node** const ptr, char* const key, unsigned int info){
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
        new_node->thread = NULL;
        return RES_OK;
    }

    new_node->parent = par;
    new_node->thread = par->thread;
    par->thread = NULL;
    if (res < 0){
        par->left = new_node;
        if (par->right){
            new_node->thread = par->right;
        }
    } else {
        par->right = new_node;
        if (par->left){
            Node* predc = find_traverse_predcessor(new_node);
            if (predc){
                if (predc->thread){ new_node->thread = predc->thread; }
                predc->thread = new_node;
            }
        }
    }
    return RES_OK;
}

Node* find_traverse_predcessor(const Node* node){
    node = node->parent;
    if (!node){
        return NULL;
    }

    node = node->left;
    while (node->left || node->right){
        if (node->right){ node = node->right; }
        else { node = node->left; }
    }
    return node;
}

Node* find(const Node* const ptr, const char* key){
    Node* cur = (Node*)ptr;
    while (cur){
        int res = strcmp(key, cur->key);
        if (res == 0){
            return cur;
        } else if (res < 0){
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return NULL;
}

Node* find_next(const Node* node){
    if (!node){
        printf("Error in find_next\n");
        return NULL;
    }

    if (node->right){
        return find_min_node(node->right);
    }

    Node* ptr = node->parent;
    while (ptr && (ptr->right == node)){
        node = ptr;
        ptr = node->parent;
    }
    return ptr;
}

int delete(Node** const ptr, const char* key){
	Node* node = find(*ptr, key);
    if (!node){
        printf("Element with this key doesn't exist\n");
        return RES_OK;
    }

    Node* real_del = NULL;
    if (!(node->left) || !(node->right)){
        real_del = node;
    } else {
        real_del = find_next(node);
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

    if (par && par->left && par->right && (par->right == real_del)){
        Node* prec = find_traverse_predcessor(real_del);
        if (real_del->thread){
            prec->thread = real_del->thread;
        } else if (real_del->left){
            prec->thread = real_del->left;
        } else {
            prec->thread = real_del->right;
        }
    } else if (par) {
        par->thread = real_del->thread;
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
    } else {
        free(real_del->key);
        free(real_del->info);
    }
    free(real_del);
    return RES_OK;
}

int calc_distance(const Node* src, const Node* dest){
    Node* common_ancestor = (Node*)find_common_ancestor(src, dest);
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

const Node* find_common_ancestor(const Node* n1, const Node* n2){
    Node* res = find(n1, n2->key);
    if (res){
        return n1;
    }
    res = find(n2, n1->key);
    if (res){
        return n2;
    }

    while (n1){
        Node* prev = (Node*)n1;
        n1 = n1->parent;
        if (strcmp(n1->key, n2->key) == 0){
            return n1;
        }

        if (n1->right && n1->left){
            if (n1->left == prev){
                res = find(n1->right, n2->key);
            } else {
                res = find(n1->left, n2->key);
            }
            if (res){
                return n1;
            }
        }
    }
}

int input_from_file(Node** const ptr, char* filename){
    FILE* f = fopen(filename, "r");
    if (!f){
        printf("This file doesn't exist\n");
        return RES_OK;
    }

    while (!feof(f)){
        fgets(filename, BUF_SIZE-1, f);
        filename[strlen(filename)-1] = '\0';
        char* key = strdup(filename);
        fgets(filename, BUF_SIZE-1, f);
        unsigned int info = atoi(filename);
        if (!info){
            printf("Wrong input format. Skipping line \"%s\"\n", filename);
        }

        int res = insert(ptr, key, info);
        if (res == RES_ERR){
            printf("Error in D_Input_From_File()\n");
            return RES_ERR;
        }
    }
    fclose(f);
    return RES_OK;
}