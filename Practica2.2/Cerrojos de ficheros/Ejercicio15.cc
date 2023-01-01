

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

int main()
{
    int df=open("/home/usuarioso/Descargas/PR2/ficheros_p2/student-records/hola.txt", O_RDWR);
    struct stat hola;
    fstat(df, &hola);
    int a = hola.st_size;

    if(lockf(df, F_LOCK, a) == -1)
    {
        perror("Se ");
    }
    time_t t;
    struct tm * tInfo;
    char buffer[80];

    time ( &t );
    tInfo = localtime ( &t );

    strftime(buffer,80,"%A, %d de %B de %Y, %H:%M", tInfo);

    printf("Fecha y hora (en ingles) : %s\n", buffer );
    sleep(10);

    if(lockf(df, F_ULOCK, a) == -1)
    {
        perror("Se ");
    }
    sleep(10);
     return 1;
}
