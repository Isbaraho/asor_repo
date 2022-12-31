#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <time.h>

int main() {
  struct stat buff;
  int fch = open("pruebas",O_RDONLY|O_CREAT,S_IRUSR|S_IWUSR);
  printf("Major asociado: %li\n", (long) major(buff.st_dev));
	printf("Minor asociado: %li\n", (long) minor(buff.st_dev));
  printf("Numero de inodo: %li\n",buff.st_ino);
  printf("Tipo: %i\n",buff.st_mode);
  time_t t = buff.st_atime;
  struct tm *tm1= localtime(&t);
  printf("Último acceso: %d:%d\n", tm1->tm_hour, tm1->tm_min);
  close(fch);
  return 1;
}
