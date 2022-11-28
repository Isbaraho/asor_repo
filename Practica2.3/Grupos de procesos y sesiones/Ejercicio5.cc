#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main()
 {
    int pid=getpid();
    printf("PID: %i \n",pid);
    int ppid=getppid();
      printf("PPID: %i \n",ppid);
    char *path = malloc(sizeof(char)*(4096 + 1));
    char *rpath = getcwd(path, 4096 + 1);
    printf("Directorio: %i\n",path);
    return 0;
 }

    
