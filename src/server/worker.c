#include "worker.h"
#include "common.h"
#include <stdio.h>
#include <unistd.h>

void handle_client(int client_socket, struct sockaddr_in client_addr, const char *root_directory) {
    char buffer[BUFFER_SIZE] = {0};
    char *response = "Bonjour du processus enfant !";

    // Juste pour le debug : affichage de l'IP du client
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    printf("[Worker %d] Connexion acceptée de %s:%d\n", getpid(), client_ip, ntohs(client_addr.sin_port));

    // Lecture simple (Ping-Pong pour l'instant)
    int valread = read(client_socket, buffer, BUFFER_SIZE);
    if (valread > 0) {
        printf("[Worker %d] Reçu : %s\n", getpid(), buffer);
        send(client_socket, response, strlen(response), 0);
    }

    // Fermeture propre
    close(client_socket);
    printf("[Worker %d] Fin de connexion.\n", getpid());
    exit(0); // IMPORTANT : L'enfant doit mourir ici
}