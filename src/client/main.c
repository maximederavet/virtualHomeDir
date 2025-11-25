#include "common.h"
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    print_welcome_msg("CLIENT");

    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "Ping du Client!";
    char buffer[BUFFER_SIZE] = {0};

    // 1. Création du socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Erreur création socket \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEFAULT_PORT);

    // Conversion IP texte -> binaire (Localhost)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nAdresse invalide / non supportée \n");
        return -1;
    }

    // 2. Connexion
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nÉchec de la connexion (Le serveur est-il lancé ?)\n");
        return -1;
    }

    // 3. Envoi
    send(sock, hello, strlen(hello), 0);
    printf("Message envoyé : %s\n", hello);

    // 4. Lecture réponse
    read(sock, buffer, BUFFER_SIZE);
    printf("Réponse du serveur : %s\n", buffer);

    close(sock);
    return 0;
}