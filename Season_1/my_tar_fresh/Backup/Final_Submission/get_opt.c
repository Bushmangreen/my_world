



#include "my_tar.h"

int is_option(char* str)
{
    if (str[0] == '-')
        return 1;
    return 0;
}
int print_error(void)
{
    printf("Ups... Error, might be one of the following:\n");
    printf("List:       tar -t <archive-filename>\n");
    printf("Extract:    tar -xf <archive-filename>\n");
    printf("Uppend:     tar -rf <archive-filename>\n");
    printf("Create:     tar -cf <archive-filename> [filenames...]\n");
    printf("Missing -f option\n");

    return 0;
}
int str_search(char* str, char* search)
{
    int flag,count1 = 0, count2 = 0;

  
    while (str[count1] != '\0')
        count1++;
    while (search[count2] != '\0')
        count2++;
    for (int i = 0; i <= count1 - count2; i++)
    {
        for (int j = i; j < i + count2; j++)
        {
            flag = 1;
            if (str[j] != search[j - i])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            break;
    }

        
   
        
    return flag;
}
int check_errors(int argc, char* argv[], t_opt* opt)
{
    //no option selected
    if ( !opt->c && !opt->x && !opt->r && !opt->u && !opt->t)
    {
        opt->error = 1;
    }
    
    //missing f: tf,xf, cf
    if( opt->t && !opt->f)
    {
        opt->error = 1;   
    }

    if( opt->x && !opt->f)
    {
        opt->error = 1;
    }
// check the substring for .tar
    if( opt->c && argc >= 3 && !opt->f && (str_search(argv[2], ".tar") == 1))
    {
        opt->error = 1;
    }
    
    if ( opt->c &&  ((str_search(argv[2], ".tar") == 1)) && argc < 4 )
    {
        opt->error = 1;
    }
    
    if (opt -> c && argc == 3 && opt -> f)
    {
            opt->error = 1;
    }
    // ct cr cx cu, missing files
    if( opt->c && opt->t)
    {
        opt->error = 1;
    }

    if( opt->c && opt->r)
    {
        opt->error = 1;
    }

    if( opt->c && opt->u)
    {
        opt->error = 1;
    }

    if( opt->c && opt->x)
    {
        opt->error = 1;
    }
    

    // tr, tx, tu
    if( opt->t && opt->r)
    {
        opt->error = 1;
    }

    if( opt->t && opt->u)
    {
        opt->error = 1;
    }
   
    if( opt->t && opt->x)
    {
        opt->error = 1;
    }

    // rx, ru, rf
    if( opt->r && opt->x)
    {
        opt->error = 1;
    }   
    
    if( opt->r && opt->u)
    {
        opt->error = 1;
    }

    if( opt->r && !opt->f )
    {
       opt->error = 1;
    }
    
    if ( opt->r && (argc < 4 || (str_search(argv[2], ".tar") == 0)))
    {
        opt->error = 1;
    }

    // uf 
    if( opt->u && !opt->f )
    {
       opt->error = 1;
    }   
    
    // 2 arguments given only
    if (argc<3)
    {
        opt->error = 1;
    }

    return 0;
}

t_opt* init_opt()
{
    t_opt* opt = (t_opt*)malloc(sizeof(t_opt));
    opt->c = 0;
    opt->f = 0;
    opt->r = 0;
    opt->t = 0;
    opt->u = 0;
    opt->x = 0; 
    opt->error = 0; 
    return opt;
}

void set_option(t_opt* opt, char* str)
{
    int index = 0;
    while (str[index] != '\0')
    {   
        if (str[index] == 'c')
        {
            opt->c = 1;
        }
        if (str[index] == 'f')
        {
            opt->f = 1;
        }
        if (str[index] == 'r')
        {
            opt->r = 1;
        }
        if (str[index] == 't')
        {
            opt->t = 1;
        }
        if (str[index] == 'u')
        {
            opt->u = 1;
        }
        if (str[index] == 'x')
        {
            opt->x = 1;
        }
        index++;
    }
   
}

t_opt* get_opt(int argc, char *argv[])
{
    t_opt* opt = init_opt();
    int index = 0;

    while(index < argc)
    {
        if (is_option(argv[index]) == 1)
        {
           
            set_option(opt, argv[index]+1);
        }
        index++;
    }

    check_errors(argc, argv, opt);
    return opt;
}