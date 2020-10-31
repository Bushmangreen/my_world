
#include "my_tar.h"

void list_archive(char* archive_name){
    // printf("opening %s \n", archive_name);
    long fsize, mysize, bytes_read;
    FILE* f;
    char* data;
    const char* myfile;
    
    f = fopen(archive_name, "rb");
    fsize = get_file_size(fileno(f));
    data = (char*) malloc(fsize + 1);
    bytes_read = fread(data, 1, fsize, f);
    
    fclose(f);
    if( bytes_read != fsize ){
        puts("File was not read correctly!");
        free(data);
        return;
    }
    data[fsize] = 0;

    tar_list(data, fsize);

    free(data); /* free data after you finished using tar reader */
}

void list_mtime(char* archive_name, char* file_name, int* flag){
    // printf("opening %s \n", archive_name);
    long fsize, mysize, bytes_read;
    FILE* f;
    char* data;
    const char* myfile;
    
    f = fopen(archive_name, "rb");
    fsize = get_file_size(fileno(f));
    data = (char*) malloc(fsize + 1);
    bytes_read = fread(data, 1, fsize, f);
    
    fclose(f);
    if( bytes_read != fsize ){
        puts("File was not read correctly!");
        free(data);
        return;
    }
    data[fsize] = 0;

    tar_u_option(data, fsize, file_name, flag);

    free(data); /* free data after you finished using tar reader */
}

void tar_parse(const void* tarData, const long tarSize, int *pSize, TAR ** pTars)
{
    const char* tar = (const char*) tarData; /* From "void*" to "char*" s*/
    int i  = 0;
    long p = 0, newOffset = 0;
    TAR * tars;
    do { 
        tars =  (i == 0) ? malloc(sizeof(TAR)) : realloc(tars, (i+1)* sizeof(TAR));
        if(strncmp(TMAGIC, &tar[p+newOffset+MAGIC_OFFSET], MAGIC_SIZE)!=0) {
            *pSize = i;
            *pTars =  tars; 
            return; // break end of new formatted files
        }
        strncpy(&tars[i].header.name[0], tar + NAME_OFFSET + p + newOffset, 100);
        strncpy(&tars[i].header.mode[0], tar + MODE_OFFSET + p + newOffset, 8);
        strncpy(&tars[i].header.mtime[0], tar + MTIME_OFFSET + p + newOffset, 12);
        strncpy(&tars[i].header.size[0], tar + SIZE_OFFSET + p + newOffset,12 );
        strncpy(&tars[i].header.typeflag, tar + TYPE_OFFSET + p + newOffset, 1);
        strncpy(&tars[i].header.linkname[0], tar + LNAME_OFFSET + p + newOffset ,100 );
        strncpy(&tars[i].header.devmajor[0], tar + MJ_OFFSET + p + newOffset ,8 );
        strncpy(&tars[i].header.devminor[0], tar + MN_OFFSET + p + newOffset, 8);
      
        tars[i].mtime = oct2uint(tars[i].header.mtime, 11);
        tars[i].data_begin = p+newOffset+ BLOCK_SIZE;
        p += newOffset; /* pointer to current file's data in TAR */
        tars[i].dsize = octal_string_to_int(tars[i].header.size); // get size in int        
        newOffset = (1 + tars[i].dsize/BLOCK_SIZE) * BLOCK_SIZE; /* skip blocks for memory */
        if( (tars[i].dsize % BLOCK_SIZE) > 0 ) newOffset += BLOCK_SIZE;
        i++;
        
    } while(p + newOffset + BLOCK_SIZE <= tarSize);
    *pTars = tars;
    return;

}

int tar_list(const void* tarData, const long tarSize){
    int count_entries = 0;
    TAR * tars;
    tar_parse(tarData, tarSize, &count_entries, &tars);
    if (count_entries < 0) return -1;
    for (int i = 0; i<count_entries; i++) {
        printf("%s \n", tars[i].header.name);
    }
    free(tars);
    return 1;
}

int tar_u_option(const void* tarData, const long tarSize, char* file_name, int* flag)
{
    int count_entries = 0;
    TAR * tars;
    tar_parse(tarData, tarSize, &count_entries, &tars);
    int same_name = 0;
    int same_mtime = 0;
    struct stat filestat;
    stat(file_name, &filestat);
    unsigned int mtime = (unsigned int)filestat.st_mtime;
    if (count_entries < 0) return -1;
    for (int i = 0; i<count_entries; i++) 
    {
        if (!strcmp(file_name,tars[i].header.name))
        {
            same_name = 1;
            if(mtime == tars[i].mtime)
                same_mtime = 1;  
        }
    }
    if (same_name == 1 && same_mtime == 1)
        *flag = 0;
    else if (same_name == 1 && same_mtime == 0)
        *flag = 1;
    else if (same_name == 0 && same_mtime == 0)
        *flag = 1;

    free(tars);
    return 1;
}

// long filesize(FILE * filepointer, char * filename)
// {
//     int fd = fileno(filepointer);
//     struct stat statbuf;
//     // fd = open(filename, O_RDONLY, S_IRUSR | S_IRGRP);
//     if (fd == -1){
//         printf("failed to open %s\n", filename);
//         exit(EXIT_FAILURE);
//     }
//     if (fstat(fd, &statbuf) == -1){
//         printf("failed to fstat %s\n", filename);
//         exit(EXIT_FAILURE);
//     }
//     return  statbuf.st_size;
// }

long octal_string_to_int(const char* oct_string)
{
    const int SZ_SIZE = 12;
    long mul,i;
    long size = 0;
    for(i=SZ_SIZE-2, mul=1; i>=0; mul*=8, i--) {
        if( (oct_string[i]>='0') && (oct_string[i] <= '9') ){
            size += (oct_string[i] - '0') * mul;
        }
    }
    return size;
}
unsigned int oct2uint(char * oct, unsigned int size){
    unsigned int out = 0;
    int i = 0;
    while ((i < size) && oct[i]){
        out = (out << 3) | (unsigned int) (oct[i++] - '0');
    }
    return out;
}

int write_size(int fd, char * buf, int size){
    int wrote = 0, rc;
    while ((wrote < size) && ((rc = write(fd, buf + wrote, size - wrote)) > 0)){
        wrote += rc;
    }
    return wrote;
}

int read_size(int fd, char * buf, int size){
    int got = 0, rc;
    while ((got < size) && ((rc = read(fd, buf + got, size - got)) > 0)){
        got += rc;
    }
    return got;
}