#include "my_header.h"

int choice(int n,char** arr,int* a,int* t, int *R, char direc[5][100],char filename[5][100], int* dir_flag, int* file_flag){
	int index1 = 0;
	int index2 = 0;
	if (n == 1){
		return 1;
	}
	else if (n ==2 && arr[1][0] == '.'){
		return 1;
	}

	else {
	

	    for (int i = 0; i < n; i++){
	    	if (arr[i][0] == '-'){
	    		if (strchr(arr[i],'R')){
	    			*R = 1;
	    		}
	    		if (strchr(arr[i],'a')){
	    			*a = 1;
	    		}
	    		if (strchr(arr[i],'t')){
	    			*t = 1;
	    		}
	    	}

		    else if (i > 0 && strchr((arr[i]),'/')){
		    	strcpy(direc[index1++],arr[i]);
		    	*dir_flag = 1; 
		 	}

		 	else if (i > 0) {
		 		strcpy(filename[index2++],arr[i]);
		 		*file_flag = 1; 
		 	}
	    }

	    
	} 
	return 0;
}

