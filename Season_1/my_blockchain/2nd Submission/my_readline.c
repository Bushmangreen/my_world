

#include "headers.h"

#define READLINE_READ_SIZE 100


char* my_readline(int fd);
char* get_line(char* str_buffer);
void my_memset(char* str, char character);



char *my_readline(int fd)
{

	 if (fd == -1) 
    { 
        printf("Error, file doesnt exist: -1\n"); 
        return NULL;       
    } 
    if (fd > 3)
    {
    	printf("Error, file doesnt exist: Big Integer\n"); 
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
    {   
        free(line);
		return NULL;
    }
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
