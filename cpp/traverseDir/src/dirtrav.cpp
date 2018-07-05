#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <iostream>

#include "dirtrav.h"


bool do_print = true;


int isadirectory( char * pathname ) {
    struct stat s;
    if( -1 == stat( pathname, &s ) ) {
        perror("stat()");
        exit(EXIT_FAILURE);
    }
    return (s.st_mode & S_IFDIR );
}

int depth_first_apply( char * pathname, int pathfun(char * pathname1) ) {
    int count = 0;
    int countbuff;
    DIR * mydir;
    dirent * entry;
    char dirpath[1024];
    
    if( 0 < (countbuff = pathfun( pathname )) && isadirectory(pathname) ) {
        mydir = opendir(pathname);
        strcpy(dirpath, pathname);
        count += countbuff;
        switch( errno ) {
            case EACCES: case EMFILE: case ENOENT: case ENOMEM: case ENOTDIR:
                perror("opendir()");
                return -1;
                break;
            default:
                while( (entry = readdir(mydir)) != NULL ) {
                    if( !strcmp(entry->d_name, ".") || !strcmp(entry->d_name,"..") )
                        continue;
                    strcpy(dirpath, pathname);
                    strcat(dirpath,entry->d_name);
                    //printf("dirpath: %s\n", dirpath);
                    if(isadirectory(dirpath))
                        strcat(dirpath,"/");
                    count += ((countbuff = depth_first_apply(dirpath, pathfun)) > 0)? countbuff:0;
                    //printf("count: %d\n", count);
                }
                break;
        }
    } else if ( countbuff == -1 ) {
        return -1;
    } else {
        return count;
    }
    return count;
}

int sizepathfun( char * pathname ) {
    struct stat s;
    //printf("statpath: %s\n", pathname);
    if( -1 == stat( pathname, &s ) ) {
        perror("stat()");
        exit(EXIT_FAILURE);
    } else if( !(s.st_mode & S_IFREG) && !(s.st_mode & S_IFDIR) ) {
        return -1;
    }
    if (do_print) {
        std::cout << pathname << " : " << s.st_size << std::endl;
    } 
    return s.st_size; 
}
