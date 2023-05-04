//
// Created by vlad on 12.04.23.
//

#ifndef LAB4A_STRUCTS_H
#define LAB4A_STRUCTS_H

typedef struct Item{
    char* key;
    unsigned int info;
}Item;

typedef struct Node{
    char* key;
    struct Node* left;
    struct Node* right;
    struct Node* thread;
    struct Node* parent;
    Item* info;
}Node;

#endif
