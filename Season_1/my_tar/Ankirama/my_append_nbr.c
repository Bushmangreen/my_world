#include <stdio.h>
#include "my_file.h"
#include "my_fun.h"

void	my_append_octal(char *str, int oct, int size)
{
  int	i;
  int	j;
  char	tmp[12];

  my_init_char(tmp, 12);
  sprintf(tmp, "%o", oct);
  i = 0;
  while (i < size - my_strlen(tmp) - 1)
    str[i++] = '0';
  j = 0;
  while (i < size)
    str[i++] = tmp[j++];
}

void	my_append_int(char *str, int nbr, int size)
{
  int	i;
  int	j;
  char	tmp[12];

  my_init_char(tmp, 12);
  if (nbr != 0)
    sprintf(tmp, "%d", nbr);
  i = 0;
  while (i < size - my_strlen(tmp) - 1)
    str[i++] = '0';
  j = 0;
  while (i < size)
    str[i++] = tmp[j++];
  str[i] = '\0';
  }

void	my_append_dev(char *str, int nbr, int size, mode_t st_mode)
{
  int	i;
  int	j;
  char	tmp[12];

  my_init_char(tmp, 12);
  if (S_ISCHR(st_mode) || S_ISBLK(st_mode))
    {
      sprintf(tmp, "%d", nbr);
      i = 0;
      while (i < size - my_strlen(tmp))
	str[i++] = '0';
      j = 0;
      while (i < size)
	str[i++] = tmp[j++];
    }
}