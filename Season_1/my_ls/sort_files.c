#include "my_header.h"

void sort_files(char* directory,int set_a,int set_t, int set_R){

	DIR *folder;
	struct dirent *entry;
	struct stat filestat;
	my_struct temp;
	my_struct file[80];
	char pathname[PATH_MAX];
	int i,j;
	int index = 0;

	folder = opendir(directory);
	if(folder == NULL)
    {
        fprintf(stderr,"./my_ls: %s: No such file or directory \n",directory);
        exit(1);
    }
    closedir(folder);
    
	if(chdir(directory))
    {
        fprintf(stderr,"Error changing to %s\n",directory);
        exit(1);
    }

    



	folder = opendir(CURRENT_DIRECTORY);

	if(folder == NULL)
    {
        fprintf(stderr,"./my_ls: %s: No such file or directory \n",directory);
        exit(1);
    }
    getcwd(pathname,PATH_MAX);
    printf("%s:\n",pathname);
    while( (entry=readdir(folder)) )
    {
    	stat(entry->d_name,&filestat);

    	if (!set_a && entry->d_name[0] == '.' ) continue;
    	file[index].name = entry->d_name;
    	file[index].type = entry->d_type;
    	file[index].mod_time_sec = ( long long )filestat.st_mtimespec.tv_sec;
    	file[index].mod_time_nsec = ( long long )filestat.st_mtimespec.tv_nsec;
    	index++;
        
    }
		
	if(set_t)
	{
		for (i = 0; i < index - 1; i++)
	    {
	        for (j = 0; j < (index - 1-i); j++)
	        {
	            if (file[j].mod_time_sec < file[j + 1].mod_time_sec)
	            {
	                temp = file[j];
	                file[j] = file[j + 1];
	                file[j + 1] = temp;
	            } 
	            else if ((file[j].mod_time_sec == file[j + 1].mod_time_sec) && (file[j].mod_time_nsec < file[j + 1].mod_time_nsec))
				{
		            	temp = file[j];
		                file[j] = file[j + 1];
		                file[j + 1] = temp;
		        }    

		        else if ((file[j].mod_time_sec == file[j + 1].mod_time_sec) && (file[j].mod_time_nsec == file[j + 1].mod_time_nsec))
		        {
		            if (strcmp(file[j].name,file[j + 1].name) > 0)
		            	{
			                temp = file[j];
			                file[j] = file[j + 1];
			                file[j + 1] = temp;
		            	} 
	       		}
	    	}
	    }
	    for (i = 0; i < index; i++)
	    {
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
	    	printf("%s\n",file[i].name);
	    }
	}
	
	 // we can pass file names to recursive function
	if (set_R){
	    for (int i = 0; i < index; i++)
	    {
	        if( file[i].type == 4 )
	        {
	            if(strcmp(file[i].name,".")==0 || strcmp(file[i].name,"..")==0)
	                continue;
	            sort_files(file[i].name,set_a,set_t, set_R);
	           
	        }
	    }
	    chdir("..");
	}
 	if (!set_R) chdir("..");

	closedir(folder);

}