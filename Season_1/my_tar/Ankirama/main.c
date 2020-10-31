

#include <stdio.h>
#include "my_tar.h"

int main(int argc, char *argv[])
{
 
    t_opt* opt = get_opt(argc,argv);

    // handle errors
    if ( opt->error == 1)
    {
        print_error();
        free(opt);
        return 1;
    }

    int fd_archive = open(argv[2], O_CREAT | O_APPEND |  O_WRONLY  , 0644);
    if ( fd_archive < 0)
    {
        printf("Error opening fd_archive\n");
        return 1;
    }
  
    printf("%d\n",argc);

    // create the archive: -cf 
    if( opt->c == 1 )
    {
        int i = 3; 
        while( i < argc)
        {   
            create_archive(fd_archive, argv[i++]);
        }
        end_of_archive(fd_archive);
    }


    // append to archive: -uf
    // if( opt->r == 1 )
    // {
    //     int i = 3;
    //     while( i <= argc)
    //     {   
    //         create_archive(fd_archive, argv[i++]);
    //     }
    //     end_of_archive(fd_archive);
    // }




    // while (i <= 4)
    
    // create_archive(fd_archive, argv[3]);

    // create_archive(fd_archive, argv[4]);
    
    // end_of_archive(fd_archive);

    free(opt);

    close(fd_archive);
    return 0;
}




/*
    
    print_opt(opt);
   
*/