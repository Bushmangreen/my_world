#include <stdio.h> 

char* itoa(int num)

{
    int length; 
    int rem;
    int num_copy=num;

    //get the number of digits

    while(num_copy != 0)
    {
        length++;
        num_copy /=10;
    }

    //char* string = malloc(length);
    char* string;
    for (int i = length-1; i >= 0; i--)
    {

        rem = num % 10;
        num /= 10;

        string[i] = rem + '0';
    }
    string[length] = '\0';

    

    return string;
}

int power(int a, int b) 
{ 
  //base case : anything raised to the power 0 is 1 
  if (b == 0) 
    return 1; 
  int answer = a; 
  int increment = a; 
  int i, j; 
  for(i = 1; i < b; i++) 
  { 
     for(j = 1; j < a; j++) 
     { 
        answer += increment; 
     } 
     increment = answer; 
  } 
  return answer; 
} 

int main(int argc, char const *argv[])

{
    int position = 0;
    int temp = 123;
    int original = 123;
    int multiple;
    int num = 123;
    char arr[10];
    int index = 0;
    
    while( num != 0 ) 
    {
        position++;
        num = num / 10;
    }
    
 

    for (int i = position-1; i >= 0; i--)
    {
        
        multiple = power(10, i);
        temp = temp / multiple;
        num = temp;
        temp = original%multiple;
        if (i == 0)
        {
            if (num>=1 && num <10)
            {
                if (num >= 1 && num <= 3)
                {
                    while (num)
                    {
                        arr[index++] = 'I';
                        num--;

                    }
                    
                }
                else if (num == 4)
                {
                    arr[index++] = 'I';
                    arr[index++] = 'V';
                    
                }
                else if (num == 5)
                {
                    arr[index++] ='V';
                    
                }
                else if (num >5 && num < 9)
                {
                    arr[index++] ='V';
                    while (num-5)
                    {
                        arr[index++] = 'I';
                        num--;
                    }
                    putchar('\n');
                    
                }
                else if (num == 9)
                {
                    arr[index++] ='I';
                    arr[index++] ='X';
                }
            }
        }
        
    /////////////////////////////////
        if(i == 1)
        {
            if (num>=1 && num <10)
            {
                if (num >= 1 && num <= 3)
                {
                    while (num)
                    {
                        arr[index++] ='X';
                        num--;

                    }
                }
                else if (num == 4)
                {
                    arr[index++] ='X';
                    arr[index++] ='L';
                }
                else if (num == 5)
                {
                    arr[index++] ='L';
                }
                else if (num >5 && num < 9)
                {
                    arr[index++] ='L';
                    while (num-5)
                    {
                        arr[index++] ='X';
                        num--;
                    }
                    
                }
                else if (num == 9 )
                {
                    arr[index++] ='X';
                    arr[index++] ='C';
                    
                }
            }
        }
        
    ///////////////////////////////////////////////
        if (i == 2)
        {
            if (num>=1 && num <10)
            {
                if (num >= 1 && num <= 3)
                {
                    while (num)
                    {
                        arr[index++] ='C';
                        num--;

                    }
                    
                }
                else if (num == 4)
                {
                    arr[index++] ='C';
                    arr[index++] ='D';
                }
                else if (num == 5)
                {
                    arr[index++] ='D';
                }
                else if (num >5 && num < 9)
                {
                    arr[index++] = 'D';
                    while (num-5)
                    {
                        arr[index++] = 'C';
                        num--;
                    }
                    
                    
                }
                else if (num == 9)
                {
                    arr[index++] = 'C';
                    arr[index++] = 'M';
                    
                }
            }    
            
        }

        if (i == 3 )
        {
            if (num >= 1 && num <= 3)
                {
                    while (num)
                    {
                        arr[index++] = 'M';
                        num--;

                    }
                }
        }
    }
    arr[index] = '\0';
    printf("%s\n", arr);
    return 0;
}
