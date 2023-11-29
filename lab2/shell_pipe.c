#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
extern void shell_ls_l(char* file, struct stat st);
extern int shell_ls(int argc, char* argv[]);
extern void shell_chmod(int argc, char* argv[]);
int shell_pipe(int argc, char *argv[]) {
    int i, j, k;
    int num = 0;
    int pipefd[2];
    pid_t pid;
    char *arg1[256], *arg2[256];
    memset(arg1, 0, sizeof(arg1));
    memset(arg2, 0, sizeof(arg2));
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            num = i;
            break;
        }
        arg1[i] = argv[i];
    }
    j = 0;
    for (i = num + 1; i < argc; i++) {
        arg2[j] = argv[i];
        j++;
    }
    if (pipe(pipefd) < 0) {
        printf("pipe error\n");
        return -1;
    }
    pid = fork();
    if (pid < 0) {
        printf("fork error\n");
        return -1;
    } else if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        if (strcmp(arg1[0], "chmod") == 0) {
            shell_chmod(num, arg1);
        } else if (strcmp(arg1[0], "ls") == 0) {
            shell_ls(num, arg1);
        } else {
            printf("invalid command\n");
        }
        exit(0);
    } else {
        pid = fork();
        if (pid < 0) {
            printf("fork error\n");
            return -1;
        } else if (pid == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            if (strcmp(arg2[0], "ls") == 0) {
                shell_ls(j, arg2);
            } else {
                printf("invalid command\n");
            }
            exit(0);
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid, NULL, 0);
        }
    }
    return 0;
}
