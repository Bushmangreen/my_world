#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#define _POSIX_C_SOURCE 200809L

#define SHOW_HIDDEN 0
#define HIDE_HIDDEN 1
#define	CURRENT_DIRECTORY "."
#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

typedef struct {
	char *name;
	long long mod_time;
} my_struct;





void list_files_alphanum(){

	DIR *folder;
	struct dirent *entry;
	struct stat filestat;
	my_struct temp;
	my_struct file[80];
	int i,j;
	int index = 0;

	folder = opendir(CURRENT_DIRECTORY);

	if(folder == NULL)
    {
        puts("Unable to read directory");
        exit(1);
    }

 


    while( (entry=readdir(folder)) )
    {
    	stat(entry->d_name,&filestat);

    	if (entry->d_name[0] == '.' ) continue;
    	
    	file[index].name = entry->d_name;
    	file[index].mod_time = ( long long )filestat.st_mtime;
    	index++;
          
    }


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


void sort_files(int set_a,int set_t){

	DIR *folder;
	struct dirent *entry;
	struct stat filestat;
	my_struct temp;
	my_struct file[80];
	int i,j;
	int index = 0;

	folder = opendir(CURRENT_DIRECTORY);

	if(folder == NULL)
    {
        puts("Unable to read directory");
        exit(1);
    }

    while( (entry=readdir(folder)) )
    {
    	stat(entry->d_name,&filestat);

    	if (!set_a && entry->d_name[0] == '.' ) continue;
    	
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

void recurse_directories(char *directory, int set_a, int set_t)
{
    DIR *folder;
    struct dirent *entry;
    struct stat filestat;
    char pathname[PATH_MAX];
    /* Change to the named directory */
    if(chdir(directory))
    {
        fprintf(stderr,"Error changing to %s\n",directory);
        exit(1);
    }

    /* open the directory */
    folder = opendir(".");
    if(folder == NULL)
    {
        fprintf(stderr,"Unable to read directory %s\n",directory);
        exit(1);
    }

    //printf("%*s%s\n",depth*2," ",directory);
    getcwd(pathname,PATH_MAX);
	printf("%s:\n",pathname);
	sort_files(set_a, set_t);
    /* Look for a subdirectory */
    while( (entry=readdir(folder)) )
    {
        stat(entry->d_name,&filestat);
        /* look for only directories */
        if( S_ISDIR(filestat.st_mode) )
        {
            /* skip the . and .. entries */
            if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
                continue;
            /* recurse to the found directory */
            recurse_directories(entry->d_name,set_a,set_t);
        }
    }

    chdir("..");
    closedir(folder);
}

void list_requested(char* directory, int set_R, int set_a, int set_t){

	if (set_R) 	recurse_directories(directory, set_a, set_t);
	
	else 		sort_files(set_a, set_t);

	
}

int choice(int n,char** arr,int* R,int* a, int *t, char* direc){
	if (n == 1){
		return 1;
	}

	else {
		
	    for (int i = 0; i < n; i++){
	    	if (arr[i][0] == '-'){
	    		if (strchr(arr[i],'R')){
	    			*R = 1;
	    		}
	    		if (strchr(arr[i],'a')){
	    			*a = 1;
	    		}
	    		if (strchr(arr[i],'t')){
	    			*t = 1;
	    		}
	    	}

	    	if ( i>0 && arr[i][1] == '/'){
	    		strcpy(direc,arr[i]);
	    		break;
	    	}

	    }
	}
	return 0;
}





int main(int argc, char *argv[])
{

	int set_R = 0;
	int set_a = 0;
	int set_t = 0;
   	char directory[100] = CURRENT_DIRECTORY;

   	choice(argc,argv,&set_R,&set_a,&set_t, directory);

	list_requested(directory, set_R, set_a, set_t);

}









