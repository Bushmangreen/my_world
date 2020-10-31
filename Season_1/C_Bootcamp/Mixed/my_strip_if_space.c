#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* my_strip(char* str) {

    char upd_str[strlen(str)];
    int c = 0;
    int index = 0;
    char *adrs = str;

    //upd_str =(char* )malloc(strlen(str)*sizeof(char));
/*
	if (upd_str == NULL) {
   		perror("malloc failed");
    	exit(1);
	}
*/
    while(str[c] != '\0'){

        //if i see the caracter after that i see a space, i should take it in 
        //if i space after space i will ignore it and increment until next character
        //
        if (str[c] != 32)
            upd_str[index++] = str[c];
        if (str[c] != 32 && str[c+1] == 32) //
            upd_str[index++] = ' ';   // take the space into 
        c++;
                //collect the string
    }
    if (str[c-1] == ' ')
		upd_str[index-1] = '\0';
	else 
		upd_str[index] = '\0';

    int i = 0;
    while(upd_str[i] != '\0'){
        str[i] = upd_str[i];
       	i++;
    }
    str[i] = '\0'; 

   // free(upd_str);
    
    return str;
}


int main (){

	char arr[] = " this        time it      will     be    more complex  . ";
	printf("%s\n", my_strip(arr));
	return 0;
}