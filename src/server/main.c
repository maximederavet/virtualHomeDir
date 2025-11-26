#include "common.h"
#include "directory_management.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>     // For access()
#include <sys/stat.h>   // For stat()
#include <sys/types.h>  // For stat()




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