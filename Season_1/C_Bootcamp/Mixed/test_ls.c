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



int count_files(char* path, int hidden){

	DIR *folder;
	struct dirent *entry;
	int counter = 0;

	folder = opendir(path);

    if(folder == NULL)
    {
        puts("Unable to read directory");
        return(1);
    }

	while( (entry=readdir(folder)) )
    {
    
    	if (hidden && entry->d_name[0] == '.' ) continue;
    	counter++;
           
    }

    closedir(folder);
    
    return counter;
}

static int compare_names(const void* a, const void* b) 
{ 
  
    // setting up rules for comparison 
    return strcmp(*(const char**)a, *(const char**)b); 
} 

static int compare_mtime(const void* a, const void* b) 
{ 
  
    // setting up rules for comparison 
    return strcmp(*(const char**)a, *(const char**)b); 
} 
// Function to sort the array 
void sort_names( char* arr[], int n) 
{ 
    // calling qsort function to sort the array 
    // with the help of Comparator 
    qsort(arr, n, sizeof(const char*), compare_names); 
} 

void print_sorted_files(char* directory, int hide_some){
    
    DIR *folder;
    struct dirent *entry;
  
    int total_number_of_files,index=0;
  
    total_number_of_files = count_files(directory, hide_some);
	char *array_of_file_names[total_number_of_files];
    

	folder = opendir(directory);

    if(folder == NULL)
    {
        puts("Unable to read directory");
        exit(1);
    }

    //writing all files to array_of_files 
	while( (entry=readdir(folder)) )
    {
    	if ( hide_some && entry->d_name[0] == '.' ) continue;
    	array_of_file_names[index++] = entry->d_name; 
    	      
    }


    sort_names(array_of_file_names, total_number_of_files);

    for (int i = 0; i < total_number_of_files; ++i)
    {
    	printf("%s\n",array_of_file_names[i] );
    }

    closedir(folder); 
}


int compare_mtime( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

qsort( a, 6, sizeof(int), compare )

int main() {
 
    DIR *folder;
    struct dirent *entry;
    struct stat filestat;
    char cwdpath[256];
    int count = 1;
    long long total = 0;
    int index=0;

    int arr_length  = count_files(CURRENT_DIRECTORY,SHOW_HIDDEN);
    long long mtime_array[arr_length];

    folder = opendir(".");
    if(folder == NULL)
    {
        perror("Unable to read directory");
        return(0);
    }

    /* State directory name 
    getcwd(cwdpath,256);
    printf("Directory of %s\n\n",cwdpath);
	*/

    /* Read directory entries */
    while( (entry=readdir(folder)) )
    {
        /* Extract Filename */
        stat(entry->d_name,&filestat);
        //printf("%-16s",entry->d_name);

        /* Extract create date and time */
       // unsigned long mtime = ctime(&filestat.st_mtime);
        
        //printf("lld\n",test);
        //printf("%s",ctime(&filestat.st_mtime));
        mtime_array [index++] = ( long long )filestat.st_mtime;
        
       	
    }
  		printf("%llu\n",mtime_array[0]); 





    closedir(folder);
    return 0;
}





/*
int compare_mtime(time_t t1, time_t t2) {
 
  if (t1 < t2) return MODIFIED_EARLIER;
 
  if (t1 > t2) return MODIFIED_LATER;
 
  return MODIFIED_SAME;
}
 
//...
 
struct stat s1, s2;
 
// do a 'stat()'
 
int result = compare_mtime(s1.st_mtime,s2.st_mtime);
	  
 



char** myFunction() {

	int total = count_files(CURRENT_DIRECTORY,SHOW_HIDDEN);
    char ** sub_str = malloc(total * sizeof(char*));
    for (int i =0 ; i < total; ++i)
        sub_str[i] = malloc(50 * sizeof(char));
    
    return sub_str;
}

char** str = myFunction();


void free_strings ( char ** str_array, int number_of_strings )
{
    int i;

    for ( i = 0; i < number_of_strings; i ++ )
    {
        //Should be checking to see if this is a null pointer.
        free ( str_array [ i ] );
    }

    //Once the strings themselves are freed, free the actual array itself.
    free ( str_array );
}
*/
