//
// Created by vlad on 12.04.23.
//

#include "dialog_mngr.h"

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

    int res = delete(ptr, key);
    free(key);
    return res;
}

int D_Traverse(Node** const ptr){
    char buf[BUF_SIZE];
    buf[0] = '\0';

    scanf("%*[^\n]");
    getchar();
    printf("Enter key:\n");
    if (!fgets(buf, BUF_SIZE-1, stdin)) {
        return RES_EOF;
    }
    buf[strlen(buf)-1] = '\0';

    print_traverse(*ptr, buf);
    printf("OK\n");
    return RES_OK;
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

    Node* res = find(*ptr, key);
    if (!res){
        printf("Elemen't with this key doesn't exist\n");
    } else {
        printf("key: %s; info: %u\n", res->key, res->info->info);
    }
    free(key);
    return RES_OK;
}

int D_Show(Node** const ptr){
    print_show(*ptr);
    printf("OK\n");
    return RES_OK;
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
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    key = strdup(buf);

    int arrlen = 0;
    Node** arr = find_most_different_key(*ptr, key, &arrlen);
    if (arrlen){
        for (int i = 0; i < arrlen; ++i) {
            printf("key: %s; info: %u\n", arr[i]->key, arr[i]->info->info);
        }
    }

    free(arr);
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

    int res = input_from_file(ptr, buf);
    if (res == RES_ERR){
        printf("Error in D_Input_From_File()\n");
    }
    return res;
}

int D_Timing(Node** const ptr){
    int res = timing(100, 501100, 1000, 50);
    if (res == RES_ERR){
        printf("Error in D_Timing()\n");
    }
    return res;
}
