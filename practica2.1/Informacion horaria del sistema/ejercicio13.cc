
#include <stdio.h>
#include <sys/time.h>
#include <stdio.h>
 
int main ()
{
    int i = 0;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    
    while (i<1000000)
    {
        i++;
    }
    gettimeofday(&end,NULL);
    perror("hola");
    long final = 1000*end.tv_sec + end.tv_usec;
    long inicial = 1000*start.tv_sec + start.tv_usec;
   
    long tEmpleado = final -inicial;
    printf("Tiempo empleado %ld microsegundos", tEmpleado);

    return 1;
}
