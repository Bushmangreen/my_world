#include <stdio.h>

char* reverse_string(char* a) {
    int l=0,i;
    char *begin_ptr, *end_ptr, ch, *adrs;
    adrs = a;
    begin_ptr = a; 
     
    
    while(*a){
        l++;
        a++;
        
    }
    if (l<2) return a;
    l--;
    a--;
    //printf("it is printed %c\n",a[0]);
    //printf("%c\n",a[l]);
    end_ptr = a;
    
     for (i = 0; i < l/2+1 ; i++) { 
  
        // swap character 
        ch = *end_ptr; 
        *end_ptr = *begin_ptr; 
        *begin_ptr = ch; 
        //printf("%s\n",begin_ptr);
        // update pointers positions 
        begin_ptr++; 
        end_ptr--; 
    } 
    begin_ptr--;

    return adrs;
}




int my_strcmp(const char *s1, const char *s2) {
  // All compares done as if `char` was `unsigned char`
  const unsigned char *us1 = (const unsigned char *) s1;
  const unsigned char *us2 = (const unsigned char *) s2;

  // As long as the data is the same and '\0' not found, iterate
  while (*us1 == *us2 && *us1 != '\0') {
    us1++;
    us2++;
  }

  // Use compares to avoid any mathematical overflow 
  // (possible when `unsigned char` and `unsigned` have the same range).
  return (*us1 > *us2) - (*us1 < *us2);
}

int main(){

    char x[4] ="abc";
    char y[3] = "abc";
    printf("%d\n",my_strcmp("abc","abc"));
    // abc bd
    // bd abc
    //abc abc


}