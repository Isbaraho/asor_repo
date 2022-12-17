#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main() {

  //Creamos otra tuberia
  mkfifo("mi_tuberia_2",0666);
  // Abrir las tuberías en sus modos
  int fd1 = open("mi_tuberia",O_RDONLY|O_NONBLOCK);
  int fd2=open("mi_tuberia_2",O_RDONLY|O_NONBLOCK);

  // Inicializar el conjunto de descriptores de archivo para select
  fd_set read_fds;
  FD_ZERO(&read_fds);
  FD_SET(fd1, &read_fds);
  FD_SET(fd2, &read_fds);

 while (1) {
    // Ejecutar select para esperar hasta que haya datos disponibles para leer
    int ret = select(FD_SETSIZE, &read_fds, NULL, NULL, NULL);

    // Si hay error, salir del bucle
    if (ret < 0) {
      perror("Error al ejecutar select");
      break;
    }
    if (FD_ISSET(fd1, &read_fds)) {
      // Leer de la tubería
      char buffer[BUFFER_SIZE];
      int bytes_read = read(fd1, buffer, BUFFER_SIZE);

      // Si se ha llegado al final de fichero, cerrar la tubería y volver a abrirla
      if (bytes_read == 0) {
        close(fd1);
        fd1 = open("mi_tuberia", O_RDONLY | O_NONBLOCK);
      } else {
        // Mostrar la tubería desde la que se ha leído y los datos leídos
        printf("Leyendo de mi_tuberia: %s", buffer);
      }
    }

      if (FD_ISSET(fd2, &read_fds)) {
      // Leer de la tubería
      char buffer[BUFFER_SIZE];
      int bytes_read = read(fd2, buffer, BUFFER_SIZE);

      // Si se ha llegado al final de fichero, cerrar la tubería y volver a abrirla
      if (bytes_read == 0) {
        close(fd2);
        fd2 = open("mi_tuberia_2", O_RDONLY | O_NONBLOCK);
      } else {
        // Mostrar la tubería desde la que se ha leído y los datos leídos
        printf("Leyendo de mi_tuberia_2: %s", buffer);
      }
    }
  }
}

