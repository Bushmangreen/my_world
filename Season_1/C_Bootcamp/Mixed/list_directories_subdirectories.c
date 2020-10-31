
#include "my_header.h"

void list_directories_subdirectories(char *directory,char *parent)
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

    /* fetch the current directory for output, but also for
       the recursive call later */
    getcwd(pathname,PATH_MAX);
    printf("%s\n",pathname);

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
            list_directories_subdirectories(entry->d_name,pathname);
        }
    }

    closedir(folder);
    chdir(parent);
}
