#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* my_union(char* str1, char* str2) {


	int p=0,k=0,i,j;
	int index = 0;
	
	char *str_collector = malloc(strlen(str2)*sizeof(char));
	char *str_cat = malloc((strlen(str1)+strlen(str2))*sizeof(char));
	
	



	while(str1[p]){
		str_cat[p] = str1[p]; 
		p++;
	}

	while(str2[k]){
		str_cat[p] = str2[k]; 
		p++;
		k++;

	}
    

	str_cat[p] = '\0';

	// i need to check for unique values
	for (i = 0; i < strlen(str_cat); i++){
		for (j = 0; j < i; j++)
			if (str_cat[i] == str_cat[j])
				break;
			

		if (i == j)
			str_collector[index++] = str_cat[i]; 
	}
	str_collector[index] = '\0';

	




	
	free(str_cat);
	free(str_collector);
	return str_collector;
	
}






int main(){

	printf("%s\n", my_union("rien","cette phrase ne cache rien"));

	return 0;
}