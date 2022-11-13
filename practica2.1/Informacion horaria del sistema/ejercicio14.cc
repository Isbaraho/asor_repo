/* localtime example */
#include <stdio.h>
#include <time.h>

int main ()
{
  time_t t;
  struct tm * tInfo;

  time ( &t );
  tInfo = localtime ( &t );
  printf ("El año actual es %d \n", tInfo->tm_year + 1900);
  
  return 0;
}
