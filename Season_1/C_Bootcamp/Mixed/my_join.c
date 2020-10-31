#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){


	char* arr[] = {"ab","bac","test"};
	char* b = "--";
	char* ptr;
	char* adrs;

	adrs = ptr;
	for (int i = 0; i< 3; i++){

		ptr = arr[i];
		ptr++;
		*ptr = b;
        printf("%s\n", ptr );

	        //printf("%d\n", (int)( sizeof(new_arr) / sizeof(new_arr[0]) ) );
	    }

	//printf("%d\n", *ptr );

    return 0;
}