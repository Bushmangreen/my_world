#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>


// how to implement my_printf 
// explanation of variadic functions https://www.youtube.com/watch?v=S-ak715zIIE
// need to read the comment as well in the video comment section
// the link below actual implementation of printf() finction with nice explanation
// http://www.firmcodes.com/write-printf-function-c/ used as a base, but implemented my own style and functions


//   These functions return the number of characters printed (not including
//     the trailing `\0' used to end output to strings) or a negative value if
//     an output error occurs, except for snprintf() and vsnprintf(), which
//     return the number of characters that would have been printed if the n
//     were unlimited (again, not including the final `\0')

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


int my_printf(const char* format,...){
	va_list args;
	va_start(args,format);

	const char* character_now;
	char * initial_address;
	int prnt_this;
	int counter = 0;
	for (character_now = format; *character_now != '\0'; character_now++ ){

		while (*character_now != '\0' && *character_now != '%'){

			my_putchar(*character_now);
			character_now++;
			counter++;
		
		}

		if (*character_now == '\0') break; // in case we do increment caracter_now twice so that passing over NULL character, which infinite loop

		character_now++;
		
		

		if (*character_now == 'c'){		// prints character done
			prnt_this = va_arg(args,int);
			counter++;
			my_putchar(prnt_this);
			
		
		} else if (*character_now == 'd' ){ // prints decimal done
			
			char* address;
			prnt_this = va_arg(args,int); // get the next argument

			if (prnt_this<0){
				my_putchar('-');
				counter++;
				prnt_this = -prnt_this;
			}
			address = itoa(prnt_this,10); // convert to string

			while(*address){				//print the string
				my_putchar(*address++);
				counter++;
			}



		} else if (*character_now == 'o' ){ //prints unsigned decimal in octal done
			
			char* address;
			prnt_this = va_arg(args,int); // get the next argument
			address = itoa(prnt_this,8); // convert to string

			while(*address){				//print the string
				my_putchar(*address++);
				counter++;
			}

		} else if (*character_now == 'u' ){ //prints unsigned decimal done
			
			char* address;
			prnt_this = va_arg(args,int); // get the next argument
			address = itoa(prnt_this,10); // convert to string

			while(*address){				//print the string
				my_putchar(*address++);
				counter++;
			}

		} else if (*character_now == 'x' ){//prints unsigned hexodecimal in decimal done
			
			char* address;
			prnt_this = va_arg(args,int); // get the next argument
			address = itoa(prnt_this,16); // convert to string

			while(*address){				//print the string
				my_putchar(*address++);
				counter++;
			}

		} else if (*character_now == 's' ){ // prints a string  done
			
			char*address;
			address = va_arg(args,char*);
			if (address == NULL) 
				address = "(null)";

			while(*address){
				my_putchar(*address++);
				counter++;
			}

		} else if (*character_now == 'p' ){ //

			unsigned long cast;			
			char* address;

			address = va_arg(args,void*); // get the next argument
			cast = (unsigned long) address;
			address = itoa(cast,16); // convert to string
			my_putchar('0');
			counter += 2;
			my_putchar('x');
			while(*address){				//print the string
				my_putchar(*address++);
				counter++;
			}

		}
	
	}

	va_end(args);
	

	return counter;
}

/*

int main(){

	char *name = "Nurdos Omarkulov";
	int age = 30;
	char s = 'A';
	
	int test1,test2,test3,test4,test5,test6,test7,test8,test9,test10,test11,test12,test13,test14;
	int test_1,test_2,test_3,test_4,test_5,test_6,test_7,test_8,test_9,test_10,test_11,test_12,test_13,test_14;
	

	
	printf("\n\n-------------------Test starts here--------------------\n\n");

		test1 = my_printf("Hello world!\n");
	 	test_1 =   printf("Hello world!\n");
	 	printf("%d and %d\n\n", test1, test_1);


		test2 = my_printf("Hello my name is %s i am %d years old and %c\n",name,age,s);
	   	test_2 =   printf("Hello my name is %s i am %d years old and %c\n",name,age,s);
	    printf("%d and %d\n\n",test2,test_2 );

		test3 = my_printf("Address: %p - original\n",&age);   
	    test_3 =   printf("Address: %p - original\n",&age);
	    printf("%d and %d\n\n",test3, test_3 );

	    test4 = my_printf("%c!\n", 'H');
	    test_4 =   printf("%c!\n", 'H');
	    printf("%d and %d\n\n",test4, test_4 );

	    test_5 = my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');
	    test5 =     printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');
	    printf("%d and %d\n\n",test5, test_5 );

	    test6 = my_printf("Hello %s!\n", "QWASAR.IO");
	    test_6 =   printf("Hello %s!\n", "QWASAR.IO");
	    printf("%d and %d\n\n",test6, test_6 );

	    test7 = my_printf("Hello %s %s!\n", "Mr", "Gaetan");
	    test7 =    printf("Hello %s %s!\n", "Mr", "Gaetan");
	    printf("%d and %d\n\n",test7, test_7 );

	    test8 = my_printf("NULL STRING %s!\n", (char*)NULL);
	    test_8 =   printf("NULL STRING %s!\n", (char*)NULL);
	    printf("%d and %d\n\n",test8, test_8 );

	    test9 = my_printf("%d!\n", 1337);
	    test_9 =   printf("%d!\n", 1337);
	    printf("%d and %d\n\n",test9, test_9 );

	    test10 = my_printf("%d - %d - %d!\n", 2048, 0, -1337);
	    test_10 =   printf("%d - %d - %d!\n", 2048, 0, -1337);
	    printf("%d and %d\n\n",test10, test_10 );

	    test11 = my_printf("%o!\n", 100);
	    test_11 =   printf("%o!\n", 100);
	    printf("%d and %d\n\n",test11, test_11 );

	    test12 = my_printf("%u!\n", 1337);
	    test_12 =   printf("%u!\n", 1337);
	    printf("%d and %d\n\n",test12, test_12 );

	    test13 = my_printf("%x!\n", 14);
	    test_13 =   printf("%x!\n", 14);
	    printf("%d and %d\n\n",test13, test_13 );

	    test14 = my_printf("%p!\n", &age);
	    test_14 =   printf("%p!\n", &age);
	    printf("%d and %d\n\n",test14, test_14 );
	    

	printf("-------------------Test ends here--------------------\n\n");
	return 0;
}
*/

