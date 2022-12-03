#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv){

  if (argc < 2) {
    printf("ERROR: Introduce el comando.\n");
    return -1;
  }

  pid_t pid = fork();

  switch (pid) {
    case -1:
      perror("fork");
      exit(-1);
    break;
    case 0:;
      pid_t mi_ses = setsid(); 
      int fd = open("/tmp/daemon.out",O_CREAT | O_RDWR, 00777);
      int fderrest = open("/tmp/daemon.err", O_CREAT | O_RDWR, 00777);
      int enestnull = open("/dev/null", O_CREAT | O_RDWR, 00777);
      int newfiches = dup2(fd,2);
      int newerror = dup2(fderrest, 1);
      int newenesta = dup2(enestnull, 0);
    int exect=execvp(argv[1], argv + 1);
      if (exect== -1) {
        printf("ERROR: llamada fallida.\n");
        exit(-1);
      }
      break;
    default:
        printf("[Padre] Proceso %i (Padre: %i)\n",getpid(),getppid());
        break;
  }

  return 0;
}
