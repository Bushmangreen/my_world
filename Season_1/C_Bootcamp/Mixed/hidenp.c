#include <string.h>


int hidenp(char* str1, char* str2) {

    if (strlen(str1)==0){
        return 1;
    }
    char l=0,r=0;

    while(str2[r] != '\0'){
        if (str1[l] == str2[r]){
            r++;
            l++;
        }else r++;

    }
    if (l>strlen(str1)-1)
        return 1;
    else return 0;
}