#define GREEN "\033[32m" 
#define RED "\033[31;1m"
#define NORMAL "\033[0m"

void test_0() {
  printf("<#0>\n");
  int my_printf_ret_value = my_printf("Hello world!\n");
  int printf_ret_value = printf("Hello world!\n");
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#0>\n");
}

void test_1() {
  printf("<#1>\n");
  int my_printf_ret_value = my_printf("%c!\n", 'H');
  int printf_ret_value = printf("%c!\n", 'H');
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#1>\n");
}

void test_2() {
  printf("<#2>\n");
  int my_printf_ret_value = my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');
  int printf_ret_value = printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#2>\n");
}

void test_3() {
  printf("<#3>\n");
  int my_printf_ret_value = my_printf("Hello %s!\n", "QWASAR.IO");
  int printf_ret_value = printf("Hello %s!\n", "QWASAR.IO");
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#3>\n");
}

void test_4() {
  printf("<#4>\n");
  int my_printf_ret_value = my_printf("Hello %s %s!\n", "Mr", "Gaetan");
  int printf_ret_value = printf("Hello %s %s!\n", "Mr", "Gaetan");
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#4>\n");
}

void test_5() {
  printf("<#5>\n");
  int my_printf_ret_value = my_printf("NULL STRING %s!\n", NULL);
  int printf_ret_value = printf("NULL STRING %s!\n", NULL);
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#5>\n");
}

void test_6() {
  printf("<#6>\n");
  int my_printf_ret_value = my_printf("%d!\n", 1337);
  int printf_ret_value = printf("%d!\n", 1337);
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#6>\n");
}

void test_7() {
  printf("<#7>\n");
  int my_printf_ret_value = my_printf("%d!\n", -1337);
  int printf_ret_value = printf("%d!\n", -1337);
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#7>\n");
}

void test_8() {
  printf("<#8>\n");
  int my_printf_ret_value = my_printf("%d!\n", 0);
  int printf_ret_value = printf("%d!\n", 0);
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#8>\n");
}

void test_9() {
  printf("<#9>\n");
  int my_printf_ret_value = my_printf("%o!\n", 100);
  int printf_ret_value = printf("%o!\n", 100);
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#9>\n");
}

void test_10() {
  printf("<#10>\n");
  int my_printf_ret_value = my_printf("%u!\n", 1337);
  int printf_ret_value = printf("%u!\n", 1337);
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#10>\n");
}

void test_11() {
  printf("<#11>\n");
  int my_printf_ret_value = my_printf("%x!\n", 14);
  int printf_ret_value = printf("%x!\n", 14);
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#11>\n");
}

void test_12() {
  int a = 3;
  printf("<#12>\n");
  int my_printf_ret_value = my_printf("%p!\n", &a);
  int
printf_ret_value = printf("%p!\n", &a);
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#12>\n");
}

void test_13(){
  printf("<#13>\n");
  int my_printf_ret_value = my_printf("%d - %d - %d!\n", 2048, 0, -1337);
  int printf_ret_value = printf("%d - %d - %d!\n", 2048, 0, -1337);
  printf("%s my_printf(%d) == printf(%d) %s\n", my_printf_ret_value != printf_ret_value ? RED : GREEN , my_printf_ret_value, printf_ret_value, NORMAL);
  printf("</#13>\n");
}


int main(int ac, char **av) {
    test_0();
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    test_8();
    test_9();
    test_10();
    test_11();
    test_12();
    test_13();
    return 0;
}


