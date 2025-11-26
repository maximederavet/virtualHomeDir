#ifndef WORKER_H
#define WORKER_H

#include <netinet/in.h>

/*
 * Gère l'interaction avec un client connecté.
 * Cette fonction est appelée par le processus enfant.
 */
void handle_client(int client_socket, struct sockaddr_in client_addr, const char *root_directory);

#endif