#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "my_file.h"
#include "my_append.h"
#include "my_append_nbr.h"

void	my_init_char(char *str, int size)
{
  int		i;

  i = 0;
  while (i < size)
    {
      str[i] = '\0';
      i += 1;
    }
}

static void	my_init_nbr(char *str, int size)
{
  int		i;

  i = 0;
  while (i < size - 1)
    {
      str[i] = '0';
      i += 1;
    }
  str[i] = '\0';
}

static t_my_file	*my_init_file()
{
  t_my_file		*my_file;

  if ((my_file = malloc(sizeof(*my_file))) == NULL)
    exit(EXIT_FAILURE);
  my_init_char(my_file->name, 100);
  my_init_nbr(my_file->mode, 8);
  my_init_nbr(my_file->uid, 8);
  my_init_nbr(my_file->gid, 8);
  my_init_nbr(my_file->size, 12);
  my_init_nbr(my_file->mtime, 12);
  my_init_nbr(my_file->chksum, 8);
  my_file->typeflag = '0';
  my_init_char(my_file->linkname, 100);
  my_init_char(my_file->magic, 6);
  my_init_nbr(my_file->version, 2);
  my_init_char(my_file->u_name, 32);
  my_init_char(my_file->g_name, 32);
  my_init_nbr(my_file->devmajor, 8);
  my_init_nbr(my_file->devminor, 8);
  my_init_char(my_file->prefix, 167);
  return (my_file);
}

t_my_file	*my_fill_struct(struct stat *buf, char *name)
{
  t_my_file	*my_file;

  my_file = my_init_file();
  my_append_data(my_file->name, name);
  my_append_octal(my_file->mode, buf->st_mode, 8);
  my_file->mode[1] = '0';
  my_append_octal(my_file->uid, buf->st_uid, 8);
  my_append_octal(my_file->gid, buf->st_gid, 8);
  my_append_octal(my_file->size, buf->st_size, 12);
  my_append_octal(my_file->mtime, buf->st_mtime, 12);
  my_file->typeflag = my_type_file(buf);
  my_append_link(my_file->linkname, name, buf);
  my_append_int(my_file->version, 0, 3);
  my_append_data(my_file->magic, "ustar");
  my_append_uid(my_file->u_name, buf, 0);
  my_append_uid(my_file->g_name, buf, 1);
  my_append_dev(my_file->devmajor, major(buf->st_dev), 8, buf->st_mode);
  my_append_dev(my_file->devminor, minor(buf->st_dev), 8, buf->st_mode);
  my_append_data(my_file->prefix, "\0");
  my_append_chksum(my_file->chksum, my_file, 0);
  return (my_file);
}

void	my_display_all(t_my_file *my_file, FILE *file)
{
  char	str[256];
  char	*check;

  printf(my_file->name);
  printf(my_file->mode);
  printf(my_file->uid);
  printf(my_file->gid);
  printf(my_file->size);
  printf(my_file->mtime);
  printf(my_file->chksum);
  printf("%c", my_file->typeflag);
  printf(my_file->linkname);
  printf(my_file->magic);
  printf(my_file->version);
  printf(my_file->u_name);
  printf(my_file->g_name);
  printf(my_file->devmajor);
  printf(my_file->devminor);
  printf(my_file->prefix);
  while ((check = fgets(str, 256, file)) != NULL)
    printf("%s", str);
  if (check == NULL && errno != 0 && errno != EISDIR)
    my_puterror(1, errno);
}