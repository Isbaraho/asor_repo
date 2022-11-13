

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    if(setuid(0) == -1)
    {
      printf("Codigo de error %d", errno);
      printf("Mensaje %s", strerror(errno));
    }

    return 1;
}
