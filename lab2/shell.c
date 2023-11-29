#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <time.h>

#define MAX_N 1024
#define N 64
#define RED(msg) "\033[31m"#msg"\033[0m"
#define GOLD(msg) "\033[33m"#msg"\033[0m"
#define BLUE(msg) "\033[32m"#msg"\033[0m"
char *vec[MAX_N] = {0};
char *cmd[N][N] = {0};
char talk[][MAX_N] = {
        {"Blue... Blue!! Blue ?\n"},
        {"Are you teaching me how to do the job?\n"},
        {"I am a fish, not a shell, try some simple cmd!\n"},
        {"How dare you let me do so many homework?\n"},
        {"Can you say the language of fish ??\n"},
        {"Let me do some simple work!\n"}
};
int has_ch_dir = 1;
char path[MAX_N] = {0};
struct passwd *usr;

void prompt() {
    char buf[MAX_N] = {0};
    if (has_ch_dir) {
        has_ch_dir = 0;
        if (getcwd(buf, MAX_N) == NULL) {
            perror("getcwd()");
            exit(1);
        }
        int cnt = 0;
        int i =0;
        for (i = 0; buf[i]; i++) {
            if (buf[i] == '/') {
                cnt = 0;
                continue;
            }
            path[cnt++] = buf[i];
        }
        path[cnt] = '\0';
    }
    fprintf(stdout, RED(%s) "@" GOLD(fish:), usr->pw_name);
    fprintf(stdout, BLUE(%s $), path);
}

void analysis(char *str, char **vec) {
    char argu[MAX_N][MAX_N] = {0};
    memset(vec, 0, sizeof(char *) * MAX_N);
    int cnt = 0;
    int i,j,t=0;
    for (i = 0,j = 0,t = 1; str[i] && str[i] !='\n'; i++){
        if (str[i] == ' ') {
            if (t) {cnt++,j = 0, t = 0;}
            continue;
        }
        t = 1;
        argu[cnt][j++] = str[i];
    }
    if (argu[0][0] == 0) return;
    for (i = 0; i <= cnt; i++) {
        vec[i] = strdup(argu[i]);
    }
    return;
}

void my_execv() {
    pid_t cpid;
    if ((cpid = fork()) < 0) {
        perror("fork()");
        return;
    }

    if (cpid == 0) {
        execvp(vec[0], vec);
        perror("myfish");
        exit(1);
    }
    else{
        int t;
        if (wait(&t) < 0){
            exit(1);
        }
    }
}

int redirctB() {
    int fd = open(cmd[1][0], O_WRONLY|O_CREAT, 0644);
    if (fd < 0) {
        perror("open()");
        return 1;
    }
    fflush(stdout);

    int out = dup(STDOUT_FILENO);

    if (dup2(fd, STDOUT_FILENO) < 0 || out < 0){
        perror("dup()");
        return 1;
    }

    pid_t pid = fork();
    if(pid < 0) {
        perror("fork()");
        return 1;
    }

    if (pid == 0) {
        execvp(cmd[0][0], cmd[0]);
        perror("execvp()");
        exit(1);
    }
    dup2(out, STDOUT_FILENO);
    close(fd);
    wait(NULL);
    return 0;
}

int redirctL() {
    int fd = open(cmd[1][0], O_RDONLY);
    if (fd < 0) {
        perror("open()");
        return 1;
    }
    fflush(stdin);

    int infd = dup(STDIN_FILENO);
    if (dup2(fd, STDIN_FILENO) < 0 || infd < 0){
        perror("dup()");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork()");
        return 1;
    }
    if (pid == 0) {
        execvp(cmd[0][0], cmd[0]);
        perror("execvp()");
        exit(1);
    }

    dup2(infd, STDIN_FILENO);
    close(infd);
    wait(NULL);
    return 0;
}

int redirPip() {
    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd) < 0) {
        perror("pipe()");
        return 1;
    }

    fflush(stdout);
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork()");
        return 1;
    }

    if (pid1 == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execvp(cmd[0][0], cmd[0]);
        perror("execvp()");
        exit(1);
    }

    pid2 = fork();
    if (pid2 < 0){
        perror("fork()");
        return 1;
    }
    if (pid2 == 0){
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execvp(cmd[1][0], cmd[1]);
        perror("execvp()");
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}

void swim_dir() {
    if (chdir(vec[1]) < 0){
        perror("chdir()");
        return;
    }
    has_ch_dir = 1;
}

int redirect() {
    char *flag = NULL, cnt = 0;

    if (vec[0] == NULL) return 0;
    if (!strcmp(vec[0], "cd")) {
        swim_dir();
        return 0;
    }

    memset(cmd, 0, sizeof(cmd));
    int i,t=0;
    for (i = 0,t = 0; vec[i]; i++) {
        if (!strcmp(vec[i], "|")||!strcmp(vec[i], "<") || !strcmp(vec[i], ">")) {
            flag = strdup(vec[i]);
            cnt++;
            t = 0;
            continue;
        }
        cmd[cnt][t++] = vec[i];
    }
    if (strcmp(cmd[0][0], "blue") == 0) {
        printf("%s", talk[0]);
        return 0;
    }

    srand(time(0));
    if (cnt > 1) {
        printf("%s", talk[rand() % 6]);
        return 0;
    }

    if (flag == NULL) {
        my_execv();
        return -1;
    }

    if(strcmp(flag, ">") == 0) {
        redirctB();
    }
    else if (strcmp(flag, "<") == 0){
        redirctL();
    }
    else if (strcmp(flag, "|") == 0){
        redirPip();
    }
    return 0;
}

int main(int argc, char *argv[]){
    char *buff = NULL;
    size_t buff_size = 0;

    fprintf(stdout, BLUE("  Blue. Blue. Blue...\n"  ));
    fprintf(stdout, "I'm a fish, nice to meet you!\n\n");

    usr = getpwuid(getuid());
    if (usr == NULL) {
        perror("getpwuid()");
        exit(1);
    }

    while (1) {
        prompt();
        if (getline(&buff, &buff_size, stdin) < 0){
            perror("getline()");
            break;
        }
        analysis(buff, vec);

        redirect();
    }

    return 0;
}
