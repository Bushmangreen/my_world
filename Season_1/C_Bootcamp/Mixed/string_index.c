#include <stdio.h>
#include <string.h>

int my_string_index(char *a,char *b){
	/* Define a pointer of type char, a string and the substring to be found*/
	
	int index;
	char *cptr;
	/* Find memory address where substr "edia, b" is found in str */
	cptr = strstr(a, b);
	index = (int)(cptr - a);
	/* Print out the character at this memory address, i.e. 'e' */
	//printf("%d\n", index);

	/* Print out "edia, be bold" */
	//printf("%s\n", cptr);

	if (index > 1000 || index <0) return -1;
	
	else return index;
}

/*
Just subtract the string address from what strchr returns:

char *string = "qwerty";
char *e;
int index;

e = strchr(string, 'e');
index = (int)(e - string);
*/

int main(void) {
	/* Define a pointer of type char, a string and the substring to be found*/


	printf("%d\n",my_string_index("hello","tt"));

	return 0;
}