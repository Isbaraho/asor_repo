#include <studio.h>
#include <stdlib.h>
#include <sys/utsname.h>
struct utsname ubameData;


int main()
{
    uname(&unameData);
    printf("%s",unameData.sysname);
    return 0;
}
