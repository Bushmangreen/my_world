



char  *my_pathfile(char *path, char *name)
{
  char  *res;
  int i;
  int j;

  if ((res = malloc(my_strlen(path) + my_strlen(name) + 1)) == NULL)
    my_puterror(0, 0);
  i = 0;
  j = 0;
  while (path[i])
    res[i] = path[i++];
  while (name[j])
    res[i++] = name[j++];
  res[i] = '\0';
  return (res);
}

char  *my_add_slash_dir(char *str)
{
  char  *res;
  int i;

  if (str[my_strlen(str) - 1] == '/')
    return (str);
  if ((res = malloc(my_strlen(str) + 1)) == NULL)
    my_puterror(0, 0);
  i = 0;
  while (str[i])
    res[i] = str[i++];
  res[i++] = '/';
  res[i] = '\0';
  return (res);
}

static char my_check_dir(struct stat *buf, char *str, FILE *tar, char *opt)
{
  DIR   *rep;
  struct dirent *fle;

  if (!S_ISDIR(buf->st_mode))
    return (0);
  if (!(rep = opendir(str)))
    my_puterror(1, errno);
  while (fle = readdir(rep))
    {
      if (!(fle->d_name[0] == '.' &&
      (fle->d_name[1] == '\0' ||
       (fle->d_name[1] == '.' && fle->d_name[2] == '\0'))))
  my_tar(my_pathfile(str, fle->d_name), tar, opt);
    }
  if (closedir(rep) == -1)
    my_puterror(1, errno);
  return (0);
}

void    my_tar(char *str, FILE *tar, char *opt)
{
  struct stat *buf;
  FILE    *file;
  t_my_file *my_file;

  if ((buf = malloc(sizeof(*buf))) == NULL)
    my_puterror(0, 0);
  if ((file = fopen(str, "r")) == NULL || (lstat(str, buf)) == -1)
    my_puterror(1, errno);
  if (S_ISDIR(buf->st_mode))
    str = my_add_slash_dir(str);
  my_file = my_fill_struct(buf, str);
  if (opt[ID_FILE])
    {
      my_writefunction(tar, my_file);
      my_writefile(file, tar);
    }
  else
    my_display_all(my_file, file);
my_check_dir(buf, str, tar, opt);
  if (opt[ID_VERBOSE])
    printf("%s\n", str);
  free(buf);
  free(my_file);
  if (fclose(file) == -1)
    my_puterror(1, errno);
}