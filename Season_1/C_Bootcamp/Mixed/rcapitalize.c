#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *rcapitalize(char *str) {

    char *adrs = str;
    int i=0;
    while (str[i] != '\0'){
        if ((str[i] >= 'A') && (str[i] <= 'Z')){ // lower every upper capital ignore the rest
        	str[i] = str[i] + 32; 
        }
        if (str[i] == 32)
        	if (str[i-1] >= 'a' && str[i-1] <= 'z')
               	str[i-1] = str[i-1] - 32; 
        
     	
        
        i++; 
	
	}
    str[i-1] = str[i-1] - 32;

	return str;

}



int main(){
	char arr[]="ceTTe pHRase";
	printf("%s\n", rcapitalize(arr));

	return 0;
}