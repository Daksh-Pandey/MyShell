#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <errno.h>

#define IO_SIZE 128
#define STR_LIST_SIZE 64
#define DELIM " \n\t"

char* input(void){
    char* input; int i = 0; char c;
    input = (char*)malloc(IO_SIZE * sizeof(char));
    if (!input){
        perror("Memory allocation failed");
    }
    while(1){
        c = getchar();
        if (c == '\n'){
            input[i] = '\0';
            return input;
        }
        input[i] = c;
        i++;
    }
}

char** split_input(char* input){
    char** string_arr;
    string_arr = (char**)malloc(STR_LIST_SIZE * sizeof(char*));
    if (!string_arr){
        perror("Memory allocation failed");
    }
    int i = 0;
    char* next = strtok(input, DELIM);
    while(next != NULL){
        string_arr[i] = next;
        i++;
       next = strtok(NULL, DELIM);
    }
    for(int j = i; j < STR_LIST_SIZE; j++){
        string_arr[j] = NULL;
    }
    return string_arr;
}

void echo(char** cmd_arr){
    int i;
    if (cmd_arr[1] == NULL){
        printf("\n");
        return;
    }
    if (strcmp(cmd_arr[1], "--help") == 0){
        printf("--help\n");
    }
    else if (strcmp(cmd_arr[1], "-n") == 0){
        if (cmd_arr[2][0] == '"'){
            cmd_arr[2]++;
            i = 2;
            while(cmd_arr[i+1] != NULL){
                printf("%s ", cmd_arr[i]);
                i++;
            }
            int j = 0;
            while(cmd_arr[i][j] != '"'){
                printf("%c", cmd_arr[i][j]);
                j++;
            }
        }
        else{
            i = 2;
            while(cmd_arr[i] != NULL){
                printf("%s ", cmd_arr[i]);
                i++;
            }
        }
    }
    else{
        if (cmd_arr[1][0] == '"'){
            cmd_arr[1]++;
            i = 1;
            while(cmd_arr[i+1] != NULL){
                printf("%s ", cmd_arr[i]);
                i++;
            }
            int j = 0;
            while(cmd_arr[i][j] != '"'){
                printf("%c", cmd_arr[i][j]);
                j++;
            } printf("\n");
        }
        else{
            i = 1;
            while(cmd_arr[i] != NULL){
                    printf("%s ", cmd_arr[i]);
                    i++;
                } printf("\n");
        }
    }
}

void pwd(char** cmd_arr){
    char cwd[2*IO_SIZE];
    if (cmd_arr[1] == NULL || strcmp(cmd_arr[1], "-P") == 0){
        printf("%s\n", getcwd(cwd, sizeof(cwd)));
    }
    else if (strcmp(cmd_arr[1], "--help") == 0){
        printf("pwd: pwd [-LP]\n");
        printf("  Print the name of the current working directory.\n");
        printf("\n");
        printf("  Options:\n");
        printf("    -P	  print the physical directory, without any symbolic links\n");
        printf("\n");
        printf("  By default, `pwd' here behaves as if `-P' were specified.\n");
        printf("\n");
        printf("  Exit Status:\n");
        printf("  Returns 0 unless an invalid option is given or the current directory\n  cannot be read.\n");
    }
    else{
        fprintf(stderr, "Option invalid/not implemented.\n");
    }
}

void cd(char** cmd_arr){
    if (cmd_arr[1] == NULL || strcmp(cmd_arr[1], "~") == 0){
        if (chdir(getenv("HOME")) != 0){
            fprintf(stderr, "Failed to change directory to HOME\n");
        }
    }
    else if (strcmp(cmd_arr[1], "/") == 0){
        if (chdir(getenv("ROOT")) != 0){
            fprintf(stderr, "Failed to change directory to ROOT\n");
        }
    }
    else if (strcmp(cmd_arr[1], "-L") == 0 || strcmp(cmd_arr[1], "-P") == 0){
        if (chdir(cmd_arr[2]) != 0){
            fprintf(stderr, "Failed to change directory to %s\n", cmd_arr[1]);
        }
    }
    else{
        if (chdir(cmd_arr[1]) != 0){
            fprintf(stderr, "Failed to change directory to %s\n", cmd_arr[1]);
        }
    }
}

char* make_cmd(char** cmd_arr){
    char* ext_cmd = (char*)malloc(512*sizeof(char));
    strcpy(ext_cmd, cmd_arr[0]);
    for (int i = 1; cmd_arr[i] != NULL; i++){
        strcat(ext_cmd, " ");
        strcat(ext_cmd, cmd_arr[i]);
    }
    return ext_cmd;
}

