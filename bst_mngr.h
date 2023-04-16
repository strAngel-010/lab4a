//
// Created by vlad on 12.04.23.
//

#ifndef LAB4A_BST_MNGR_H
#define LAB4A_BST_MNGR_H

enum NUMS{
    RES_OK = 0,
    RES_EOF = -1,
    RES_ERR = 1,
    BUF_SIZE = 81
};

typedef struct Item{
    char* key;
    unsigned int info;
}Item;

typedef struct Node{
    char* key;
    struct Node* left;
    struct Node* right;
    struct Node* next;
    struct Node* parent;
    Item* info;
}Node;

int D_Add(Node** const ptr);
int D_Delete(Node** const ptr);
int D_Traverse(Node** const ptr);
int D_Find(Node** const ptr);
int D_Show(Node** const ptr);
int D_Find_Most_Different_Key(Node** const ptr);
int D_Input_From_File(Node** const ptr);
void erase(Node** const ptr);

#endif //LAB4A_BST_MNGR_H
