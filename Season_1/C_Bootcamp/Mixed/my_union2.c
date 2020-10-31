#include <stdio.h>
#include <string.h>
#include <stdlib.h>




char* my_union(char* str1, char* str2) {
    
    
    int p=0,k=0,i,j;
	int index = 0;
	int str1_len=0; 
    int str2_len=0;
	
    char *str_collector = malloc((strlen(str1)+strlen(str2))*sizeof(char));
    char *str_org;
    str_org = str1;
    
    while(*str1){
        str1_len++;
        str1++;
    }
    while(*str2){
        *str1 = *str2;
        str2_len++;
        str1++;
        str2++;
    }
    *str1 = '\0';
    str1 = str_org;
	

	// i need to check for unique values
	for (i = 0; i < str1_len+str2_len; i++){
		for (j = 0; j < i; j++)
			if (str1[i] == str1[j])
				break;
			

		if (i == j)
			str_collector[index++] = str1[i]; 
	}
	str_collector[index] = '\0';

	int c=0;
	while(str_collector[c]!= '\0'){
		str1[c] = str_collector[c];
		c++;
	}

	str1[c] = '\0';
	free(str_collector);

	return str1;
}


int main(){

	char arg1[] = "rien";
	char arg2[] = "cette phrase ne cache rien";


	printf("%s\n", my_union(arg1,arg2));

	return 0;
}