#include <stdio.h>


int main() {
    int n = 9;
    int layers=3;
  


        for (int i = 4; i <=n; ++i) {

            for (int j = i; j < n; ++j)
                printf(" ");

            for (int k = 0; k < i; ++k)
                printf("*");

            for (int k = 1; k < i; ++k)
               printf("*");

            printf("\n");
        }
      
    
    

    return 0;
}
