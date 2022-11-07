#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    
    printf("Longitud maxima de los args %lu \n",sysconf(_SC_ARG_MAX));

    printf("Numero maximo de hijos %lu \n",sysconf(_SC_CHILD_MAX));

    printf("Numero maximo de ficheros abiertos %lu \n",sysconf(_SC_OPEN_MAX));
    return 0;
}
