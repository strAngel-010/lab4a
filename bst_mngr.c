//
// Created by vlad on 12.04.23.
//

#include "bst_mngr.h"
#include "aux_funcs.h"

int insert(Node** const ptr, const char** const key, unsigned int info);

int D_Add(Node** const ptr){
    const char* errmsgs[] = {"Ok", "Wrong input format", "Duplicate key"};
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

    //printf("key: %s; info: %u\n", key, info);


}

int insert(Node** const ptr, const char** const key, unsigned int info){
    Node* new_node = (Node*) malloc(sizeof (Node));
    if (!new_node){
        printf("Error in insert\n");
        return RES_ERR;
    }
    new_node->key = *key;
    new_node->left = NULL;
    new_node->right = NULL;

    Node* root = *ptr;
    if (!root){
        Item* new_item = (Item*) malloc(sizeof (Item));
        if (!new_item){
            printf("Error in insert\n");
            return RES_ERR;
        }
        new_node->parent = NULL;
        new_node->info = new_item;
        new_node->next = NULL;
        *ptr = new_node;
        return RES_OK;
    }
}
