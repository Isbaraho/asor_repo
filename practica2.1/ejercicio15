#include <stdio.h>
#include <time.h>

int main ()
{
  time_t t;
  struct tm * tInfo;
  char buffer[80];

  time ( &t );
  tInfo = localtime ( &t );

  strftime(buffer,80,"%A, %d de %B de %Y, %H:%M", tInfo);
  
  printf("Fecha y hora (en ingles) : %s\n", buffer );
  return 0;
}
