#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>



int my_isalnum(char a) {
  if ((a <= 'Z' && a >= 'A') || (a <= 'z' && a >= 'a') || (a <= '9' && a >= '0')) {
    
    return 1;
  }
  else {
    return 0;
  }
}

int my_isalnum2(char a) {
  if (a<=1&&a>='060') {
    
    return 1;
  }
  else {
    return 0;
  }
}

void my_print_reverse_alphabet() {

    char ch;
    for(ch='z'; ch>='a'; ch--)    
    {

        printf("%c",ch);

    }
    printf("\n");
}



int main(){


	printf("%d\n", my_isalnum2('4'));
	
	return 0;
}





