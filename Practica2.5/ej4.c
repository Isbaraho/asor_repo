#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int server_sockfd;  // Descriptor del socket del servidor
    struct sockaddr_in6 server_addr;  // Dirección del servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_addr = in6addr_any;  // Acepta cualquier dirección IPv6
    server_addr.sin6_port = htons(2222);  // Puerto del servidor

    // Crear el socket del servidor
    if ((server_sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
        perror("Error al crear el socket del servidor");
        exit(EXIT_FAILURE);
    }

    // Asignar la dirección y puerto al socket del servidor
    if (bind(server_sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Error al asignar la dirección y puerto al socket del servidor");
        exit(EXIT_FAILURE);
    }

    // Poner el socket en estado de escucha
    if (listen(server_sockfd, 5) < 0) {  // 5 es el número máximo de clientes en la cola
        perror("Error al poner el socket en estado de escucha");
        exit(EXIT_FAILURE);
    }

    printf("Servidor de eco iniciado en la dirección IPv6 :: y puerto 2222\n");

    while (1) {
        int client_sockfd;  // Descriptor del socket del cliente
        struct sockaddr_in6 client_addr;  // Dirección del cliente
        socklen_t client_addr_len = sizeof(client_addr);
        char client_ip[INET6_ADDRSTRLEN];  // Dirección IP del cliente en formato string
        int client_port;  // Puerto del cliente

        // Aceptar una conexión entrante
        if ((client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_addr, &client_addr_len)) < 0) {
perror("Error al aceptar una conexión entrante");
continue;
}

 // Obtener la dirección IP y puerto del cliente
    if (inet_ntop(AF_INET6, &client_addr.sin6_addr, client_ip, INET6_ADDRSTRLEN) == NULL) {
        perror("Error al obtener la dirección IP del cliente");
        continue;
    }
    client_port = ntohs(client_addr.sin6_port);

    printf("Conexión desde %s %d\n", client_ip, client_port);

    char buffer[1024];  // Buffer para almacenar los datos recibidos
    int n;  // Número de bytes recibidos

    // Enviar al cliente todo lo que recibe desde el mismo (eco)
    while ((n = recv(client_sockfd, buffer, sizeof(buffer), 0)) > 0) {
        // Enviar los datos recibidos de vuelta al cliente
        if (send(client_sockfd, buffer, n, 0) < 0) {
            perror("Error al enviar datos al cliente");
            break;
        }
    }

    if (n < 0) {
        perror("Error al recibir datos del cliente");
    }

    // Cerrar el socket del cliente
    close(client_sockfd);
    printf("Conexión terminada\n");
}

return 0;
}
