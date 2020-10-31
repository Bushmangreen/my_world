
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <sys/sysmacros.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TMAGIC   "ustar"        /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2

/* Values used in typeflag field.  */
#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */

#define XHDTYPE  'x'            /* Extended header referring to the
                                   next file in the archive */
#define XGLTYPE  'g'            /* Global extended header */

/* Bits used in the mode field, values in octal.  */
#define TSUID    04000          /* set UID on execution */
#define TSGID    02000          /* set GID on execution */
#define TSVTX    01000          /* reserved */
                                /* file permissions */
#define TUREAD   00400          /* read by owner */
#define TUWRITE  00200          /* write by owner */
#define TUEXEC   00100          /* execute/search by owner */
#define TGREAD   00040          /* read by group */
#define TGWRITE  00020          /* write by group */
#define TGEXEC   00010          /* execute/search by group */
#define TOREAD   00004          /* read by other */
#define TOWRITE  00002          /* write by other */
#define TOEXEC   00001          /* execute/search by other */



#define    NAME_OFFSET  0 
#define    SIZE_OFFSET  124 
#define    MAGIC_OFFSET 257
#define    TYPE_OFFSET  156
#define    MODE_OFFSET  100 
#define    LNAME_OFFSET 157
#define    MJ_OFFSET  329 
#define    MN_OFFSET  337
#define    MTIME_OFFSET  136

#define    NAME_SIZE  100
#define    MAGIC_SIZE 5
#define    BLOCK_SIZE 512

#define BLOCKSIZE       512
#define BLOCKING_FACTOR 20
#define RECORDSIZE      10240



#define DEFAULT_DIR_MODE S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH // 0755
#define PATH_MAX_STRING_SIZE 256
// file type values (1 octet)
#define REGULAR          0
#define NORMAL          '0'
#define HARDLINK        '1'
#define SYMLINK         '2'
#define CHAR            '3'
#define BLOCK           '4'
#define DIRECTORY       '5'
#define FIFO            '6'
#define CONTIGUOUS      '7'














typedef struct t_opt
{
	int c;
    int f;
	int r;
	int t;
	int u;
	int x; 
    int error;
}t_opt;

typedef struct posix_header
{				/* byte offset */
	char name[100];		/*   0 */
	char mode[8];			/* 100 */
	char uid[8];			/* 108 */
	char gid[8];			/* 116 */
	char size[12];		/* 124 */
	char mtime[12];		/* 136 */
	char chksum[8];		/* 148 */
	char typeflag;		/* 156 */
	char linkname[100];		/* 157 */
	char magic[6];		/* 257 */
	char version[2];		/* 263 */
	char uname[32];		/* 265 */
	char gname[32];		/* 297 */
	char devmajor[8];		/* 329 */
	char devminor[8];		/* 337 */
	char prefix[155];		/* 345 */
	
				/* 500 */
}tar_header;


typedef struct compiled_tar{
    char original_name[100];    // original filenme; only availible when writing into a tar
    long data_begin;            // location of data in file (including metadata)
    long dsize;          // size in long 
    unsigned long mtime;                  // mtime in long
    tar_header header;
}TAR;

t_opt* get_opt(int argc, char *argv[]);
void print_opt(t_opt* opt,int argc, char* argv[]);
int print_error(void);
int str_search(char* str, char* search);
tar_header* init_tar_header();
int get_file_size(int fd);
int write_file_content(int fd_archive, char* file_name);
tar_header* get_meta_data(char* file_name);
int open_flags(t_opt* opt);
int get_file_size(int fd);
int write_to_stdout(int fd_archive, char* file_name);

void end_of_archive(int fd);
char* itoa(char* res, unsigned int number, int size, int base);
void fill_name(char* header, char* name, int size);
void fill_mode(char* header, int st_mode, int size);
void fill_num(char* header, char* file_info, int size);
void fill_size(char* header, char* file_info, int size);
void fill_spaces(char* header);
char file_type(struct stat *buf);
void fill_linkname(char *header, char *str, struct stat *buf);
void fill_version(char* header, int size);
void fill_magic(char* header, char* magic);
void fill_uid(char *header, struct stat *buf, char type);
void fill_prefix(char* header, char end_of_string, int size);
void fill_checksum(char* header, int sum, int size);
int create_archive(int fd_archive, char* file_name, t_opt* opt);






void list_archive(char* archive_name);
void list_mtime(char* archive_name, char* file_name, int* flag);
void extract_archive(char* archive_name);

void tar_parse(const void* tarData, const long tarSize, int *pSize, TAR ** pTars);
int tar_list(const void* tarData, const long tarSize);
int tar_u_option(const void* tarData, const long tarSize, char* file_name, int* flag);
int mkdir_p(const char *dir, const mode_t mode);
int recursive_mkdir(const char * dir, const unsigned int mode);
int mkdir_for_file(TAR* entry);

int tar_x(const void* tarData, const long tarSize);
int extract(TAR* entry, const void* tarData);
int extract_regular(TAR* entry,const void* tarData);
int extract_dir(TAR* entry);
int extract_symlink(TAR* entry);
int extract_hlink(TAR* entry);
int extract_char(TAR* entry);
int extract_block(TAR* entry);
int extract_fifo(TAR* entry);




// long filesize(FILE * filepointer, char * filename);
unsigned int octal_decimal(long octalnum);
long octal_string_to_int(const char* oct_string);
unsigned int oct2uint(char * oct, unsigned int size);
int write_size(int fd, char * buf, int size);
int read_size(int fd, char * buf, int size);