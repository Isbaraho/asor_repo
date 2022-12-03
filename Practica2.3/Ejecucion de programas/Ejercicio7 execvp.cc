#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * * argv)
{

	if (argc < 2) {
        printf("Uso: %s comando [argumentos...] \n");
		exit(EXIT_FAILURE);
	}

	// Crear otro hijo para que ejecute el código.

	pid_t pid = fork();

	switch (pid) {
		case -1:
            printf("Error: no se pudo crear el proceso hijo.");
			perror("fork()");

			exit(EXIT_FAILURE);
		case 0:
			// Ejecutar el comando.

			if (execvp(argv[1], argv + 1) == -1) {
                printf("Error: no se pudo ejecutar el comando \n");
				perror("execvp()");

				exit(EXIT_FAILURE);
			}
		default:
			// Esperar a que termine el hijo.

			wait(NULL);

			printf("El comando termino de ejecutarse\n");
			break;
	}

	exit(EXIT_SUCCESS);
}
