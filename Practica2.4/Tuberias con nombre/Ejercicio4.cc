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

int main(int argc, char *argv[]) {
// Abre la tubería en modo sólo escritura
int fd = open("mi_tuberia", O_WRONLY);
if (fd < 0) {
perror("Error al abrir la tubería");
return 1;
}

// Escribe el primer argumento en la tubería
if (argc > 1) {
write(fd, argv[1], strlen(argv[1]));
}

// Cierra la tubería
close(fd);
return 0;
}
