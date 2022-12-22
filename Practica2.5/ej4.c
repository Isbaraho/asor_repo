#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <address> <port>\n", argv[0]);
    return 1;
  }

  // Obtener información sobre la dirección y el puerto
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;  // Permitir IPv4 e IPv6
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;  // Usar dirección local
  struct addrinfo *ai_result;
  int err = getaddrinfo(argv[1], argv[2], &hints, &ai_result);
  if (err != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
    return 1;
  }

  // Crear socket y enlazar a la dirección y puerto especificados
  int fd_socket;
  for (struct addrinfo *ai = ai_result; ai != NULL; ai = ai->ai_next) {
    fd_socket = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (fd_socket == -1) {
      continue;
    }
    if (bind(fd_socket, ai->ai_addr, ai->ai_addrlen) == 0) {
      // Enlace exitoso
      break;
    }
    close(fd_socket);
  }
  freeaddrinfo(ai_result);
  if (fd_socket == -1) {
    perror("Error al crear y enlazar el socket");
    return 1;
  }

  // Descriptor de archivo para la entrada estándar
  int fd_stdin = STDIN_FILENO;

  // Bucle de recepción de mensajes
  while (1) {
// Estructuras para la función select
fd_set read_fds;
FD_ZERO(&read_fds);
FD_SET(fd_socket, &read_fds);
FD_SET(fd_stdin, &read_fds);
int fd_max = fd_socket > fd_stdin ? fd_socket : fd_stdin;

// Esperar a que alguno de los descriptores esté listo para ser leído
if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) == -1) {
  perror("select");
  return 1;
}

if (FD_ISSET(fd_socket, &read_fds)) {
  // Estructuras para la función recvfrom
  char buffer[2];
  struct sockaddr_storage client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  // Recibir mensaje del cliente
  ssize_t num_bytes = recvfrom(fd_socket, buffer, 2, 0,
                               (struct sockaddr*) &client_addr, &client_addr_len);
  if (num_bytes < 0) {
    perror("recvfrom");
    return 1;
  }

  // Obtener nombre y puerto del cliente
  char client_name[NI_MAXHOST];
  char client_port[NI_MAXSERV];
  err = getnameinfo((struct sockaddr*) &client_addr, client_addr_len,
                    client_name, NI_MAXHOST, client_port, NI_MAXSERV,
                    NI_NUMERICSERV);
  if (err != 0) {
    fprintf(stderr, "getnameinfo: %s\n", gai_strerror(err));
  } else {
    printf("Mensaje recibido de %s:%s\n", client_name, client_port);
  }

// Procesar comando
if (buffer[0] == 't') {
  // Enviar hora al cliente
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char response[64];
  strftime(response, sizeof(response), "%T\n", &tm);
  sendto(fd_socket, response, strlen(response), 0,
         (struct sockaddr*) &client_addr, client_addr_len);
} else if (buffer[0] == 'd') {
  // Enviar fecha al cliente
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char response[64];
  strftime(response, sizeof(response), "%F\n", &tm);
  sendto(fd_socket, response, strlen(response), 0,
         (struct sockaddr*) &client_addr, client_addr_len);
} else if (buffer[0] == 'q') {
  // Terminar el proceso servidor
  break;
}
}

// Cerrar socket
close(fd_socket);

return 0;
}
   

