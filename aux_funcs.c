//
// Created by vlad on 12.04.23.
//

#include "aux_funcs.h"

int getInt(unsigned int* n){
    int is_correct = 0;
    while (!is_correct){
        int res = scanf("%u", n);
        switch (res) {
            case -1:
                printf("\nExiting...\n");
                return RES_EOF;
            case 0:
                printf("Wrong input format\n");
                scanf("%*[^\n]");
                break;
            case 1:
                is_correct = 1;
                return RES_OK;
            default:
                return RES_ERR;
        }
    }
}

/*
char* myreadline(const char* msg){
    scanf("%*[^\n]");
    getchar();
    printf("%s", msg);
    char* str = (char*)malloc(sizeof(char));
    str[0] = '\0';
    char* buf = (char*)malloc(BUF_SIZE*sizeof(char));
    for (int i = 0; i < BUF_SIZE; i++){
        buf[i] = '\0';
    }
    int n = 0;
    int len = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0){
            free(str);
            str = NULL;
        } else if (n == 0){
            scanf("%*c");
        } else {
            len += strlen(buf);
            str = (char*)realloc(str, len+1);
            strcat(str, buf);
        }
    } while (n>0);
    free(buf);
    return str;
}
*/