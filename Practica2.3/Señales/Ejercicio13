
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

volatile int stop = 0;

static void handler(int signo)
{
	if (signo == SIGUSR1) stop = 1;
}

int main(int argc, char * * argv)
{
	if (argc != 2) {
        printf("Uso: %i segundos\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Perparar la máscara para desbloquear la señal SIGUSR1.

	sigset_t mask;

	if (sigemptyset(& mask) == -1) perror("sigemptyset()");

	if (sigaddset(& mask, SIGUSR1) == -1) perror("sigaddset()");

	// Desbloquear la señal SIGUSR1.

	if (sigprocmask(SIG_UNBLOCK, & mask, NULL) == -1) perror("sigprocmask()");

	// Preparar la estructura para el manejador.

	struct sigaction sa;

	sa.sa_handler = handler;

	// Instalar el manejador.

	if (sigaction(SIGUSR1, & sa, NULL) == -1) perror("sigaction()");

	// Bucle de espera.

	int seconds = atoi(argv[1]);
	int i = 0;

	while (i < seconds && ! stop) {
		sleep(1);
		i++;
	}

	// Comprobar y eliminar.

	if (stop) {
		printf("Abortado \n");
	} else {
		printf("Eliminando \n");

		unlink(argv[0]);
	}

	exit(EXIT_SUCCESS);
}
