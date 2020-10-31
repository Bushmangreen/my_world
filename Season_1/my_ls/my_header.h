#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#define _POSIX_C_SOURCE 200809L

#define	CURRENT_DIRECTORY "."
#ifndef PATH_MAX
#define PATH_MAX 1024
#endif


typedef struct {
	char *name;
	int type;
	long long mod_time_sec;
	long long mod_time_nsec;
	
} my_struct;


int choice(int n,char** arr,int* a,int* t, int *R, char direc[5][100],char filename[5][100], int* dir_flag, int* file_flag);
void sort_files(char* directory, int set_a, int set_t, int set_R);
void list_filename(char* directory, char filename[5][100]);