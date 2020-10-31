#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include "my_fun.h"
#include "my_file.h"

/*
** Will add data into our struct
*/
void	my_append_data(char *str, char *data)
{
  int	i;

  i = 0;
  while (data != NULL && data[i])
  {
    str[i] = data[i];
    i++;
  }
}

/*
** Will create the checksum
*/
void	my_append_chksum(char *str, t_my_file *file, int tot)
{
  char	tmp[6];

  tot += my_add(file->name);
  tot += my_add(file->mode);
  tot += my_add(file->uid);
  tot += my_add(file->gid);
  tot += my_add(file->size);
  tot += my_add(file->mtime);
  tot += my_add("        ");
  tot += file->typeflag;
  tot += my_add(file->linkname);
  tot += my_add(file->magic);
  tot += my_add(file->version);
  tot += my_add(file->u_name);
  tot += my_add(file->g_name);
  tot += my_add(file->devmajor);
  tot += my_add(file->devminor);
  tot += my_add(file->prefix);
  sprintf(tmp, "%o", tot);
  my_checksum(str, tmp);
}

/*
** Will append a link in linkname if the current file (str) is a link
*/
void	my_append_link(char *my_link, char *str, struct stat *buf)
{
  char	*link;
  int	len;

  if ((link = malloc(sizeof(char) * 256)) == NULL)
    exit(EXIT_FAILURE);
  if (S_ISLNK(buf->st_mode))
    {
      if ((len = readlink(str, link, 256 * sizeof(char))) < 0)
	{
	  printf("%m\n");
	  exit(EXIT_FAILURE);
	}
      else
	link[len] = '\0';
      my_append_data(my_link, link);
    }
}

/*
** type = 0 --> uid
** type = 1 --> gid
*/
void		my_append_uid(char *str, struct stat *buf, char type)
{
  struct passwd	*pwd;
  struct group	*grp;
  char		*tmp;
  int		i;

  if (type == 0)
    {
      pwd = getpwuid(buf->st_uid);
      tmp = pwd->pw_name;
    }
  else
    {
      grp = getgrgid(buf->st_gid);
      tmp = grp->gr_name;
    }
  i = 0;
  while (tmp[i])
  {
    str[i] = tmp[i];
    i++;
  }
}

char	my_type_file(struct stat *buf)
{
  char	c;
  if (S_ISREG(buf->st_mode))
    c = '0';
  else if (S_ISLNK(buf->st_mode))
    c = '2';
  else if (S_ISCHR(buf->st_mode))
    c = '3';
  else if (S_ISBLK(buf->st_mode))
    c = '4';
  else if (S_ISDIR(buf->st_mode))
    c = '5';
  else if (S_ISFIFO(buf->st_mode))
    c = '6';
  else if (S_ISSOCK(buf->st_mode))
    c = '7';
  return (c);
}