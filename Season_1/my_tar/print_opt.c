

#include "my_tar.h"

void print_opt(t_opt* opt)
{
	if (opt->c) printf("-c option has been set\n");
	if (opt->r) printf("-r option has been set\n");	
	if (opt->t) printf("-t option has been set\n");		
	if (opt->u) printf("-u option has been set\n");		
	if (opt->x) printf("-x option has been set\n");	
}	