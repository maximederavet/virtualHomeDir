#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> // Pour sockaddr_in, inet_pton

#define DEFAULT_PORT 8080
#define BUFFER_SIZE 1024

// Juste pour tester le linkage du dossier common
void print_welcome_msg(const char *role);

#endif