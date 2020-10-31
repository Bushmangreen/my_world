#include "my_tar.h"

void extract_archive(char* archive_name){
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

    tar_x(data, fsize);

    free(data); /* free data after you finished using tar reader */
}

int tar_x(const void* tarData, const long tarSize){
    int count_entries = 0;
    TAR * tars;
    tar_parse(tarData, tarSize, &count_entries, &tars);
    if (count_entries < 0) return -1;
    for (int i = 0; i<count_entries; i++) {
        extract(&tars[i], tarData);
    }
    free(tars);
    return 1;
}