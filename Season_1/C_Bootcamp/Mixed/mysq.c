#include <stdio.h>


int main(void) {
    int width, height;
    printf("Please enter a number that will define  the size of the square: \n");
    scanf("%d", &width);
    scanf("%d", &height);
    width = width - 2;
    height = height - 2;

    

    const char *spaces="                                         "; 
    const char *dashes="*****************************************";
    if (width <= 1 && height <= 1){

    	printf("o\n");

    }else if (width <= 1){   // printing 1 column only
    	printf("o\n"); // %.*s is width specifier 
     	for(int i=1; i<=height; ++i)
    		{
       			printf("|\n");
    		}
    	printf("o\n");

    }else if (height <= 1){   // printing 1 row only

    	printf("o%.*so\n", width, dashes);
    	
    }else {

    printf("o%.*so\n", width, dashes); // %.*s is width specifier 
    //for(int i=1; i<width/2+1; ++i)

     for(int i=1; i<=height; ++i)
    {
        printf("|%.*s|\n",width, spaces);
    }
    printf("o%.*so\n", width, dashes); // %.*s is width specifier 
    //for(int i=1; i<width/2+1; ++i)
}
}