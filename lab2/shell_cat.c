#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shell_cat(int argc, char *argv[])
{
    if(argc == 2)
    {
        FILE *fp;
        if( !(fp = fopen( argv[1], "r" )) )
        {
            printf("No such file or directory!");
            return 1;
        }
        int c;
        while( (c = fgetc(fp) ) != EOF )
        {
            fputc(c,stdout);
        }
        printf("\n");
        fclose(fp);
        printf("\033[34mThe cat command is executed successfully!\033[0m\n");
    }
    if(argc==3&&strcmp(argv[1],"-n")==0)
    {
        FILE *fp;
        char StrLine[1024];
        if( !(fp = fopen( argv[2], "r" )) )
        {
            printf("No such file or directory!");
            return 1;
        }
        int c;
        int count=1;
        while( fgets(StrLine,1024,fp) != NULL )
        {
            if(count<10)
            {
                printf("   %d  %s",count++,StrLine);
            }
            else if(count<100)
            {
                printf("  %d  %s",count++,StrLine);
            }
            else if(count<1000)
            {
                printf(" %d  %s",count++,StrLine);
            }

        }
        printf("\n");
        fclose(fp);
        printf("\033[34mThe cat command is executed successfully!\033[0m\n");
    }
    if(strcmp(argv[argc-2],">")==0)
    {
        FILE *src_file, *dst_file;
        if( !(src_file = fopen( argv[argc-3], "r" )) )
        {
            printf("No such file or directory!");
            return 1;
        }
        if( !(dst_file = fopen( argv[3], "w" )) )
        {
            printf("Failed to create file!");
            fclose(src_file);
            return 1;
        }
        int c;
        while( (c = fgetc(src_file)) != EOF )
        {
            fputc(c, dst_file);
        }
        fclose(src_file);
        fclose(dst_file);
        printf("\033[34mThe redirect command is executed successfully!\033[0m\n");
    }
    return 0;
}
