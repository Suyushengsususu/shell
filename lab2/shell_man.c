#include<stdio.h>
#include <string.h>

int shell_man(int argc,char *argv[])
{
    if(argc==2)
    {
        //normal shell command
        if(strcmp(argv[1],"ls")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\tls [-a] [-l] [路径]：用来显示目标目录列表（路径只能是文件夹且路径必须以”/”结尾：例如：ls -l /home/）\n");
            printf("语法:\n");
            printf("\tls（选项）（参数）\n");
            printf("\t[路径]：显示目标目录下的非隐藏文件名\n");
            printf("\t-a[路径]：显示目标目录下的所有文件名\n");
            printf("\t-l[路径]：显示目标目录下文件的详细信息\n");

        }
        else if(strcmp(argv[1],"echo")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\techo [字符串(可带空格)]：用来直接输出指定的字符串\n");
            printf("语法:\n");
            printf("\techo (参数)\n");
            printf("\t[字符串]：直接打印出指定的字符串\n");
        }
        else if(strcmp(argv[1],"cat")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\tcat [-n] [路径]：用来显示文件的内容.\n");
            printf("语法:\n");
            printf("\tcat(选项)(参数)\n");
            printf("\t[路径]：显示指定文件的内容\n");
            printf("\t-n[路径]：显示指定文件的内容，显示的时候在每行行首的位置加上行号\n");
        }
        else if(strcmp(argv[1],"mkdir")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\tmkdir [路径]：用来创建文件夹\n");
            printf("语法:\n");
            printf("\tmkdir (参数)\n");
            printf("\t[路径]：创建指定路径的文件夹\n");
        }
        else if(strcmp(argv[1],"rm")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\trm -r [路径]：用来删除一个文件或者一个文件夹\n");
            printf("语法:\n");
            printf("\trm (选项)(参数)\n");
            printf("\t[路径]：删除指定路径的文件\n");
            printf("\t-r [路径]：删除指定路径的文件夹\n");
        }
        else if(strcmp(argv[1],"cd")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\tcd [路径]|~|-：用来切换工作目录\n");
            printf("语法:\n");
            printf("\tcd (参数)\n");
            printf("\t[路径]：切换到指定路径\n");
            printf("\t-：切换到上一个工作目录\n");
            printf("\t~：切换到家目录\n");
        }
        else if(strcmp(argv[1],"pwd")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\tpwd：用来显示当前工作路径\n");
            printf("语法:\n");
            printf("\tpwd\n");
            printf("\t注：该命令无任何参数\n");
        }
        else if(strcmp(argv[1],"wc")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\twc -c -l -w [路径]：用来统计一个文件的行数，字符数和单词数\n");
            printf("语法:\n");
            printf("\twc (选项)(参数)\n");
            printf("\t-c [路径]：统计一个文件的字符数\n");
            printf("\t-l [路径]：统计一个文件的行数\n");
            printf("\t-w [路径]：统计一个文件的单词数\n");
        }
            //personal shell command
        else if(strcmp(argv[1],"history")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\thistory：用来显示最新执行的前20条历史命令\n");
            printf("语法:\n");
            printf("\thistory\n");
            printf("\t注：该命令无任何参数\n");
        }
        else if(strcmp(argv[1],"list")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\tlist：显示该shell脚本的所有指令功能\n");
            printf("语法:\n");
            printf("\tlist\n");
            printf("\t注：该命令无任何参数\n");
        }
        else if(strcmp(argv[1],"man")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\tman [命令名]：用来提命令帮助\n");
            printf("语法:\n");
            printf("\tman (参数)\n");
            printf("\t[命令名]：显示指定命令名的基本帮助信息\n");
            printf("\t支持命令：cat，cd，echo，out，man，ls，mkdir，pwd，rm，wc，history, clear\n");
        }
        else if(strcmp(argv[1],"clear")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\tclear：清楚屏幕\n");
            printf("语法:\n");
            printf("\tclear\n");
            printf("\t注：该命令无任何参数\n");
        }
        else if(strcmp(argv[1],"chmod")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\tchmod [权限代码] [文件名]：更改文件权限\n");
            printf("语法:\n");
            printf("\tchmod (权限代码) (参数)\n");
            printf("\t注：权限代码是大于0且小于777的整数\n");
        }
        else if(strcmp(argv[1],">")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\t[命令] > [文件名]：重定向\n");
            printf("语法:\n");
            printf("\t(命令) > (文件名)\n");
        }
        else if(strcmp(argv[1],">>")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\t[命令] >> [文件名]：追加重定向\n");
            printf("语法:\n");
            printf("\t(命令) >> (文件名)\n");
        }
        else if(strcmp(argv[1],"pipe")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\t[命令] | [命令]：多管道功能\n");
            printf("语法:\n");
            printf("\t(命令) | (命令)\n");
        }
        //exit shell command
        else if(strcmp(argv[1],"out")==0)
        {
            printf("%s命令:\n",argv[1]);
            printf("\tout：退出Hong'sshell\n");
            printf("语法:\n");
            printf("\tout\n");
            printf("\t注：该命令无任何参数\n");
        }
        else
        {
            printf("No such parameter!\n");
        }
    }
    else
    {
        printf("No such command!-man\n");
    }
    return 0;
}