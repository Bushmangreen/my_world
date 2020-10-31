

#include <stdio.h>
#include "my_tar.h"

void print_opt(t_opt* opt,int argc, char* argv[])
{
    int index = 2;
    printf("============my_tar==============\n");
	if (opt->c) printf("Option has been set: \t-c\n");    
	if (opt->r) printf("Option has been set: \t-r\n");	
	if (opt->t) printf("Option has been set: \t-t\n");		
	if (opt->u) printf("Option has been set: \t-u\n");		
	if (opt->x) printf("Option has been set: \t-x\n");
    if (opt->f) printf("Option has been set: \t-f\n");	
    if ((str_search(argv[2], ".tar") == 1)) 
    {
        index = 3;
        printf ("Tar file name: \t\t %s\n", argv[2]);
    }
    while(index<argc)
    {
        printf("Files to be archived: \t %s\n", argv[index++]);
    }
    printf("================================\n");
}	