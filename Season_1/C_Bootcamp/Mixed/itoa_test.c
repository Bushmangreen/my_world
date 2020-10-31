
#include <stdio.h>

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


int main(){

	const char characters_map[] = "0123456789abcdef";
	int value = 10;
	int base = 8;
	int index = 4%8;
	int i;
	static char buffer[32] = {0};

	
	//buffer[i] 

	printf("%s  \n", itoa(0,16));


	return 0;
}