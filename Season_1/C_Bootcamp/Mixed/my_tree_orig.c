#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){

    const char *spaces="                                                                                                               "; 
    const char *stars ="***************************************************************************************************************";
    const char *dashes="||||||||||||||||||||||||||||||||||||||||||";
    int row;
    int layers = atoi(argv[1]); // intput from argv
    int n = 3+layers;
    int cur_layer;
    int sub_layer = 4;
    int t = 0;
    int last_row = n*(n+1)/2-6;
    int trunk;
    

    int max_stars;
    if (layers<2){
        max_stars = (2*last_row-1)/2;
        trunk = (2*last_row-1)/2;
    }else if(layers>3){
        max_stars = (2*last_row-6*layers+9)/2;
        trunk = (2*last_row-6*layers+9)/2; 
    }
    else if(layers>5){
        max_stars = (2*last_row-8*layers+9)/2;
        trunk = (2*last_row-8*layers+9)/2; 
    
    }
    else {
        max_stars = (2*(last_row-(2*layers-2))-1)/2;
        trunk = (2*(last_row-(2*layers-2))-1)/2;
    }

    cur_layer = 1;
    for (int i = 1; i<= layers; i++){

        for (row = cur_layer; row <= sub_layer; row++){
    
            printf("%.*s%.*s\n", max_stars,spaces, (2*(row-t)-1), stars);
            if (row == sub_layer) continue;

            max_stars --;                   
        }
        if (i>=3 && layers >=3){
            if (row == sub_layer) max_stars ++;max_stars++;
        }
        if (i>=5 && layers >=5){
            if (row == sub_layer) max_stars ++;max_stars++;
        }

        cur_layer = sub_layer + 1;
        sub_layer = 4 + i + sub_layer;
        max_stars += 1;

        if (i>=3 && layers>=3) t += 3;
        else t += 2;

        if (i>=5 && layers>=5) t++;
        

        
    }  

    for (int i = 1; i <= layers; i++){    
    
        printf("%.*s%.*s\n", trunk - ((layers%2)==0?layers/2-1:layers/2),spaces, layers, dashes);
    }

    return 0;
}

