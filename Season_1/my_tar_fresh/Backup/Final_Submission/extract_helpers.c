#include "my_tar.h"

int extract_regular(TAR* entry,const void* tarData){

    // if(mkdir_for_file(entry) < 0) return -1;
    long size = entry->dsize; 
    int f = open(entry->header.name, O_WRONLY | O_CREAT | O_TRUNC, oct2uint(entry->header.mode, 7) & 0777);
    if (f < 0){
        printf("Unable to open file %s\n", entry->header.name);
        return -1;
    }
    if(write(f, tarData+entry->data_begin, size)<0){
        printf("error in writing");
        return -1;
    }
    close(f);

    return 1;
}

int extract_dir(TAR* entry){
    if (mkdir_p(entry->header.name, oct2uint(entry->header.mode, 7) & 0777) < 0){
        printf("Unable to create directory %s: %s", entry->header.name, strerror(errno));
        return -1;
    }
    return 1;
}

int extract_symlink(TAR* entry){
    if (symlink(entry->header.linkname, entry->header.name) < 0){
        printf("Unable to make symlink %s: %s", entry->header.name, strerror(errno));
        return -1;
    }
    return 1;
}

int extract_hlink(TAR* entry){
    if (link(entry->header.linkname, entry->header.name) < 0){
        printf("Unable to make hlink %s: %s", entry->header.name, strerror(errno));
        return -1;
    }
    return 1;
}

int extract_char(TAR* entry){
    if (mknod(entry->header.name, S_IFCHR | (oct2uint(entry->header.mode, 7) & 0777), (oct2uint(entry->header.devmajor, 7) << 20) | oct2uint(entry->header.devminor, 7)) < 0){
        printf("Unable to make char %s: %s", entry->header.name, strerror(errno));
        return -1;
    }
    return 1;
}

int extract_block(TAR* entry){
    if (mknod(entry->header.name, S_IFBLK | (oct2uint(entry->header.mode, 7) & 0777), (oct2uint(entry->header.devmajor, 7) << 20) | oct2uint(entry->header.devminor, 7)) < 0){
        printf("Unable to make char %s: %s", entry->header.name, strerror(errno));
        return -1;
    }
    return 1;
}

int extract_fifo(TAR* entry){
    if (mkfifo(entry->header.name, oct2uint(entry->header.mode, 7) & 0777) < 0){
        printf("Unable to make fifo %s: %s", entry->header.name, strerror(errno));
        return -1;
    }
    return 1;
}

int extract(TAR* entry, const void* tarData){
    printf("%s \n", entry->header.name);

    int type = entry->header.typeflag;

    if(type == NORMAL ||type == REGULAR  || type == CONTIGUOUS){
        if(extract_regular(entry, tarData)<0) return -1;
    }
    switch (type) {
        case HARDLINK:{
            if(extract_hlink(entry) < 0) return -1;
            break;
        }
        case SYMLINK:{
            if(extract_symlink(entry) < 0) return -1;
            break;
        }
        case CHAR:{
            if(extract_char(entry) < 0) return -1;
            break;
        }
        case BLOCK:{
            if(extract_block(entry) < 0) return -1;
            break;
        }
        case DIRECTORY:{
            if(extract_dir(entry) < 0) return -1;
            break;
        }
        case FIFO:{
            if(extract_fifo(entry) < 0) return -1;
            break;
        }
        default: break;
    }

    return 1;
}

int mkdir_for_file(TAR* entry){
    size_t len = strlen(entry->header.name);
    if (!len) {
        printf("Attempted to extract entry with empty name");
        return -1;
    }   

    char * path = calloc(len + 1, sizeof(char));
    strncpy(path, entry->header.name, len);

    // remove file from path
    while (--len && (path[len] != '/'));
    path[len] = '\0';   // if nothing was found, path is terminated

    if (recursive_mkdir(path, DEFAULT_DIR_MODE) < 0){
        printf("Could not make directory %s", path);
        free(path);
        return -1;
    }
    free(path);
    return 1;
}


int mkdir_p(const char *dir, const mode_t mode) {
    char tmp[PATH_MAX_STRING_SIZE];
    char *p = NULL;
    struct stat sb;
    size_t len;
    
    /* copy path */
    len = strnlen (dir, PATH_MAX_STRING_SIZE);
    if (len == 0 || len == PATH_MAX_STRING_SIZE) {
        return -1;
    }
    memcpy (tmp, dir, len);
    tmp[len] = '\0';

    /* remove trailing slash */
    if(tmp[len - 1] == '/') {
        tmp[len - 1] = '\0';
    }

    /* check if path exists and is a directory */
    if (stat (tmp, &sb) == 0) {
        if (S_ISDIR (sb.st_mode)) {
            return 0;
        }
    }
    
    /* recursive mkdir */
    for(p = tmp + 1; *p; p++) {
        if(*p == '/') {
            *p = 0;
            /* test path */
            if (stat(tmp, &sb) != 0) {
                /* path does not exist - create directory */
                if (mkdir(tmp, mode) < 0) {
                    return -1;
                }
            } else if (!S_ISDIR(sb.st_mode)) {
                /* not a directory */
                return -1;
            }
            *p = '/';
        }
    }
    /* test path */
    if (stat(tmp, &sb) != 0) {
        /* path does not exist - create directory */
        if (mkdir(tmp, mode) < 0) {
            return -1;
        }
    } else if (!S_ISDIR(sb.st_mode)) {
        /* not a directory */
        return -1;
    }
    return 0;
}

int recursive_mkdir(const char * dir, const unsigned int mode){
    int rc = 0;
    const size_t len = strlen(dir);

    if (!len){
        return 0;
    }

    char * path = calloc(len + 1, sizeof(char));
    strncpy(path, dir, len);

    // remove last '/'
    if (path[len - 1] ==  '/'){
       path[len - 1] = 0;
    }

    // all subsequent directories do not exist
    for(char * p = path + 1; *p; p++){
        if (*p == '/'){
            *p = '\0';

            if ((rc= mkdir(path, mode?mode:DEFAULT_DIR_MODE))){
                printf("Could not create directory %s: %s", path, strerror(rc));
            }

            *p = '/';
        }
    }

    if (mkdir(path, mode?mode:DEFAULT_DIR_MODE) < 0){
        printf("Could not create directory %s: %s", path, strerror(rc));
    }

    free(path);
    return 0;
}