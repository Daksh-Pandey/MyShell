#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char* argv[]){
    if (argc < 1){
        exit(EXIT_SUCCESS);
    }
    else if (argc == 1){
        printf("mkdir: requires an argument\n");
    }
    else if (argc >= 2){
        int i;
        if (strcmp(argv[1], "-v") == 0 || strstr(argv[1], "-m") != NULL){
            i = 2;
        }
        else{
            i = 1;
        }
        for (; i < argc; i++){
            if (strcmp(argv[1], "-v") == 0){
                if (mkdir(argv[i], S_IRWXU) == -1){
                    if (errno == EEXIST){
                        printf("mkdir: Directory %s already exists\n", argv[i]);
                    }
                    else{
                        printf("mkdir: Failed to create directory %s\n", argv[i]);
                    }
                }
                else{
                    printf("mkdir: created directory '%s'\n", argv[i]);
                }
            }
            else if (strstr(argv[1], "-m") != NULL){
                int j = 0;
                if (strcmp(argv[1], "-m=r") == 0){
                    if (mkdir(argv[i], S_IREAD) == -1){
                        j = 1;
                    }
                }
                else if (strcmp(argv[1], "-m=w") == 0){
                    if (mkdir(argv[i], S_IWRITE) == -1){
                        j = 1;
                    }
                }
                else if (strcmp(argv[1], "-m=x") == 0){
                    if (mkdir(argv[i], S_IEXEC) == -1){
                        j = 1;
                    }
                }
                else if (strcmp(argv[1], "-m=rwx") == 0 || strcmp(argv[1], "-m") == 0){
                    if (mkdir(argv[i], S_IRWXU) == -1){
                        j = 1;
                    }
                }
                else{
                    printf("mkdir: -m option not defined/implemented\n");
                }
                if (j == 1){
                    if (errno == EEXIST){
                        printf("mkdir: Directory %s already exists\n", argv[i]);
                    }
                    else{
                        printf("mkdir: Failed to create directory %s\n", argv[i]);
                    }
                }
            }
            else{
                if (mkdir(argv[i], S_IRWXU) == -1){
                    if (errno == EEXIST){
                        printf("mkdir: Directory %s already exists\n", argv[i]);
                    }
                    else{
                        printf("mkdir: Failed to create directory %s\n", argv[i]);
                    }
                }
            }
        }
    }

    return 0;
}