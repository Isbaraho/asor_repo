#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  struct stat buff;
  char* hard = malloc(sizeof(char)*(5 + strlen(argv[1])));
	char* sym = malloc(sizeof(char)*(5 + strlen(argv[1])));
	strcpy(hard, argv[1]);
	strcpy(sym, argv[1]);

	hard = strcat(hard, ".hard");
	sym = strcat(sym, ".sym");
  
	int statint = stat(argv[1], &buff);
  mode_t mode = buff.st_mode;
  if(S_ISREG(mode))
  {
    if (link(argv[1],hard) == -1) {
			printf(" No se ha podido crear el enlace duro.\n");
		} else printf("Enlace duro creado.\n");

		if (symlink(argv[1],sym) == -1) {
			printf(" No se ha podido crear el enlace simbólico.\n");
		} else printf("Enlace simbólico creado.\n");
  }
  return 0;
}
