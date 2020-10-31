#ifndef MY_FILE_H_
# define MY_FILE_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct  s_my_file
{
  char    name[100];
  char    mode[8];
  char    uid[8];
  char    gid[8];
  char    size[12];
  char    mtime[12];
  char    chksum[8];
  char    typeflag;
  char    linkname[100];
  char    magic[6];
  char    version[3];
  char    u_name[32];
  char    g_name[32];
  char    devmajor[8];
  char    devminor[8];
  char    prefix[167];
}   t_my_file;

void    my_init_char(char *str, int size);
t_my_file *my_fill_struct(struct stat *buf, char *name);
void    my_display_all(t_my_file *my_file, FILE *file);

#endif /* !MY_FILE_H_ */