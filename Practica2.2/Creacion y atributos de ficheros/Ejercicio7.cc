#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    mode_t prev=umask(027);

    int df=open("pruebas.txt),O_CREAT|O_RDONLY,0777);
    
    mode_t last=umask(prev);

    return 1;
}
