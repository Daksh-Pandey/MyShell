#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]){
    if (argc < 1){
        exit(EXIT_SUCCESS);
    }
    else if (argc == 1 || (argc == 2 && (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "-d") == 0))){
        printf("rm: requires an argument\n");
    }
    else if (argc >= 2){
        int i;
        if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "-d") == 0){
            i = 2;
        }
        else{
            i = 1;
        }
        for (; i < argc; i++){
            if (strcmp(argv[1], "-i") == 0){
                char remove;
                printf("rm: remove file '%s'? ", argv[i]);
                scanf("%c", &remove);
                if (remove == 'y'){
                    if (unlink(argv[i]) == -1){
                        if (errno == EACCES){
                            printf("rm: cannot remove '%s': Is write protected\n", argv[i]);
                        }
                        else if (errno == EISDIR){
                            printf("rm: cannot remove '%s': Is a directory\n", argv[i]);
                        }
                        else if (errno == ENOENT){
                            printf("rm: cannot remove '%s': No such file\n", argv[i]);
                        }
                        else{
                            printf("rm: cannot remove '%s'\n", argv[i]);
                        }
                    }
                    else{
                        continue;
                    }
                }
            }
            else if (strcmp(argv[1], "-d") == 0){
                if (rmdir(argv[i]) == -1){
                    if (errno == EACCES){
                            printf("rm: cannot remove '%s': Is write protected\n", argv[i]);
                        }
                        else if (errno == ENOTDIR){
                            printf("rm: cannot remove '%s': Is not a directory\n", argv[i]);
                        }
                        else if (errno == ENOTEMPTY){
                            printf("rm: cannot remove '%s': Is not empty\n", argv[i]);
                        }
                        else if (errno == ENOENT){
                            printf("rm: cannot remove '%s': No such directory\n", argv[i]);
                        }
                        else{
                            printf("rm: cannot remove '%s'\n", argv[i]);
                        }
                }
            }
            else{
                if (unlink(argv[i]) == -1){
                        if (errno == EACCES){
                            printf("rm: cannot remove '%s': Is write protected\n", argv[i]);
                        }
                        else if (errno == EISDIR){
                            printf("rm: cannot remove '%s': Is a directory\n", argv[i]);
                        }
                        else if (errno == ENOENT){
                            printf("rm: cannot remove '%s': No such file\n", argv[i]);
                        }
                        else{
                            printf("rm: cannot remove '%s'\n", argv[i]);
                        }
                    }
            }
        }
    }

    return 0;
}