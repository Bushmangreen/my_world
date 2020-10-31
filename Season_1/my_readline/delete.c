/*
**
** QWASAR.IO -- my_array_uniq
**
** @param {integer_array*} param_1
**
** @return {integer_array*}
**
*/
#include <stdlib.h>
#include <stdio.h>


/*
**
** QWASAR.IO -- last_word
**
** @param {char*} param_1
**
** @return {char*}
**
*/

/*
**
** QWASAR.IO -- my_csv_parser
**
** @param {char*} param_1
** @param {char*} param_2
**
** @return {string_array_array*}
**
*/

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array
{
    int size;
    char** array;
} string_array;
#endif





string_array* my_csv_parser(char* s1, char* s2)
{
    string_array* my_s = malloc(sizeof(string_array));
    my_s->*array = malloc(5*sizeof(char**));
    

 
  
    int i = 0;
    int j = 0;
    int ii = 0;
    int jj = 0;
    int index = 0;
  while( s1[index] != '\n' )
    {
        if (s1[index] != ',')
        { 
            index++;
            continue;
        }
        my_s->array[i][j++] = s1[index]+'0';
        index++;
    }
  
    my_s->array[i][j] = '\0';
    i++;
    index++;
    j = 0;
    while(s1[index] != '\n')
    {        
        if (s1[index] != ',')
        { 
            index++;
            continue;
        }
        my_s->array[i][j++] = s1[index]+'0';
        index++;
    }
    
    my_s->array[i][j] = '\0';
    my_s->size = i+1;
          
        

        
    return my_s;
}

int main(int argc, char const *argv[])
{
  /*
  char string[] = "" ;
  char* word;
  word = last_word(string);
  printf("%s\n", word);
  free(word);
  */
  char array[] = "a,b,c,e\n1,2,3,4\n";
  char* str = ",";
  //integer_array my_s;
  string_array* new_s;
  //my_s.array = array;
  //my_s.size = 7;

  new_s = my_csv_parser(array,str);


  
  printf("%s\n", new_s->array[0]);
  printf("%s\n", new_s->array[1]);
  //free(new_s->array);
  free(new_s);

  
  return 0;
}