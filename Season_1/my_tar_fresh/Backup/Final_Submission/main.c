


#include "my_tar.h"

int main(int argc, char *argv[])
{ 
    t_opt* opt = get_opt(argc, argv);

    // handle errors
    if ( opt->error == 1)
    {
        print_error();
        free(opt);
        return 1;
    }
    
    //print parsed arguments
    //print_opt(opt, argc, argv);

    // If  -c is set and arguments are 3 ".tar" is not present
    //we will print to stdout
    if ( argc >= 3 && opt->c && (str_search(argv[2], ".tar") == 0))
    {   
        int i = 2;
        while (i < argc)
        { 
            create_archive( 1, argv[i++],opt);
            end_of_archive(1);
        }
        free(opt);
        return 0;
    }

    int fd_archive = open(argv[2], open_flags(opt) , 0644);
    if ( fd_archive < 0)
    {
        printf("Error opening fd_archive\n");
        free(opt);
        return 1;
    }

    // create the archive: -cf and append to archive: -rf
    if( opt->c == 1 || opt->r == 1 )
    {
        int i = 3; 
        while( i < argc)
        {              
            create_archive(fd_archive, argv[i++], opt);
        }
        end_of_archive(fd_archive);
    }


    // append if mode is less: -uf 
    if( opt->u == 1 )
    {
        int flag = 0;
        list_mtime(argv[2], argv[3], &flag);
        if (flag)
        {
            create_archive(fd_archive, argv[3], opt);
            end_of_archive(fd_archive);
        }
        
    }
    close(fd_archive);

    // READING PARTS

    // list archive -tf?
    if( opt->t == 1 )
    {
        list_archive(argv[2]);
    }

    //extract archive
    if( opt->x == 1 )
    {
        extract_archive(argv[2]);
    }



   
    free(opt);

    close(fd_archive);
    return 0;
}