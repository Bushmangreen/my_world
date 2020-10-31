
#include "my_tar.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>


#define F_NAME 100;
#define F_MODE 8;
#define F_OWNER 8;
#define F_GROUP 8;
#define F_SIZE 12;
#define F_MODIFIED 12;
#define F_CHECKSUM 8;
#define F_TYPE 1;
#define F_LINKED_FILE_NAME 100;



/* POSIX header.  */

typedef struct posix_header
{                              /* byte offset */
	char name[100];               /*   0 */
	char mode[8];                 /* 100 */
	char uid[8];                  /* 108 */
	char gid[8];                  /* 116 */
	char size[12];                /* 124 */
	char mtime[12];               /* 136 */
	char checksum[8];               /* 148 */
	char typeflag;                /* 156 */
	char linkname[100];           /* 157 */
	char magic[6];                /* 257 */
	char version[2];              /* 263 */
	char uname[32];               /* 265 */
	char gname[32];               /* 297 */
	char devmajor[8];             /* 329 */
	char devminor[8];             /* 337 */
	char prefix[155];             /* 345 */
    char padding[12];             /* 500 */

}tar_header;

long long decimal_to_octal(long long decimalNumber)
{
    long long octalNumber = 0, i = 1;

    while (decimalNumber != 0)
    {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octalNumber;
}



char* itoa(unsigned long value, int base){ // converts integer to string
	
	static char buffer[32] = {0};
	const char characters_map[] = "0123456789abcdef";
	
	int i = 30;
	int index;

	if (value == 0) return "0";

	for ( i = 30; value && i ; --i) {
		
		index = value % base ;
		buffer[i] = characters_map[index];
		value /= base;
		
	
	}
	return &buffer[i+1];
}

void filler(char* str, char* header_info, int size)
{
	int index = 0;
	
	int i = 0;
	int n;
	

	memset( str, '0', size );
	str[size-1] = '\0';
	str[size-2] = ' ';
	n = strlen(header_info)/sizeof(*header_info);
	while(*header_info)
	{
		str[size-2-n+i++] = *header_info++;
	}



	
}


/*
void fill_in_header(tar_header* header)
{	
	int index = 0;
	char* owner;
	int i = 0;
	
	header.owner[7] = '\0';
	header.owner[6] = ' ';
	owner = itoa(file_stat.st_uid,8);
	printf("%s", owner);
	while(*owner)
	{
		header.owner[3+i++] = *owner++;
	}

	header.owner[0] = '0';
	header.owner[1] = '0';
	header.owner[2] = '0';

}
	
*/
char file_type(struct stat *buf)
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

void	file_linkname(char *my_link, char *str, struct stat *buf)
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
      strcpy(my_link, link);
    }

    free(link);
}

void get_uid(char *str, struct stat *buf, char type)
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


int main(int argc, char* argv[])
{

	struct stat file_stat;
	
	stat(argv[3],&file_stat);
	/*
	Good Evening Terence, the way to do the creating tar is as follows correct?
1. Get the header info
        1. a) loop through the current directory by readdir () and get the "struct stat file_stats" for solutation
         1. b) then i will write all the info from file_stat as header to tar_file
	*/

	tar_header header;


	/*

    memset( &header, 0, sizeof( struct tar_header ) );
	snprintf( header.name, 100, "%s", argv[3]);
	snprintf( header.mode, 8, "%06o ", file_stat.st_mode ); 
    snprintf( header.owner, 8, "%06o ", file_stat.st_uid ); 
    snprintf( header.group, 8, "%06o ", file_stat.st_gid ); 
    snprintf( header.size, 12, "%011llo ", file_stat.st_size );
    snprintf( header.modified, 12, "%lld ",decimal_to_octal(file_stat.st_mtime)); 
    memset( header.checksum, ' ', 8 );
    header.type[0] = '0'; 
    */


	memset( &header,0, sizeof(tar_header) );
	snprintf( header.name, 100, "%s", argv[3]);
	filler(header.mode,itoa(file_stat.st_mode,8),8);
	filler(header.uid,itoa(file_stat.st_uid,8),8);
	filler(header.gid,itoa(file_stat.st_gid,8),8);
	filler(header.size,itoa(file_stat.st_size,8),12);
	filler(header.mtime,itoa(file_stat.st_mtime,8),12);
	memset( header.checksum, ' ', 8 );
    header.typeflag = file_type(&file_stat);
    file_linkname(header.linkname, argv[3], &file_stat);
    snprintf( header.version, 2, "%s", "00");
    snprintf( header.magic, 6, "%s", "ustar");
    get_uid(header.uname, &file_stat, 0);
    get_uid(header.gname, &file_stat, 1);
    snprintf( header.prefix, 155, "%s", "\0");

    /*
    my_append_int(my_file->version, 0, 3);
  my_append_data(my_file->magic, "ustar");
  my_append_uid(my_file->u_name, buf, 0);
  my_append_uid(my_file->g_name, buf, 1);
  my_append_dev(my_file->devmajor, major(buf->st_dev), 8, buf->st_mode);
  my_append_dev(my_file->devminor, minor(buf->st_dev), 8, buf->st_mode);
  my_append_data(my_file->prefix, "\0");
  my_append_chksum(my_file->chksum, my_file, 0);
  return (my_file);
*/

     //Calculate the checksumec
    int checksum = 0;
    int i;
    printf("%lu\n", sizeof(header));
    char* bytes = header.name;

    for( i = 0; i < sizeof(header); i++ ){
  
        checksum += bytes[i];
    }

    filler(header.checksum,itoa(checksum,8),8);


    write(1, &header, sizeof(tar_header));

    printf("\n");



	/*


	printf("%s  ",argv[3]);
	printf("%lld  ",decimal_to_octal(file_stat.st_mode));
	printf("%lld  ",decimal_to_octal(file_stat.st_uid));
	printf("%lld  ",decimal_to_octal(file_stat.st_gid));
	printf("%lld  ",decimal_to_octal(file_stat.st_size));
	printf("%lld  \n",decimal_to_octal(file_stat.st_mtime));
	printf("%lld  \n",file_stat.st_size);
	//printf("Checksum for header record: <--- do not know hot get this?  ");
	//printf("Link indicator (file type) <--- do not know hot get this?  ");
	//printf("Name of linked file <--- do not know hot get this?  ");
	//Calculate the checksum
    
    size_t checksum = 0;
    const unsigned char* bytes = &header;
    for(int i = 0; i < sizeof(tar_header); ++i ){
        checksum += bytes[i];
    }
    snprintf( header.checksum, 8, "%06o ", checksum );

    printf("%lld  \n",decimal_to_octal(checksum));

	*/

	t_opt* opt = get_opt(argc,argv);
	print_opt(opt);
	/*

	FILE *fp;
   	char str[] = "This is tutorialspoint.com";

   	fp = fopen( argv[2] , "w" );
   	fwrite(str , 1 , sizeof(str) , fp );



	

   	fclose(fp);
	*/
	free(opt);

	return 0;
}