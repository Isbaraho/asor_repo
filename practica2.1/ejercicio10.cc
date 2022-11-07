#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    printf("Id real: %d \n", getuid());
    printf("Id efectiva: %d \n", geteuid());
    printf("Usuario: %s", getlogin());

    struct passwd *info = getpwuid(1000);
    printf(info);
    return 1;
}
