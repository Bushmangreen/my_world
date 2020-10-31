
string_array* my_split(char* str, char* delim) {

  ////"abc def gh-!" && "-"
    int i=0;
    int c=0;
    int index = 0; // index for the strin location;
    string_array *arr_struct;
    arr_struct->array = (char**) malloc(30 * sizeof(char*));

    while(str[c] != '\0'){ // scanning the string for the fisrt delimeter
        
        arr_struct->array[index][i] = str[c]; // 1st character written to arr;
        i++;
        c++;

        if (str[c] == *delim){
            index++;
            i=0;
            while (str[c] != *delim){
                arr_struct->array[index][i] = str[c];// recording everying until next delimeter
                c++;  
                i++;             // write everything into next array unitl next delimeter met
                if (str[c] == '\0')
                    break;           // if next delimeter met, incerement the array
                       // if else not met return the array;
            }
            arr_struct->array[index][i] = '\0';

        }

        


    }   
    free(arr_struct);
    return arr_struct;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_STRING 4
#define MAX_STRING_SIZE 40

typedef struct s_string_array {
    int size;
    char** array;
  } string_array;

string_array* my_split(char* str, char* delim) {

  
    int i=0;
    int c=0;
    int index = 0; // index for the strin location;
    string_array *arr_struct;

    char *test[]={"hello","there"}; 

    

    //test = (char**) malloc(10 * sizeof(char*));
/*
    while(str[c] != '\0'){ // scanning the string for the fisrt delimeter
        
        test[index][i] = str[c]; // 1st character written to arr;
        i++;
        c++;

        if (str[c] == *delim){
            index++;
            i=0;
            while (str[c] != *delim){
                test[index][i] = str[c];// recording everying until next delimeter
                c++;  
                i++;             // write everything into next array unitl next delimeter met
                if (str[c] == '\0')
                    break;           // if next delimeter met, incerement the array
                       // if else not met return the array;
            }
            test[index][i] = '\0';

        }

    


    }  
*/
    arr_struct-> array = &test[0]; 
 //   free(test);
    return arr_struct;
}


int main (){
/*
     
    string_array arr;

  
 
char *str[] =
{ "ar",
  "is",
  "mak",
  "tel"
};

arr.array = str;

*/
char str[]="hello-there";
char del[]= "-";
char (*array[5])[5];

    string_array *test;
    test = my_split(str,del);

    printf("%s\n", test->array[0]);

    return 0;
}