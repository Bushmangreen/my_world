#include <stdio.h>
//Input: "Baby" && "Yoda" && 50
//Output: "Hello, my name is Baby Yoda, I'm 50."
/*
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}
*/

char *my_string_formatting(char *name, char *surname,int c){
  
    char sentence[100] = "Hello, my name is ";
    char filler[] =", I'am ";
    char space[1] =" "; 
    char dot[1]="."; 
    int i=0;
    int j=0;
   	char *final;
   while (*name){
   	sentence[i+18] = *name; 
    name++;
    i++; 
  
   }
   sentence[i+18] = space[0];
   i++;

   while (*surname){
	 sentence[i+18] = *surname; 
	 surname++;
	 i++; 
  	printf("%s\n", sentence);
   }

   j=0;
   
   while (filler[j]!='\0'){
   	sentence[i+18] = filler[j]; 
    name++;
    i++; 
  	j++;
  	
   }

  
   int rem;
   char str[10];
   j=0;
   int len = 0;
   int n =0;
   n = c;
    while (n != 0)
    {
        len++;
        n /= 10;
    }

   for (int j = 0; j < len; j++)


   {
        rem = c % 10;
        c = c / 10;
        str[len - (j + 1)] = rem + '0';
   }
   str[len] = '\0';

   j=0;
   while (str[j]!='\0'){
   	sentence[i+18] = str[j]; 
    i++; 
  	j++;
   }
  
   sentence[i+18] = '\0';



   /*
   while(*name){
   	sentence[i]=dot[j];
	j++;
	i++;

	}

	while(*surname){

   	*sentence=*surname;
	surname++;
	sentence++;

	}

	while(*filler){

   	*sentence=*filler;
	filler++;
	sentence++;

	}

	*sentence = c;
	sentence++;
	*sentence = *dot;

	
   *sentence = '\0';
   */
   printf("%s\n", sentence);
   i=0;
   while (sentence[i]!='\0'){
	 *final = sentence[i]; 
	 i++; 
	 final++;
  	printf("%s\n", sentence);
   }
  

   return final;

}

int main(){

	
	printf("%s\n",my_string_formatting("ad","abi",100));

	return 0;

}


