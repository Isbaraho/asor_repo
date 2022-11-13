#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Podemos ver si setuid esta activo observando EUID en comparación con UID

int main()
{
    printf("Id real: %d \n", getuid());
    printf("Id efectiva: %d \n", geteuid());
    return 1;
}
