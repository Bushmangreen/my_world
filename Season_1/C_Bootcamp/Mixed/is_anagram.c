#include <stdio.h>
#include <string.h>



int is_anagram(char* str1, char* str2) {


   int c = 0,x; 
   int count1[26] = {0};
   int count2[26] = {0};


  // printf("Enter a string\n");
  // gets(string);

   while (str1[c] != '\0') {
   /** Considering characters from 'a' to 'z' only and ignoring others. */

      if (str1[c] >= 'a' && str1[c] <= 'z') {
         x = str1[c] - 'a';
         count1[x]++;
      }

      c++;
   }
   c = 0;
   x = 0;
   while (str2[c] != '\0') {
   /** Considering characters from 'a' to 'z' only and ignoring others. */

      if (str2[c] >= 'a' && str2[c] <= 'z') {
         x = str2[c] - 'a';
         count2[x]++;
      }

      c++;
   }


   for (c = 0; c < 26; c++){
      if(count1[c] != count2[c]) return 0;
   }

   return 1;
}






int main()
{
   char str1[] = "aciman";
   char str2[] = "cmana"; 
   printf("%d\n", is_anagram(str1,str2));

   return 0;
}