#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv) 
{
    int fd[2]; 
    pid_t pid; 
    
    if (argc < 4) 
    { 
         fprintf(stderr, "Uso: %s comando1 argumento1 | comando2 argumento2\n", argv[0]);
         exit(EXIT_FAILURE);
    } 



    if (pipe(fd) == -1) 
    {
        perror("Error al crear la tubería sin nombre");
        exit(EXIT_FAILURE);
    } 

    pid = fork(); 
    switch(pid)
    {
        case -1: 

            perror("Error al crear el proceso hijo");
            exit(EXIT_FAILURE);

        break;
        case 0:
            
            if (dup2(fd[0], STDIN_FILENO) == -1)  //0  
            {    
                perror("Error al redirigir la entrada estándar");
                exit(EXIT_FAILURE);
            }

            close(fd[1]);
            close(fd[0]);

            if(execlp(argv[3],argv[3],argv[4], (char*) 0) == -1)
            {  
                perror("Error al ejecutar el segundo comando");
                exit(EXIT_FAILURE);
            } 

        break;

        default:

            if (dup2(fd[1], STDOUT_FILENO) == -1)  //1
            {   
                perror("Error al redirigir la salida estándar");
                exit(EXIT_FAILURE);
            }  

            close(fd[1]);
            close(fd[0]);

            if(execlp(argv[1],argv[1],argv[2], (char*) 0) == -1)
            {
                perror("Error al ejecutar el primer comando");
                exit(EXIT_FAILURE);
            }   

        break;  
    }

    return 1;
}
