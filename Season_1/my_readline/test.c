
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define READLINE_READ_SIZE 512


int get_line_length(char* str)
{
	int i;
	while(str[i] != '\n' && str[i] != '\0') 
	{
    	i++;
 	}
 	return i;
}

char* string_after_newline(char* str,int len)
{
  char* temp;
  int index = 0;
  temp = (char *)malloc(strlen(str) * sizeof(char) + 1);

  for(int j = len + 1; str[j] != '\0'; j++) {
    temp[index] = str[j];
    index++;
  }

  temp[index] = '\0';
  return temp;
}

char *createLine(char *line, char *strFromBuf) {
  int line_length = 0;
  char* temp;
  int tempInx = 0;


  line_length = get_line_length(strFromBuf);


  line = (char *)malloc(line_length * sizeof(char) + 1);

  if(strFromBuf[line_length] == '\n') {
    strncpy(line, strFromBuf, line_length);
  } else {
    strcpy(line, strFromBuf);
  }
  line[line_length] = '\0';

  temp = string_after_newline(strFromBuf,line_length);

  strcpy(strFromBuf, temp);

  free(temp);

  return line;
}

char *my_readline(int fd) {
  char* buffer;
  char *line;

  static char strFromBuf[4095];

  int size_read = 0;

  while((size_read = read(fd, buffer, READLINE_READ_SIZE)) > 0) 
  {
    buffer[size_read] = '\0';
    strcat(strFromBuf, buffer);
    if(strchr(strFromBuf, '\n')) {
      break;
    };
  }

  line = createLine(line, strFromBuf);

  int len = strlen(line);

  if(size_read == 0 && len == 0) {
    //printf("%s\n", "ENd");
    return NULL;
  }

  return line;
};


int main(int ac, char **av) {
  char *str = NULL;
  int fd = open("./file.txt", O_RDONLY);

  while ((str = my_readline(fd)) != NULL)
  {
  	printf("%s\n", str);
  	free(str);
  }
 

  close(fd);

  return 0;
}

