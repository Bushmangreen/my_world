#include <stdio.h>

char* my_capitalize(char *str)
{
   char *temp;
   char *lastSpace;
   temp = str;
   while(*str)

   {
      if(*str<91&&*str>64) *str=*str+32;
      if (*str > 96) lastSpace = str;
         
      //printf("\n The Lowercase letter is %s\n", str);   
      str++;
      
   
   }

   str = temp;

   while(*str)
   {
      if (*str > 96) {
         lastSpace = str;
         break;
      }
         str++;

   }
   //str=temp;
   str = lastSpace;
   *str = *str - 32;
    str = temp;

  

   printf("\n The Lowercase letter is %s\n", str);
return str;
}


int main()
{
   char ch[60]="      asdfqQASDbcE Fgef ";
   //char  *gets= my_upcase(ch);
   printf("\n The Lowercase string is %s\n", my_capitalize(ch));
   return 0;
}
   

