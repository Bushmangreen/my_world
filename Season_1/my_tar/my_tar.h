
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

typedef struct t_opt
{
	int c;
	int r;
	int t;
	int u;
	int x; 
	
}t_opt;

t_opt* get_opt(int argc, char *argv[]);
void print_opt(t_opt* opt);