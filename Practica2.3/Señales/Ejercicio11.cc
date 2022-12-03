
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	sigset_t mask;

	if (sigemptyset(& mask) == -1) perror("sigemptyset()");

	if (sigaddset(& mask, SIGINT) == -1) perror("sigaddset()");

	if (sigaddset(& mask, SIGTSTP) == -1) perror("sigaddset()");

	if (sigprocmask(SIG_BLOCK, & mask, NULL) == -1) 
    {
		printf("Error: no pudo establecerse la máscara de bloqueo de las señales SIGINT y SIGTSTP.\n");
		perror("sigprocmask()");
		exit(EXIT_FAILURE);
	}

	char * sleep_secs = getenv("SLEEP_SECS");

	if (sleep_secs == NULL) 
    {
		printf("Error: no se pudo encontrar la variable de entorno SLEEP_SECS.\n");
		exit(EXIT_FAILURE);
	}

	sleep(atoi(sleep_secs));

	sigset_t pending;

	sigemptyset(& pending);

	// Recuperar las señales pendientes.

	if (sigpending(& pending) == -1) 
    {
		printf("Error: no se pudieron recuperar las señales pendientes.\n");
		perror("sigpending()");

		exit(EXIT_FAILURE);
	}

	// Comprobar si una de las señales pendientes es SIGINT.

	switch(sigismember(& pending, SIGINT)) {
		case -1:
			printf("Error: no se pudo comprobar si SIGINT es una de las señales pendientes.\n");
			perror("sigismember()");

			exit(EXIT_FAILURE);
		case 1:
			printf("Señal SIGINT recibida durante la suspensión y pendiente.\n");
    
            if (sigdelset(& mask, SIGINT) == -1) perror("sigdelset()");

            // Desbloquear la señal.

            if (sigprocmask(SIG_UNBLOCK, & mask, NULL) == -1) {
                printf("Error: no se pudo desbloquear la señal SIGSTP.\n");
                perror("sigprocmask()");

                exit(EXIT_FAILURE);
            }
            break;
    
    
    }

	// Comprobar si una de las señales pendientes es SIGTSTP.

	switch(sigismember(& pending, SIGTSTP)) {
                case -1:
                        printf("Error: no se pudo comprobar si SIGTSTP es una de las señales pendientes.\n");
                        perror("sigismember()");

                        exit(EXIT_FAILURE);
                case 1:
                        printf("Señal SIGTSTP recibida durante la suspensión y pendiente. Desbloqueando...\n");

                        if (sigdelset(& mask, SIGTSTP) == -1) perror("sigdelset()");

                        // Desbloquear la señal.

                        if (sigprocmask(SIG_UNBLOCK, & mask, NULL) == -1) {
                            printf("Error: no se pudo desbloquear la señal SIGSTP.\n");
                            perror("sigprocmask()");

                            exit(EXIT_FAILURE);
                        }
                        break;
        }

	printf("Fin del programa \n");

	exit(EXIT_SUCCESS);
}
