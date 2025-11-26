#include "directory_management.h" 
#include <stdlib.h>
#include <stdio.h>


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

