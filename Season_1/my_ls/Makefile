# -*- Makefile -*- 


#target: dependencies
#	action
 

my_ls: my_ls.o choice.o sort_files.o list_filename.o
	gcc my_ls.o choice.o sort_files.o list_filename.o -o my_ls

my_ls.o: my_ls.c my_header.h
	gcc -c my_ls.c

choice.o: choice.c my_header.h
	gcc -c choice.c

sort_files.o: sort_files.c
	gcc -c sort_files.c

list_filename.o: list_filename.c
	gcc -c list_filename.c




clean:
	rm -f *.o my_ls 