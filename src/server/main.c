#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>     // For access()
#include <sys/stat.h>   // For stat()
#include <sys/types.h>  // For stat()

int does_root_directory_exist(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        return 0; // Does not exist
    }

    if (!S_ISDIR(st.st_mode)) {
        return -1; // Not a directory
    }

    return 1; // Directory exists
}

int create_directory(const char *path) {
    if (mkdir(path, 0755) == -1) {
        perror("mkdir failed");
        return -1;
    }
    return 0;
}

int check_or_create_root_dir(const char *path) {
    int status = does_root_directory_exist(path);
    if (status == 1) {
        return 0; // Directory exists
    } else if (status == -1) {
        fprintf(stderr, "Error: %s exists but is not a directory.\n", path);
        return -1;
    } else {
        // Directory does not exist, attempt to create it
        if (create_directory(path) == -1) {
            return -1; // Failed to create directory
        }
        return 0; // Successfully created directory
    }
}


/*
 * The server is supposed to be launched with 
 * $ ./Server <root_directory> <IP> <port>.
 */
int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <root_directory> <IP> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *root_directory = argv[1];
    char *ip_address     = argv[2];
    int   port           = atoi(argv[3]);

    if (check_or_create_root_dir(root_directory) == 0) {
        printf("Root directory is ready: %s\n", root_directory);
    } else {
        fprintf(stderr, "Failed to prepare root directory: %s\n", root_directory);
        exit(EXIT_FAILURE);
    }


    return 0;
}