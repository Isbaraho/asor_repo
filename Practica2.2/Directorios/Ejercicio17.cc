#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc,char**argv)
{
  DIR *fch;
  fch=opendir(argv[1]);
  struct stat buf;
  struct dirent *file;
  char link[100];
  char aux[100];
  off_t tam=0;
  int long;
  while((file=readdir(fch))!=NULL)
  {
    strcpy(aux,argv[1]);
    strcat(aux,"/");
    strcat(aux,file->d_name);
    if(buf.st_mode==S_IFDIR)
    {
      printf("%s/\n",file->d_name);
    }
    else if(buf.st_mode==S_IFLNK)
    {
      link[len]='\0';
      printf("%s->%s\n",file->d_name,link);
    }
    else if(buf.st_mode==S_IFREG)
    {
      printf("%s*\n",file->d_name);
    }
    if(!S_ISDIR(buf.st_mode))
    {
      size+=buf.st_size;
    }
  closedir(fch);
    return 1;
}
