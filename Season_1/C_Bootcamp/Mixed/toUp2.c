#include <stdio.h>
#include <string.h>
#include <ctype.h>


int my_upcase(char *str){

	


	while(*str){
		*str = toupper(*str);
		str++;
		
	}
	//val[i] = "0";

	



return *str;

}



int main(){

	char str[30] = "hello";
	my_upcase(str);
	printf("%s\n", &str);



   
}