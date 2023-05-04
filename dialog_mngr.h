//
// Created by vlad on 12.04.23.
//

#ifndef LAB4A_DIALOG_MNGR_H
#define LAB4A_DIALOG_MNGR_H

#include <time.h>
#include "../aux_funcs/aux_funcs.h"
#include "structs.h"
#include "bst_mngr.h"

int D_Add(Node** const ptr);
int D_Delete(Node** const ptr);
int D_Traverse(Node** const ptr);
int D_Find(Node** const ptr);
int D_Show(Node** const ptr);
int D_Find_Most_Different_Key(Node** const ptr);
int D_Input_From_File(Node** const ptr);
int D_Timing(Node** const ptr);

#endif //LAB4A_BST_MNGR_H
