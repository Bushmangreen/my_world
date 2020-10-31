#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "my_options.h"
#include "my_file.h"
#include "my_untar.h"
#include "my_fun.h"

t_my_file       *my_create_header(char *str)
{
  t_my_file	*my_file;
  int		i;

  if ((my_file = malloc(sizeof(*my_file))) == NULL)
    exit(EXIT_FAILURE);
  i = 0;
  i = my_fill_elt(str, my_file->name, 0, 100);
  i = my_fill_elt(str, my_file->mode, i, i + 8);
  i = my_fill_elt(str, my_file->uid, i, i + 8);
  i = my_fill_elt(str, my_file->gid, i, i + 8);
  i = my_fill_elt(str, my_file->size, i, i + 12);
  i = my_fill_elt(str, my_file->mtime, i, i + 12);
  i = my_fill_elt(str, my_file->chksum, i, i + 8);
  my_file->typeflag = str[i++];
  i = my_fill_elt(str, my_file->linkname, i, i + 100);
  i = my_fill_elt(str, my_file->magic, i, i + 6);
  i = my_fill_elt(str, my_file->version, i, i + 2);
  i = my_fill_elt(str, my_file->u_name, i, i + 32);
  i = my_fill_elt(str, my_file->g_name, i, i + 32);
  i = my_fill_elt(str, my_file->devmajor, i, i + 8);
  i = my_fill_elt(str, my_file->devminor, i, i + 8);
  i = my_fill_elt(str, my_file->prefix, i, i + 167);
  return (my_file);
}

void		my_createfile(int fd, t_my_file *my_file, char *opt)
{
  int		my_fd;
  char		buff[MAX_SIZE];
  int		nbr;
  int		len;
  mode_t	mode;
  uid_t		owner;
  gid_t		group;

  my_convert_elt(&mode, &owner, &group, my_file);
  if ((my_fd = open(my_file->name, O_WRONLY | O_CREAT, mode)) == -1 ||
      fchown(fd, owner, group) == -1)
    my_puterror(1, errno);
  nbr = oct_to_int(atoi(my_file->size));
  while (nbr > 0)
    {
      my_init_char(buff, MAX_SIZE);
      if ((len = read(fd, buff, MAX_SIZE < nbr ? MAX_SIZE : nbr)) == -1)
	my_puterror(1, errno);
      write(my_fd, buff, len);
      nbr -= len;
    }
  close(my_fd);
  if (opt[ID_VERBOSE])
    printf("%s\n", my_file->name);
}

void		my_createdir(t_my_file *my_file, char *opt)
{
  char		*my_path;
  int		i;
  int		j;
  mode_t	mode;

  if ((my_path = malloc(2 + my_strlen(my_file->prefix) +
			my_strlen(my_file->name))) == NULL)
    my_puterror(0, 0);
  mode = strtol(my_file->mode, NULL, 8);
  i = 0;
  j = 0;
  while (my_file->prefix[j])
    my_path[i++] = my_file->prefix[j++];
  j = 0;
  while (my_file->name[j])
    my_path[i++] = my_file->name[j++];
  my_path[i] = '\0';
  if ((mkdir(my_path, mode)) == -1)
    my_puterror(1, errno);
  if (opt[ID_VERBOSE])
    printf("%s\n", my_path);
  free(my_path);
}