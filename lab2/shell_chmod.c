#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

void shell_chmod(int argc, char *argv[]){
    int mode;                            //权限
    int mode_u;                          //所有者的权限
    int mode_g;                          //所属组的权限
    int mode_o;                          //其他用户的权限
    char *filename;                      //存放要修改的文件
    //argv[0]--chmod
    //argv[1]--mode number
    //argv[2]--file
    if (argc  < 3) {                             //参数默认为3个

        printf("%s <mode num> <target file>", argv[0]);
        exit(0);

    }

    /*获取命令行参数*/
    //atoi()函数将字符串转换成整形数
    mode = atoi(argv[1]);
    if (mode > 777 || mode < 0) {
        printf("mode error\n");
        exit(0);
    }

    mode_u = mode / 100;
    mode_g = ( mode - mode_u * 100 ) /10;
    mode_o = mode - mode_u * 100 - mode_g *10;
    //转换成八进制表示
    mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;
    filename = argv[2];
    //权限修改失败返回-1
    if ( chmod (filename,mode) ==  -1  ) {
        perror("chmod fail");
        exit(1);
    }
    printf("\033[34mThe chmod command is executed successfully!\033[0m\n");
}
