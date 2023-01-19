#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

char* rmNewLine(char* str){
    str[strcspn(str, "\n")] = 0;
    return str;
}

int main(int argc, char* argv[]){
    time_t t = time(NULL);
    struct tm* tm;
    
    if (argc == 1){
        tm = localtime(&t);
        printf("%s IST\n", rmNewLine(asctime(tm)));
    }
    else if (argc == 2 && strcmp(argv[1], "-u") == 0){
        tm = gmtime(&t);
        printf("%s UTC\n", rmNewLine(asctime(tm)));
    }
    else if (strcmp(argv[1], "-r") == 0){
        if (argc == 2){
            printf("date: -r option requires an argument\n");
        }
        else if (argc == 3){
            char path[PATH_MAX];
            struct stat attr;
            char* status = realpath(argv[2], path);
            if (status){
                stat(path, &attr);
                if (stat){
                printf("%s IST\n", rmNewLine(ctime(&attr.st_mtime)));
                }
                else{
                    printf("date: Cannot show last modified time of file\n");
                }
            }
            else{
                printf("date: Failed to fetch file.\n");
            }
        }
        else{
            printf("date: Too many arguments\n");
        }
    }
    else{
        printf("date: Option not defined/implemented\n");
    }

    return 0;
}