
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
 
int main ()
{
    int i = 0;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    
    while (i<1000000000)
    {
        i++;
    }
    gettimeofday(&end,NULL);
    long tEmpleado = end.tv_usec - start.tv_usec;
    printf("Tiempo empleado %ld microsegundos", tEmpleado);

    return 1;
}
