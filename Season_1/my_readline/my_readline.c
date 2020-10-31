#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define READLINE_READ_SIZE 8


char* my_readline(int fd);
char* get_line(char* str_buffer);
void my_memset(char* str, char character);


int main(int ac, char ** av )
{
	char *str = NULL;
	int fd = open("./file122.txt", O_RDONLY);

	while ((str = my_readline(fd)) != NULL)
	{
		//printf("**************\n");
		printf("%s\n", str);
		free(str);
		//printf("**************\n");
	}


/*

		

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");

		str = my_readline(fd);
		printf("**************\n");
		printf("%s\n", str);
		free(str);
		printf("**************\n");
*/	

	close(fd);
	//
	//  Yes it's also working with stdin :-)
	//  printf("%s", my_readline(0));
	//
}

char *my_readline(int fd)
{

	 if (fd ==-1) 
    { 
        printf("Error, cannot open the file\n"); 
        return NULL;       
    } 

	char buffer[READLINE_READ_SIZE + 1];
	static char str_buffer[5000];
	char* line = NULL;
	int characters_read = 0; 
 	// record everything into string buffer
	while((characters_read = read(fd, buffer, READLINE_READ_SIZE)))
	{
		buffer[characters_read] = '\0';
		strcat(str_buffer, buffer);
		if(strchr(str_buffer, '\n')) 
		{
      		break;
    	}
	}
	

	line = get_line(str_buffer);


	
	
	if(strlen(line) == 0 && strlen(str_buffer) == 0)
		return NULL;

	return line;
}

char* get_line(char* str_buffer)
{
	int index = 0;
	int line_length = 0;
	int i = 0;
	char* rest_of_lines;


	//count how many characters until new line or end of file
	while(str_buffer[line_length] != '\n' && str_buffer[line_length] != '\0')
	{
		line_length++;
	}

    // get the line and pass it to first_line
	char* first_line = malloc(line_length*sizeof(char)+1);
	
	while(i < line_length)
	{
		first_line[i] = str_buffer[i];
		i++;
	}
	first_line[line_length] = '\0';
	
	rest_of_lines = (char* )malloc(strlen(str_buffer)*sizeof(char)+1);


	
	while(str_buffer[line_length+index+1] != '\0')
	{
		rest_of_lines[index] = str_buffer[line_length+index+1];
		index++;
	}

	rest_of_lines[index] = '\0';
	my_memset(str_buffer,'\0');
	strcpy(str_buffer,rest_of_lines);
	
	free(rest_of_lines);

	return first_line;
}

void my_memset(char* str, char character)
{
	while(*str)
	{
		*str++ = character;
	}
}
