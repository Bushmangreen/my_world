#include "my_header.h"

void list_filename(char* directory, char filename[5][100]){

	DIR *folder;
	struct dirent *entry;
	int i,j;
	int index = 0;
    int flag = 0;
	
    folder = opendir(directory);
	if(folder == NULL)
    {
        fprintf(stderr,"./my_ls: %s: No such file or directory \n",directory);
        exit(1);
    }

    while( (entry=readdir(folder)) )
    {
    	if (!strcmp(filename[index],entry->d_name)){
            printf("%s\n", filename[index]);
            index++;
            flag = 1;
        }
    }

    if (!flag) 
        fprintf(stderr,"./my_ls: %s: No such file or directory \n",filename[0]);;

}