#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    printf("Id real: %d \n", getuid());
    printf("Id efectiva: %d \n", geteuid());
    printf("Usuario: %s", getlogin());

    struct passwd *info = getpwuid(1000);
    printf("Nombre de usuario: %d \n",info->pw_name);
    printf("Directorio home: &d \n",info->pw_dir);
    printf("Descripcion del usuario: %d \n",info->pw_gecos);
    return 1;
}
