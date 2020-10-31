#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>



#define BASE10 10
#define BASE8 8
#define BASE16 16



void my_putchar(char c);
char* itoa(unsigned long val, int base);
void my_printf(const char* format,...);


int main(){

	char* name = "Aziza";
	int age = 0 ,num1,num2,num3;
	int*ptr = &age;
	char s = 's';
	
	my_printf("Hello %s! %d\n", "World", 123);
	  num1 = printf("Hello %s! %d\n\n", "World", 123);
	  printf("%d\n\n",num1 );


	my_printf("Hello my name is %s i am %d years old and %c\n",name,age,s);
	   num2 = printf("Hello my name is %s i am %d years old and %c\n\n",name,age,s);
	    printf("%d\n\n",num2 );

	my_printf("Address: %p - my address\n",ptr);   
	   num3 = printf("Address: %p - original\n\n",ptr);
	    printf("%d\n\n",num3 );


	    my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');

	return 0;
}



void my_putchar(char c) { // pirints character to strandard output
 	write(1, &c, 1);
}

char* itoa(unsigned long value, int base){ // converts integer to string
	
	static char buffer[32] = {0};
	const char characters_map[] = "0123456789abcdef";
	
	int i = 30;
	int index;

	if (value == 0) return "0";

	for ( i = 30; value && i ; --i) {
		
		index = value % base ;
		buffer[i] = characters_map[index];
		value /= base;
		
	
	}
	return &buffer[i+1];
}

void my_printf(const char* format,...){
	va_list args;
	va_start(args,format);

	const char* character_now;
	int prnt_this;


	while (*character_now){

		while (*character_now != '\0' && *character_now != '%'){

			my_putchar(*character_now);
			character_now++;
		
		}

		if (*character_now == '\0') break; // in case we do increment caracter_now twice so that passing over NULL character, which infinite loop

		character_now++;
		

		if (*character_now == 'c'){		// prints character done
			prnt_this = va_arg(args,int);
			my_putchar(prnt_this);
		
		} else if (*character_now == 'd' ){ // prints decimal done
			
			char* address;
			prnt_this = va_arg(args,int); // get the next argument

			if (prnt_this<0){
				my_putchar('-');
				prnt_this = -prnt_this;
			}
			address = itoa(prnt_this,BASE10); // convert to string

			while(*address){				//print the string
				my_putchar(*address++);
			}



		} else if (*character_now == 'o' ){ //prints unsigned decimal in octal done
			
			char* address;
			prnt_this = va_arg(args,int); // get the next argument
			address = itoa(prnt_this,BASE8); // convert to string

			while(*address){				//print the string
				my_putchar(*address++);
			}

		} else if (*character_now == 'u' ){ //prints unsigned decimal done
			
			char* address;
			prnt_this = va_arg(args,int); // get the next argument
			address = itoa(prnt_this,10); // convert to string

			while(*address){				//print the string
				my_putchar(*address++);
			}

		} else if (*character_now == 'x' ){//prints unsigned hexodecimal in decimal done
			
			char* address;
			prnt_this = va_arg(args,int); // get the next argument
			address = itoa(prnt_this,BASE16); // convert to string

			while(*address){				//print the string
				my_putchar(*address++);
			}

		} else if (*character_now == 's' ){ // prints a string  done
			
			char*address;
			address = va_arg(args,char*);

			while(*address){
				my_putchar(*address++);
			}

		} else if (*character_now == 'p' ){ //

			unsigned long cast;
			
			char* address;

			address = va_arg(args,void*); // get the next argument
			//printf("Address: %p - original\n",address); //debugging
			//ret = strtoul(address, &ptr, 10);
   			//printf("The number(unsigned long integer) is %lu\n", ret); //debugging
			
			
			cast = (unsigned long) address;
			//printf("Address: %lu - original\n",cast); //debugging
			
			address = itoa(cast,16); // convert to string
			my_putchar('0');
			my_putchar('x');
			while(*address){				//print the string
				my_putchar(*address++);
			}

		}
	
	}

	va_end(args);
	//return 0;
}
