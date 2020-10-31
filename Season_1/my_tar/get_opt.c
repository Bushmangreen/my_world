

#include "my_tar.h"

int is_option(char* str)
{
	if (str[0] == '-')
		return 1;
	return 0;
}

t_opt* init_opt()
{
	t_opt* opt = (t_opt*)malloc(sizeof(t_opt));
	opt->c = 0;
	opt->r = 0;
	opt->t = 0;
	opt->u = 0;
	opt->x = 0; 
	return opt;
}
void set_option(t_opt* opt, char* str)
{
	int index = 0;
	while (str[index] != '\0')
	{	
		if (str[index] == 'c')
		{
			opt->c = 1;
		}
		if (str[index] == 'r')
		{
			opt->r = 1;
		}
		if (str[index] == 't')
		{
			opt->t = 1;
		}
		if (str[index] == 'u')
		{
			opt->u = 1;
		}
		if (str[index] == 'x')
		{
			opt->x = 1;
		}
		index++;
	}
}

t_opt* get_opt(int argc, char *argv[])
{
	t_opt* opt = init_opt();
	int index = 0;

	while(index < argc)
	{
		if (is_option(argv[index]) == 1)
		{
			set_option(opt, argv[index]+1);
		}
		index++;
	}


	return opt;
}