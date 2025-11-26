#ifndef DIRECTORY_MANAGEMENT_H
#define DIRECTORY_MANAGEMENT_H

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

/**
This function checks if the specified root directory exists.
@param path The path to the root directory.
@return 1 if the directory exists, 0 if it does not exist, -1 if the path exists but is not a directory.
*/
int does_root_directory_exist(const char *path);

/**
This function creates a directory at the specified path.
@param path The path where the directory should be created.
@return 0 on success, -1 on failure.
*/
int create_directory(const char *path);

/**
This function checks if the root directory exists, and creates it if it does not.
@param path The path to the root directory.
@return 0 on success, -1 on failure.
*/
int check_or_create_root_dir(const char *path);

#endif // DIRECTORY_MANAGEMENT_H