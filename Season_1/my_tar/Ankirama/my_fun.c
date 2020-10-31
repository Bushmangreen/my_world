#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_nbr.h"

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    i += 1;
  return (i);
}

int	my_add(char *str)
{
  int	i;
  int	tot;

  i = 0;
  tot = 0;
  while (str[i])
    tot += str[i++];
  return (tot);
}

void	my_checksum(char *str, char *tmp)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (i < 6 - my_strlen(tmp))
    str[i++] = '0';
  while (i < 6)
    str[i++] = tmp[j++];
  str[i++] = ' ';
  str[i] = '0';
}

/*
** type = 0 --> malloc
** type = 1 --> errno
*/
void	my_puterror(char type, int my_errno)
{
  errno = my_errno;
  if (type == 0)
    printf("ERROR: malloc!\n");
  else
    printf("%m\n");
  exit(EXIT_FAILURE);
}

/*
** Will check block of 512
*/
char	my_check_block(char *str)
{
  int	i;

  i = 0;
  while (i < 512 && str[i] == '\0')
    i += 1;
  return (i == 512);
}