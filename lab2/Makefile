objects = head.h shell_cat.o shell_echo.o shell_ls.o shell_pwd.o shell_rm.o  shell_cd.o shell_man.o shell_mkdir.o shell_wc.o shell_clear.o shell_chmod.o shell_list.o shell_pipe.o Main.c
4423_mysh:$(objects)
	gcc -o 4423_mysh $(objects)
%.o: %.c
	gcc -c $<
clean:
	rm *.o
	rm 4423_mysh
