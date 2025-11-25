#include "common.h"
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    print_welcome_msg("SERVEUR");

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "Pong du Serveur!";

    // 1. Création du socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Echec socket");
        exit(EXIT_FAILURE);
    }

    // 2. Options pour éviter l'erreur "Address already in use"
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Echec setsockopt");
        exit(EXIT_FAILURE);
    }

    // 3. Bind (Attacher le socket au port 8080)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Écoute sur toutes les interfaces
    address.sin_port = htons(DEFAULT_PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Echec bind");
        exit(EXIT_FAILURE);
    }

    // 4. Listen
    if (listen(server_fd, 3) < 0) {
        perror("Echec listen");
        exit(EXIT_FAILURE);
    }

    printf("En attente de connexion sur le port %d...\n", DEFAULT_PORT);

    // 5. Accept (Bloquant)
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("Echec accept");
        exit(EXIT_FAILURE);
    }

    // 6. Lecture
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Message reçu du client : %s\n", buffer);

    // 7. Écriture (Réponse)
    send(new_socket, response, strlen(response), 0);
    printf("Réponse envoyée.\n");

    // Fermeture
    close(new_socket);
    close(server_fd);
    return 0;
}