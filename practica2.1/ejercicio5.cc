#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/utsname.h>
struct utsname unameData;


int main()
{
    uname(&unameData);
    printf("%s",unameData.sysname);
    printf("%s",unameData.version);
    printf("%s",unameData.release);
    printf("%s",unameData.machine);
    printf("%s",unameData.nodename);
    printf("%s",unameData.__domainname);
    printf("\n");
    return 0;
}
