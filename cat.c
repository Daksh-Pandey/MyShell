#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    FILE* file;
    int line = 1;
    char c;

    if (argc < 1){
        exit(EXIT_SUCCESS);
    }
    else if (argc == 1 || (argc == 2 && (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-E") == 0))){
        printf("cat: requires an argument\n");
    }
    else if (argc >= 2){
        int i;
        if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-E") == 0){
            i = 2;
        }
        else{
            i = 1;
        }
        for (; i < argc; i++){
            file = fopen(argv[i], "r");
            if (!file){
                printf("cat: %s: No such file\n", argv[i]);
            }
            while (!feof(file)){
                c = fgetc(file);
                if (strcmp(argv[1], "-n") == 0 && c == '\n'){
                    printf("\n%d  ", line);
                    line++;
                }
                else if (strcmp(argv[1], "-E") == 0 && c == '\n'){
                    printf("$\n");
                }
                else{
                    printf("%c", c);
                }
            }
            fclose(file);
        }
    }
    else{
        printf("cat: Option not defined\n");
    }

    return 0;
}