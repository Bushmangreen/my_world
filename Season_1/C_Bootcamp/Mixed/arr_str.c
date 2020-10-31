#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){

	int a = 10;
	int *ptr=&a;
	char* arr[] = {"ab","bac","test"};
	char* b = "--"
	int new_arr[4];
	for (int i = 0; i< 3; i++){
	        new_arr[i] = strlen(arr[i]);
	        printf("%d\n", new_arr[i] );


	        //printf("%d\n", (int)( sizeof(new_arr) / sizeof(new_arr[0]) ) );
	    }
	printf("%d\n", *ptr );

    return 0;
}