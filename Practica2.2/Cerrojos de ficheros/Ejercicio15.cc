#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char ** argv) {
  int fd = open(argv[1], O_CREAT | O_RDWR, 00777);
  struct flock lock;
  int status = fcntl(fd, F_GETLK, &lock);
    if (lock.l_type == F_UNLCK) {
    printf("STATUS: Cerrojo desbloqueado.\n");
      time_t tim = time(NULL);
      struct tm *tm = localtime(&tim);
      char buffer[1024];
      sprintf (buffer, "Hora: %d:%d\n", tm->tm_hour, tm->tm_min);
      write(fd, &buffer, strlen(buffer));
      sleep(30);
      if (fcntl(fd, F_GETLK, &lock) == -1) {
        printf("ERROR:No se ha podido crear el cerrojo.\n");
        close(fd);
        return 1;
      } else
      close(fd);
    }

  } else {
    printf("STATUS: Cerrojo bloqueado.\n");
    close(fd);
    return 1;
  }

  close(fd);
}

