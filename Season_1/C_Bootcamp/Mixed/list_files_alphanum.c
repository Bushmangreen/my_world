#include "my_header.h"

void list_files_alphanum(char* directory, int yes)
{
    struct dirent **namelist;
   
    int n = scandir(directory,&namelist,NULL,alphasort);

    if(n < 0)
    {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {  
            if (yes);
            else if (strcmp(namelist[i]->d_name,".")==0 || *namelist[i]->d_name=='.') continue; // simple ls, skips the '.' and '..'
            printf("%s\n",namelist[i]->d_name);
            free(namelist[i]);
        }
        free(namelist);
    }
    
}