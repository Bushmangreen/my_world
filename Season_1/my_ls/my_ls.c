
#include "my_header.h"

int main(int argc, char *argv[])
{

	int set_R = 0;
	int set_a = 0;
	int set_t = 0;
	
	int dir_flag = 0;
	int file_flag = 0;
   	char directories[5][100] = {CURRENT_DIRECTORY,'\0','\0','\0','\0'};
   	char filename[5][100];

   	choice(argc,argv,&set_a,&set_t,&set_R, directories, filename, &dir_flag, &file_flag);

   	if (file_flag)
   		list_filename(directories[0], filename);

   	if (dir_flag || !file_flag)
   	{
	   	for(int i = 0; i < 5 && strcmp(directories[i],"\0"); i++)
	   	{
			sort_files(directories[i], set_a, set_t, set_R);
		}
	}

	return 0;
}


