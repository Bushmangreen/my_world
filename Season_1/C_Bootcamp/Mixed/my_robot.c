#include <stdio.h>    



int main(){

    char direction = 'N'; // set initial orientation
    int x = 0;
    int y = 0;
    char *a = "RAARA";
    char *dir;
    char string[40] = {'\n'};
        while (*a){
        if (*a == 'L'){
            if (direction == 'N') direction = 'W';
            else if (direction == 'W') direction = 'S';
            else if (direction == 'S') direction = 'E';
            else if (direction == 'E') direction = 'N';
        }else if (*a == 'R'){
            if (direction == 'N') direction = 'E';
            else if (direction == 'E') direction = 'S';
            else if (direction == 'S') direction = 'W';
            else if (direction == 'W') direction = 'N';
        }else {
            if (direction == 'N') y--;
            else if (direction == 'S') y++;
            else if (direction == 'E') x++;
            else x--;
        }

        a++;



    }


    //printf("%d\n",x);
    //printf("%d\n",y);
    //printf("%c\n",direction);
    
    sprintf ( string, "x: %d, y: %d, bearing: %s", x, y, direction );
    printf("%s\n",string);
}