#include<stdio.h>
int shell_echo(int argc,char *argv[])
{
    if(strcmp(argv[argc-2],">")==0)
    {
        FILE *dst_file;
        if( !(dst_file = fopen( argv[argc-1], "w" )) )
        {
            printf("Failed to create file!");
            return 1;
        }
        int i=0;
        for(i = 1; i < argc - 2; i++)
        {
            fputs(argv[i], dst_file);
            fputs(" ",dst_file);
        }
        fclose(dst_file);
        printf("\033[34mThe redirect command is executed successfully!\033[0m\n");
        return 0;
    }
    if(strcmp(argv[argc-2],">>")==0)
    {
        FILE *dst_file;
        if( !(dst_file = fopen( argv[argc-1], "a" )) )
        {
            printf("Failed to create file!");
            return 1;
        }
        int i=0;
        for(i = 1; i < argc - 2; i++)
        {
            fputs("\n",dst_file);
            fputs(argv[i], dst_file);
        }
        fclose(dst_file);
        printf("\033[34mThe redirect command is executed successfully!\033[0m\n");
        return 0;
    }
    argc--;
    while(argc)
    {
        printf("%s%s",*++argv,(argc > 1)? " ":"");
        argc--;
    }
    printf("\n");
    printf("\033[34mThe echo command is executed successfully!\033[0m\n");
    return 0;
}
