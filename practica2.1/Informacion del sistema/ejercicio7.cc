#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

 main()
{
    
    printf("Numero maximo de enlaces %ld \n",pathconf("/",_PC_LINK_MAX));

    printf("Tamaño maximo de una ruta  %ld \n",pathconf("/",_PC_PATH_MAX));

    printf("Tamaño maximo de un nombre de fichero %ld \n",pathconf("/",_PC_NAME_MAX));
    
}
