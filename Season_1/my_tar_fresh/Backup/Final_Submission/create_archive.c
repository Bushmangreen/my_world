


#include "my_tar.h"


int open_flags(t_opt* opt)
{
    int res = 0;
    
    if (opt->c == 1)
    {
        return (res | O_CREAT | O_TRUNC | O_WRONLY);
    }
    
    if (opt->r == 1 || opt->u == 1 )
    {
        return ( res | O_RDWR );
    }
    
    return (res | O_RDONLY);  
}   

tar_header* init_tar_header()
{
    tar_header* header = malloc(512);
    if (header != NULL)
    {
        bzero(header, 512);
    }
    return header;
}

tar_header* get_meta_data(char* file_name)
{
    struct stat file_stat;

    if ( (stat(file_name, &file_stat)) < 0)
    {
        printf("Error, file does not exist\n");
        exit(0);
    }

    tar_header* header = init_tar_header();

    fill_name( header->name, file_name, 100);
    fill_mode(header->mode, file_stat.st_mode, 8);
    itoa(header->uid, file_stat.st_uid, 8, 8);
    itoa(header->gid, file_stat.st_gid, 8, 8);
    itoa(header->size, file_stat.st_size, 12 ,8);
    itoa(header->mtime, file_stat.st_mtime, 12, 8);
    fill_spaces(header->chksum);
    header->typeflag = file_type(&file_stat);    
    fill_linkname(header->linkname, file_name, &file_stat);
    fill_magic(header->magic, "ustar");
    fill_version(header->version, 2);
    fill_uid(header->uname, &file_stat, 0);
    fill_uid(header->gname, &file_stat, 1);
    
     // sum the checksum
    char* byte = (char *) header;
    unsigned int sum = 0;
    for(int index = 0; index < 512; index++)
    {
        sum = sum + byte[index];
    }
    // write the checksum to header
    fill_checksum(header->chksum, sum, 8);

    return header;
}

int get_file_size(int fd)
{
    int res = 0;
    int counter;
    char buf[512];
    while((counter = read(fd, buf, 512)) > 0)
    {
        res = res + counter;
    }

    if (res % 512 != 0)
    {
        res += 512 - ( res % 512);
    }
    lseek(fd, 0, SEEK_SET);
    return res;
}

int write_file_content(int fd_archive, char* file_name)
{
    int res = 0;
    int fd_file = open(file_name, O_RDONLY);
    int file_size = get_file_size(fd_file);

    char content[file_size];
    bzero(content, file_size);
    
    read(fd_file, content, file_size);
    write(fd_archive, content, file_size);

    close(fd_file);
    return res;
    
}

void end_of_archive(int fd)
{
    int two_blocks = 512 * 2;
    char end[two_blocks];
    bzero(end, two_blocks);
    write(fd, end, two_blocks);
}


int create_archive(int fd_archive, char* file_name, t_opt* opt)
{ 
    tar_header* header;

    if (opt->r == 1 || opt->u == 1)
    {
        if (lseek(fd_archive, -1024, SEEK_END) == (off_t) (-1))
        {
            printf("could not locate lseek\n");
        }
    }
     // write header to file
    header = get_meta_data(file_name);
    write(fd_archive, header, 512);
    
    // write file content to file 
    write_file_content(fd_archive, file_name);

    //end_of_archive(fd_archive);
    free(header);
    
    return 0;
}


int write_to_stdout(int fd_archive, char* file_name)
{
    
    tar_header* header;
   
    // write header to file
    header = get_meta_data(file_name);
    write(fd_archive, header, 512);
    
    // write file content to file 
    write_file_content(fd_archive, file_name);

    //end_of_archive(fd_archive);
    free(header);
    return 0;
}

char* itoa(char* res, unsigned int number, int size, int base){ // converts integer to string
    
    
    const char characters_map[] = "0123456789abcdef";
    memset(res, '0', size - 1);
    res[size - 1] = '\0';

    size--;
    while (number)
    {
        res[--size] = characters_map[number % base];
        number = number / base;
    } 

    return res;
}

void fill_name(char* header, char* name, int size)
{
    int index = 0;

    while(name[index] != '\0')
    {
        header[index] = name[index];
        index++;
    }
    header[index++] = '\0';
    if (index > size)
        printf("File name is more than 100 characters\n");

}

void fill_mode(char* header, int st_mode, int size)
{

    int masked = st_mode & 0777;
    char* file_info = itoa(header, masked, 8, 8);
    
}




void fill_size(char* header, char* file_info, int size)
{
    int index = 0;
    int i = 0;
    int length = 0;

    while(i < size)
    {
        header[i++] = '0';
    }

    while(file_info[length] != '\0')
    {
        length++;
    }

    int offset = size - length - 2;

    while(offset < size - 2)
    {
        header[offset++] = file_info[index++];
    }   
    header[offset++] = ' ';
    header[offset] = '\0';

}

void fill_spaces(char* header)
{
    int index = 0;
    
    while ( index < 8)
    {
        header[index++] = ' ';
    }
        

}

char file_type(struct stat *buf)
{
  char  c;
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

void fill_linkname(char *header, char *str, struct stat *buf)
{
  char  *link;
  int   len;

  if ((link = malloc(sizeof(char) * 256)) == NULL)
    exit(EXIT_FAILURE);
  if (S_ISLNK(buf->st_mode))
    {
      if ((len = readlink(str, link, 256 * sizeof(char))) < 0)
    {
      printf("Could not allocate memory for linkname\n");
    }
      else
    link[len] = '\0';
      strcpy(header, link);
    }

    free(link);
}
void fill_magic(char* header, char* magic)
{
    int index = 0;
    while(magic[index])
    {
        header[index] = magic[index];
        index++;
    }
    header[index] = ' ';
}

void fill_version(char* header, int size)
{
    header[0] = ' ';
    header[1] = '\0';   
}



void fill_uid(char *header, struct stat *buf, char type)
{
  struct passwd *pwd;
  struct group  *grp;
  char          *tmp;
  int            i;

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
        header[i] = tmp[i];
        i++;
    }
}

void fill_prefix(char* header, char end_of_string, int size)
{
    int index = 0;

    while (index < size)
    {
        header[index++] = end_of_string;
    }
}




void fill_checksum(char* header, int sum, int size)
{
    int index = 0;
    int i = 0;
    int length = 0;
    char* file_info = itoa(header, sum, 8, 8);
    int offset = 1;

    while(offset < size)
    {
        header[index++] = file_info[offset++];
    }
    
    header[6] = '\0';
    header[7] = ' ';
    
}