int main(){
    char* ext_cmd;
    while(1){
        printf("MyShell> ");
        char* cmd = input();
        if (*cmd == '\0'){
            continue;
        }
        char** cmd_arr = split_input(cmd);
        if (strcmp(cmd_arr[0], "echo") == 0){
            echo(cmd_arr);
        }
        else if (strcmp(cmd_arr[0], "pwd") == 0){
            pwd(cmd_arr);
        }
        else if (strcmp(cmd_arr[0], "cd") == 0){
            cd(cmd_arr);
        }
        else if (strcmp(cmd_arr[0], "ls") == 0){
            cmd_arr[0] = "/home/dakshp/Desktop/OSAssignment1/ls";
            pid_t pid = fork();
            if (pid == 0){
                if (execv(cmd_arr[0], cmd_arr) == -1){
                    fprintf(stderr, "Failed to change files : %s\n", strerror(errno));
                }
            }
            else if (pid > 0){
                wait(NULL);
            }
            else{
                fprintf(stderr, "Child process creation failed.\n");
            }
        }
        else if (strcmp(cmd_arr[0], "ls&t") == 0){
            cmd_arr[0] = "/home/dakshp/Desktop/OSAssignment1/ls";
            ext_cmd = make_cmd(cmd_arr);
            pthread_t new_thread;
            if (pthread_create(&new_thread, NULL, (void*)system, (void*)ext_cmd) != 0){
                printf("Failed to create new thread.\n");
            }
            if (pthread_join(new_thread, NULL) != 0){
                printf("New thread termination failed.\n");
            }
            free(ext_cmd);
        }
        else if (strcmp(cmd_arr[0], "cat") == 0){
            cmd_arr[0] = "/home/dakshp/Desktop/OSAssignment1/cat";
            pid_t pid = fork();
            if (pid == 0){
                if (execv(cmd_arr[0], cmd_arr) == -1){
                    fprintf(stderr, "Failed to change files : %s\n", strerror(errno));
                }
            }
            else if (pid > 0){
                wait(NULL);
            }
            else{
                fprintf(stderr, "Child process creation failed.\n");
            }
        }
        else if (strcmp(cmd_arr[0], "cat&t") == 0){
            cmd_arr[0] = "/home/dakshp/Desktop/OSAssignment1/cat";
            ext_cmd = make_cmd(cmd_arr);
            pthread_t new_thread;
            if (pthread_create(&new_thread, NULL, (void*)system, (void*)ext_cmd) != 0){
                printf("Failed to create new thread.\n");
            }
            if (pthread_join(new_thread, NULL) != 0){
                printf("New thread termination failed.\n");
            }
            free(ext_cmd);
        }
        else if (strcmp(cmd_arr[0], "date") == 0){
            cmd_arr[0] = "/home/dakshp/Desktop/OSAssignment1/date";
            pid_t pid = fork();
            if (pid == 0){
                if (execv(cmd_arr[0], cmd_arr) == -1){
                    fprintf(stderr, "Failed to change files : %s\n", strerror(errno));
                }
            }
            else if (pid > 0){
                wait(NULL);
            }
            else{
                fprintf(stderr, "Child process creation failed.\n");
            }
        }
        else if (strcmp(cmd_arr[0], "date&t") == 0){
            cmd_arr[0] = "/home/dakshp/Desktop/OSAssignment1/date";
            ext_cmd = make_cmd(cmd_arr);
            pthread_t new_thread;
            if (pthread_create(&new_thread, NULL, (void*)system, (void*)ext_cmd) != 0){
                printf("Failed to create new thread.\n");
            }
            if (pthread_join(new_thread, NULL) != 0){
                printf("New thread termination failed.\n");
            }
            free(ext_cmd);
        }
        else if (strcmp(cmd_arr[0], "rm") == 0){
            cmd_arr[0] = "/home/dakshp/Desktop/OSAssignment1/rm";
            pid_t pid = fork();
            if (pid == 0){
                if (execv(cmd_arr[0], cmd_arr) == -1){
                    fprintf(stderr, "Failed to change files : %s\n", strerror(errno));
                }
            }
            else if (pid > 0){
                wait(NULL);
            }
            else{
                fprintf(stderr, "Child process creation failed.\n");
            }
        }
        else if (strcmp(cmd_arr[0], "rm&t") == 0){
            cmd_arr[0] = "/home/dakshp/Desktop/OSAssignment1/rm";
            ext_cmd = make_cmd(cmd_arr);
            pthread_t new_thread;
            if (pthread_create(&new_thread, NULL, (void*)system, (void*)ext_cmd) != 0){
                printf("Failed to create new thread.\n");
            }
            if (pthread_join(new_thread, NULL) != 0){
                printf("New thread termination failed.\n");
            }
            free(ext_cmd);
        }
        else if (strcmp(cmd_arr[0], "mkdir") == 0){
            cmd_arr[0] = "/home/dakshp/Desktop/OSAssignment1/mkdir";
            pid_t pid = fork();
            if (pid == 0){
                if (execv(cmd_arr[0], cmd_arr) == -1){
                    fprintf(stderr, "Failed to change files : %s\n", strerror(errno));
                }
            }
            else if (pid > 0){
                wait(NULL);
            }
            else{
                fprintf(stderr, "Child process creation failed.\n");
            }
        }
        else if (strcmp(cmd_arr[0], "mkdir&t") == 0){
            cmd_arr[0] = "/home/dakshp/Desktop/OSAssignment1/mkdir";
            ext_cmd = make_cmd(cmd_arr);
            pthread_t new_thread;
            if (pthread_create(&new_thread, NULL, (void*)system, (void*)ext_cmd) != 0){
                printf("Failed to create new thread.\n");
            }
            if (pthread_join(new_thread, NULL) != 0){
                printf("New thread termination failed.\n");
            }
            free(ext_cmd);
        }
        else if (strcmp(cmd_arr[0], "exit") == 0){
            break;
        }
        else{
            fprintf(stderr, "Command \"%s\" invalid/not implemented.\n", cmd_arr[0]);
        }
        free(cmd);
        free(cmd_arr);
    }
    
    return 0;
}