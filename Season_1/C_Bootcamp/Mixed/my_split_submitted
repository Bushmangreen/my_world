#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>


typedef struct s_string_array {
    int size;
    char** array;
  } string_array;

string_array* my_split(char* str, char* delim) {
    int i=0;
    int c=0;
    char* token;
    int index = 0; // index for the strin location;
    string_array *new = (string_array*) malloc(sizeof(string_array));;
    char **arr = (char**) malloc(30 * sizeof(char*));
    
    //char str[] = "abc def gh-!"; 
  
    // Returns first token 
    // Keep printing tokens while one of the 
    // delimiters present in str[]. 
    token = strtok(str, delim);
    arr[i] = token;
    i++;
    c++;
    while (token != NULL) { 
        token = strtok(NULL, " "); 
        arr[i] = token; 
        i++;
        c++;
        
    }

    new -> array = arr;
    new -> size = c-1;
    return new;

}




int main() 
{ 
    char arr1[] = "abc def gh-!";
    char arr2[] = " ";
    string_array *test;
    test = my_split(arr1,arr2);
   
    for (int i=0; i< test->size;i++){
        printf("%s\n", test -> array[i]); 
    }

   // free(arr); 
    return 0; 
} 