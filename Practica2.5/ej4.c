#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char **argv) {

	if (argc < 3) 
	{
		printf("Use: ./ej1 host port\n");
		return -1;
	}

  // Obtiene la dirección y el puerto de los argumentos
  const char* address = argv[1];
  const char* port = argv[2];
	// crea socket
	int sd = socket(AF_INET, SOCK_DGRAM, list->ai_protocol);
	if (sd == -1) 
  	{
		perror("Unable to open the socket");
		return -1;
	}
		// Establece la dirección y el puerto del socket
	  struct sockaddr_in serv_addr;
	  memset(&serv_addr, 0, sizeof(serv_addr));
	  serv_addr.sin_family = AF_INET;
	  serv_addr.sin_port = htons(atoi(port));
	  if (inet_pton(AF_INET, address, &serv_addr.sin_addr) <= 0) {
	    perror("Error al establecer dirección del servidor");
	    return 1;
	  }

	if (bind(sd, list->ai_addr, list->ai_addrlen)) 
 	{
		perror("Unable to bind");
		return -1;
	}
 while (1) {
    // Crea el conjunto de descriptores de archivo para leer
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds); // STDIN_FILENO es el descriptor de archivo para la entrada estándar (tecl
	    // Ejecuta la función select para esperar hasta que haya algún mensaje disponible para leer en alguno de los canales
    int nfds = sockfd + 1; // nfds es el número máximo de descriptores de archivo + 1
    if (select(nfds, &readfds, NULL, NULL, NULL) < 0) {
      perror("Error en select");
      return 1;
    }

    // Si hay un mensaje disponible para leer en el socket, lo procesa
    if (FD_ISSET(sockfd, &readfds)) {
      // Crea un buffer para almacenar el mensaje recibido
      char buf[BUF_SIZE];
      memset(buf, 0, BUF_SIZE);

      // Crea una estructura sockaddr_in para almacenar la dirección del cliente
      struct sockaddr_in cli_addr;
      socklen_t cli_addr_len = sizeof(cli_addr);

      // Recibe el mensaje del cliente
      ssize_t n = recvfrom(sockfd, buf, BUF_SIZE - 1, 0, (struct sockaddr*) &cli_addr, &cli_addr_len);
      if (n < 0) {
        perror("Error al recibir mensaje del cliente");
        continue;
      }

      // Obtiene el nombre y el puerto del cliente
      char host[NI_MAXHOST];
      char service[NI_MAXSERV];
      if (getnameinfo((struct sockaddr*) &cli_addr, cli_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, 0) < 0) {
        perror("Error al obtener información del cliente");
        continue;
      }

      // Procesa el comando recibido
      if (buf[0] == 't') {
        // Obtiene la hora actual
        time_t rawtime;
        time(&rawtime);
        struct tm* timeinfo = localtime(&rawtime);

        // Crea el mensaje de respuesta con la hora
        char response[BUF_SIZE];
        strftime(response, BUF_SIZE, "Hora: %H:%M:%S\n", timeinfo);

        // Envía el mensaje de respuesta al cliente
        if (sendto(sockfd, response, strlen(response), 0, (struct sockaddr*) &cli_addr, cli_addr_len) < 0) {
          perror("Error al enviar mensaje de respuesta al cliente");
          continue;
        }
      } else if (buf[0] == 'd') {

	while (buf[0] != 'q') 
 	 {
		FD_ZERO(&set);
		FD_SET(0, &set);
		FD_SET(sd, &set);

		if (-1 == select(sd + 1, &set, NULL, NULL, NULL)) 
  		 {		
			perror("Error while waiting for data");
			return -1;
		}

		if (FD_ISSET(sd, &set))
			readsize = recvfrom(sd, &buf, 2*sizeof(char), 0, (struct sockaddr*) &input_addr, &input_len);
		else if (FD_ISSET(0, &set))
			readsize = read(0, &buf, 2*sizeof(char));
		
		if (readsize == -1) 
    		{
			perror("Error ocurred while reciving");
			close(sd);
			return -1;
		}
		else if (readsize == 0) 
   		 {
			printf("Client has performed a shutdown\n");
			buf[0] = 'q';
		}
		else
		{
			if (FD_ISSET(sd, &set)) 
			{
				char hostname[NI_MAXHOST] = "";
				char port[NI_MAXSERV] = "";

				if (getnameinfo((struct sockaddr*) &input_addr, input_len, hostname, NI_MAXHOST, port, NI_MAXSERV, 0)) 
				{
					perror("Error getting info from name");
					return -1;
				}

				printf("Recibí %i bytes de %s:%s\n", readsize, hostname, port);
			}

			if (buf[0] == 'd') 
			{
				time_t t;
				struct tm *loctime;
				char buffer[256];
				t =  time(NULL);
				loctime = localtime(&t);
				strftime(buffer,256,"%Y-%m-%d", loctime);

				if (FD_ISSET(0, &set))
					printf("%s\n", buffer);
				else if (FD_ISSET(sd, &set)) 
				{
					int writesize = sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr *)&input_addr, input_len);
					if (writesize == -1) 
					{
						perror("Error while sending back to client");
						return -1;
					}
				}
			} 
			else if (buf[0] == 't') 
			{
				time_t t;
				struct tm *loctime;
				char buffer[256];
				t =  time(NULL);
				loctime = localtime(&t);
				strftime(buffer,256,"%r", loctime);

				if (FD_ISSET(0, &set))
					printf("%s\n", buffer);
				else if (FD_ISSET(sd, &set)) 
				{
					int writesize = sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr *)&input_addr, input_len);
					if (writesize == -1) 
					{
						perror("Error while sending back to client");
						return -1;
					}
				}
			}
			else if (buf[0] == 'q')
				printf("Comando de finalización recibido, saliendo…\n");
			else
				printf("Comando no soportado %s", buf);
		}
	}

	close(sd);
	return 0;
}
