#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{

	if (argc < 2) {
        printf("Uso: %s comando [argumentos...]. Introducir comillas \n");
		exit(EXIT_FAILURE);
	}

	
	// Ejecutar el comando.

	if (system(argv[1]) == -1) {
		printf("Error: no se pudo ejecutar el comando\n");
        perror("system()");

		exit(EXIT_FAILURE);
	}

    printf("El comando terminó de ejecutarse \n");
	exit(EXIT_SUCCESS);
}


