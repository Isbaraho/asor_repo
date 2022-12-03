#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>


void printDatos(char *type){
    struct rlimit a;
    int pid=getpid();
    printf("PID: %i \n",pid);
    int ppid=getppid();
      printf("PPID: %i \n",ppid);
    int pgid=getpgid(pid);
    printf("PGID: %i \n",pgid);
      int sid=getsid(pid);
    printf("PGID: %i \n",sid);
    char *path = malloc(sizeof(char)*(4096 + 1));
    char *rpath = getcwd(path, 4096 + 1);

    getrlimit(RLIMIT_NOFILE, &a);
    printf("Máximo número %li", a.rlim_max);
    printf("Directorio: %s\n",path);
  free (path);
}

int main() {

  pid_t pid = fork();

  switch (pid) {
    case -1:
      perror("fork");
      exit(-1);
    break;
    case 0:;
      pid_t mi_ses= setsid(); //Creacion de una nueva sesión
      char *ncwd= chdir("/tmp"); //Cambiamos el directorio a tmp
      printDatos("Hijo");
        sleep(3);
      break;
    default:
        printDatos("Padre");
        int aux;
        wait(&aux);
        break;
  }

  return 0;
}

