
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *const argv[]) {

//int COLS;
//int ROWS;
  // print out the argv strings:
for(int i=0; i < argc; i++) {
    printf("Command line arg %2d: %s\n", i, argv[i]);
}
    printf("\n");

if(argc != 3 ) {
   // printf("usage: ./prog name age id_num gpa\n");
    exit(1);
  }
  
//
//
//if (argv[1] != NULL)  COLS = atoi(argv[1]);
//if (argv[1] != NULL)  ROWS =  atoi(argv[2]);
//else ROWS =0;
int COLS  = strtol(argv[1], NULL, 10);
int ROWS  = strtol(argv[2], NULL, 10);
//if (argv < 3) _error_exit();
//int COLS = atoi(argv[1]);
//int ROWS =  atoi(argv[2]);


for(int i=0; i < ROWS; i++) {
    for(int j=0; j < COLS; j++) {
        if (i == 0 || i == ROWS - 1) {
            if (((i == 0) && (j == 0)) || ((j == (COLS-1)) && (i == (ROWS-1))) || (i==0 && (j==(COLS-1))) || ((i==(ROWS -1)) && j==0))
                printf("o");
            else 
                printf("-");
        }
        else if(j == 0 || j == COLS -1) {
            printf("|");
        }
        else {
            printf(" ");
        }
        //printf(" ");
    }
    printf("\n");
}



return 0;

}



  
