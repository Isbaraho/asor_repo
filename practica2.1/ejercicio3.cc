#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    // El numero de errores se ha ajustado de 255 a 134
    // ya que no hay tantos errores posibles.
    for(int i = 0; i < 134; i++)
    {
        printf("Mensaje numero %d: %s \n", i, strerror(i));
    }

    return 1;
}
