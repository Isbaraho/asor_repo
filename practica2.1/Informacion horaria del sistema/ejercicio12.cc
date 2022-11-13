
#include <stdio.h>
#include <time.h>
 
int main ()
{
    time_t seconds;
     
    seconds = time(NULL);
    printf("Segundos desde el epoch = %ld\n", seconds);
     
    return(0);
}
