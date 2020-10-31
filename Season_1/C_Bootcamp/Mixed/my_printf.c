#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

// how to implement my_printf 
// explanation of variadic functions https://www.youtube.com/watch?v=S-ak715zIIE
// need to read the comment as well in the video comment section
// the link below actual implementation of printf() finction with nice explanation
// http://www.firmcodes.com/write-printf-function-c/


void my_printf(char* format,...) 
{ 
	char *string_character; 
	int i; 
	char *s; 
	
	//Module 1: Initializing Myprintf's arguments 
	va_list arg; 
	va_start(arg, format); 
	
	for(string_character = format; *string_character != '\0'; string_character++) { //see each character in the string
		
		while( *string_character != '%' && string_character != '\0' ) { // we gonna put all the character until we see % or NULL
			
			putchar(*string_character);
			string_character++; 
		} 
		
		string_character++; 
		
		//Module 2: Fetching and executing arguments
		switch(*traverse) { 
			case 'c' : i = va_arg(arg,int);		//Fetch char argument
						putchar(i);
						break; 
						
			case 'd' : i = va_arg(arg,int); 		//Fetch Decimal/Integer argument
						if(i<0) 
						{ 
							i = -i;
							putchar('-'); 
						} 
						puts(convert(i,10));
						break; 
						
			case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
						puts(convert(i,8));
						break; 
						
			case 's': s = va_arg(arg,char *); 		//Fetch string
						puts(s); 
						break; 
						
			case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
						puts(convert(i,16));
						break; 
		}	
	} 







int main(){

	my_printf_test(5,2,3,4,5,3,4);



	return 0;
}


/*
int my_printf(const char *format,...){
	
	va_list args;
	int done;

	va_start(args,format);
	done = vfprintf(stdout,format,args);
	va_end(args);

	return done;
}


void my_printf_test(int num,...){

	va_list variable_list;

	va_start(variable_list,num);

	for (int i = 0; i < num; i++ ){

		int value = va_arg(variable_list,int);
		printf("%d: %d\n", i, value);

	}

	va_end(args);

}

*/


