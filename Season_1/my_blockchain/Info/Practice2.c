#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* my_strstr(char* str, char* substring) {
  
  	const char *a = str;
  	const char *b = substring;

	for (;;) 
	{
		if ( !*b ) 
			return (char *) str;

		if ( !*a ) 
			return NULL;

		if ( *a++ != *b++)
		{ 
			a = str++; 
			b = substring; 
		}
	}
}

void my_memset(char* str)
{
	while(*str)
	{
		*str = '\0';
		str++;
	}
}

char* my_itoa(int num)
{
	char* str = malloc(10);
	my_memset(str);
	int i = 0, rem = 0;
	int copy = num;
	int digits = 0;

	while(copy)
	{
		copy = copy/10;
		digits++;	
	}
	
	i = digits;

	while(i>0)
	{
		str[i - 1] = num%10 + '0';
		num = num / 10;
		i--;
	}
	str[digits] = '\0';
	return str;
}

int main(int ac, char **av)
{

	char* test = my_itoa(0);

	printf("%s\n",test );
	free(test);
	return 0;
}                   
                                            