#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char* argv[]){
    struct dirent* diren;
    DIR* dir;
    int i = 0;

    if (argc < 1){
        exit(EXIT_FAILURE);
    }
    if (argc == 1){
        dir = opendir(".");
        i = 1;
    }
    else if (argc == 2 && (strcmp(argv[1], "-A") == 0 || strcmp(argv[1], "-1") == 0)){
        dir = opendir(".");
    }
    else if (argc == 2){
        dir = opendir(argv[1]);
        i = 1;
    }
    else if (argc == 3 && (strcmp(argv[1], "-A") == 0 || strcmp(argv[1], "-1") == 0)){
        dir = opendir(argv[2]);
    }
    else{
        printf("ls: Option not defined/implemented\n");
        exit(EXIT_SUCCESS);
    }

    if (dir){
        int j = 0;
        while ((diren = readdir(dir)) != NULL){
            if (argc == 1 || (strcmp(argv[1], "-1") != 0 && strcmp(argv[1], "-A") != 0)){
                if (diren->d_name[0] == '.'){
                    continue;
                }
                else if (j == 7){
                    printf("%s\n", diren->d_name);
                    j = 0;
                }
                else{
                    printf("%s  ", diren->d_name);
                    j++;
                }
            }
            else if (strcmp(argv[1], "-1") == 0){
                if (diren->d_name[0] == '.'){
                    continue;
                }
                else{
                    printf("%s\n", diren->d_name);
                }
            }
            else if (strcmp(argv[1], "-A") == 0){
                if (j == 0){
                    printf("%s\t", diren->d_name);
                    j = 1;
                }
                else{
                    printf("%s\n", diren->d_name);
                    j = 0;
                }
            }
        }
        if (i == 1){
            printf("\n");
        }
    }
    else if (errno == ENOENT){
        printf("ls: Directory doesn't exist\n");
    }
    else{
        printf("ls: Unable to read directory\n");
    }

    return 0;
}