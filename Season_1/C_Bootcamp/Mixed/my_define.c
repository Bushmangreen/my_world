
//#include<stdio.h> 
//#include<string.h> 
#include<unistd.h> 
//#include<fcntl.h> 
#include<stdlib.h> 
  

#define EVEN(x) (x%2!=0)
#define SUCCESS 0
#define EVEN_MSG "I have an even number of arguments.\n"
#define ODD_MSG "I have an odd number of arguments.\n"
//#define TRUE 1
//#define FALSE 0
typedef enum {FALSE, TRUE} t_bool;
/*
Input: 1
Output: 
Return Value: "I have an odd number of arguments."

Input: 2
Output: 
Return Value: "I have an even number of arguments."

*/
void my_putstr(char *str)
{
    int index;

    index = 0;
	while (str[index] != '\0') {
		write(1, &str[index], 1);
		index++;
	}
}

t_bool	my_is_even(int nbr)
{
	return ((EVEN(nbr)) ? TRUE : FALSE);
}

/*
char* my_define(int num) {


}
*/

int	my_main(int argc)
{
	
	if (my_is_even(argc - 1) == TRUE)
		my_putstr(EVEN_MSG);
	else
		my_putstr(ODD_MSG);
	return (SUCCESS);
}


int main(int argc,char* argv[]){
	int t = atoi(argv[1]);
	my_main(t);

}