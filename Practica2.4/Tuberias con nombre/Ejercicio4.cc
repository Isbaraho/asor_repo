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
// Asegurarse de que se haya proporcionado argumento
if (argc< 2) {
fprintf(stderr,"Se necesita un argumento\n");
exit(1);
}
// Abrir la tuberia en modo solo escritura
int fd = open("mi_tuberia", O_WRONLY);
// Escribir el primer argumento en la tubería
write(fd, argv[1], strlen(argv[1]));

// Cierra la tubería
close(fd);
return 0;
}
