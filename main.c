#include <stdio.h>
#include "aux_funcs.h"
#include "bst_mngr.h"

int init();
int dialog(const char* msgs[], int N);

int main() {
    if (init()){
        printf("Program finished with errors\n");
    } else {
        printf("Program finished successfully\n");
    }
    return 0;
}

int init(){
    const char* msgs[] = {"0. Quit", "1. Add", "2. Delete", "3. Traverse", "4. Find", "5. Show", "6. Find Most Different Key", "7. Input from file"};
    const int NMsgs = sizeof(msgs)/sizeof(msgs[0]);
    int (*fptr[])(Node** const) = {NULL, D_Add, D_Delete, D_Traverse, D_Find, D_Show, D_Find_Most_Different_Key, D_Input_From_File};
    Node* root = NULL;
    int res = 0;
    int rc = 0;

    while (rc = dialog(msgs, NMsgs)){
        res = fptr[rc](&root);
        if (res == RES_ERR || res == RES_EOF){
            break;
        }
    }

    erase(&root);
    return res == RES_ERR ? RES_ERR : RES_OK;
}

int dialog(const char* msgs[], const int N){
    int rc, res;
    for (int i = 0; i < N; ++i) {
        puts(msgs[i]);
    }
    printf("Make your choice:\n");
    res = getInt(&rc);
    if (res == RES_EOF){
        rc = 0;
    }
    return rc;
}
