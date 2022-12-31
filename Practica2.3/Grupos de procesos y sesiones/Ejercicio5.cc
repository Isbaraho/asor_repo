#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
 {
    struct rlimit a;
    int pid=getpid();
    printf("PID: %i \n",pid);
    int ppid=getppid();
      printf("PPID: %i \n",ppid);
    int pgid=getpgid(pid);
    printf("PGID: %i \n",pgid);
      int sid=getsid(pid);
    printf("SID: %i \n",sid);
    char *path = malloc(sizeof(char)*(4096 + 1));
    char *rpath = getcwd(path, 4096 + 1);

    getrlimit(RLIMIT_NOFILE, &a);
    printf("Máximo número %li", a.rlim_max);
    printf("Directorio: %s\n",path);
    return 0;
 }
