#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int cont = 1;

void hand()
{
    unlink("pep.txt");
    printf("El fichero ha sido borrado \n");
    cont = 0;
}

void hand2() // SIGUSR1
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, NULL);
    printf("Señal detenida\n");
    cont = 0;
}

int main(int argc, char ** argv)
{
    unsigned int a = 10;

    if(argc < 2)
    {
        fprintf(stderr, "Faltan argumentos");
        return 0;
    }
    else if((a = atoi(argv[1])) == 0)
    {
        fprintf(stderr, "Error en argumentos");
        return 0;
    }

    struct sigaction act;

    sigaction(SIGALRM, NULL, &act);
    act.sa_handler = hand;
    sigaction(SIGALRM, &act, NULL);

    struct sigaction act2; sigaction(SIGUSR1, NULL, &act2);
    act2.sa_handler = hand2;
    sigaction(SIGUSR1, &act2, NULL);

   

    alarm(a);
    //kill(getpid(), SIGUSR1);
    while(cont)
    {

    }
  

    return 0;
}
