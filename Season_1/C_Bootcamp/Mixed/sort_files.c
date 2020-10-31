#include "my_header.h"

void sort_files(char* directory,int set_a,int set_t){

	DIR *folder;
	struct dirent *entry;
	struct stat filestat;
	my_struct temp;
	my_struct file[80];
	int i,j;
	int index = 0;

	folder = opendir(directory);

	if(folder == NULL)
    {
        puts("Unable to read directory");
        exit(1);
    }

    while( (entry=readdir(folder)) )
    {
    	stat(entry->d_name,&filestat);

    	if (!set_a && entry->d_name[0] == '.' ) continue;
    	printf("%d\n", set_a);
    	file[index].name = entry->d_name;
    	file[index].mod_time = ( long long )filestat.st_mtime;
    	index++;
          
    }
		
	if(set_t)
	{
		for (i = 0; i < index - 1; i++)
	    {
	        for (j = 0; j < (index - 1-i); j++)
	        {
	            if (file[j].mod_time < file[j + 1].mod_time)
	            {
	                temp = file[j];
	                file[j] = file[j + 1];
	                file[j + 1] = temp;
	            } 
	        }
	    }

	    for (i = 0; i < index; i++){
	    	printf("%s\n",file[i].name );
	    }
	}
	else 
	{
		for (i = 0; i < index - 1; i++)
    		{	
		        for (j = 0; j < (index - 1-i); j++)
		        {
		            if (strcmp(file[j].name,file[j + 1].name) > 0)
		            {
		                temp = file[j];
		                file[j] = file[j + 1];
		                file[j + 1] = temp;
		            } 
		        }
    		}

	    for (i = 0; i < index; i++){
	    	printf("%s\n",file[i].name );
	    }
	}




}