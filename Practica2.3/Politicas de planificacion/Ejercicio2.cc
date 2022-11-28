#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main()
 {
    int pid=0;
    struct sched_param p;
    int sche=sched_getscheduler(pid);
    if(sche==SCHED_OTHER)
    {
        printf("Estandar\n");
    }
    else if( sche==SCHED_FIFO)
    {
        printf("FIFO\n");
    }
    else 
    {
        printf("Round Robin\n");
    }
    int prio=sched_getparam(pid,&p );
    printf("Prioridad: %i \n", prio);
    int max,min;
    max=sched_get_priority_max(sche);
    min=sched_get_priority_min(sche);
    printf("Maximo: %i\n", max);
    printf("Minimo: %i\n", min);
    return 0;
 }
