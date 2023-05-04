#ifndef LAB4A_BST_MNGR_H
#define LAB4A_BST_MNGR_H

#include <time.h>
#include "../aux_funcs/aux_funcs.h"
#include "structs.h"

#define add_timing_filename "add.txt"
#define find_timing_filename "find.txt"
#define delete_timing_filename "delete.txt"

int insert(Node** const ptr, char* const key, unsigned int info);
Node* find(const Node* const node, const char* key);
Node* find_next(const Node* node);
Node* find_traverse_predcessor(const Node* node);
const Node* find_min_node(const Node* root);
const Node* find_max_node(const Node* root);
int find_level(const Node* node);
const Node* find_common_ancestor(const Node* n1, const Node* n2);
Node** find_most_different_key(const Node* root, const char* const key, int* len);
int calc_distance(const Node* src, const Node* dest);
int delete(Node** const ptr, const char* key);
int timing(int min_elems, int max_elems, int step, int trees);
int add_rand_elems(int elems, Node** const root, char** const keys);
char* gen_rand_str(int len);
int input_from_file(Node** const ptr, char* filename);
void erase(Node** const ptr);

void print_traverse(const Node* root, const char* buf);
void print_show(const Node* node);

#endif
