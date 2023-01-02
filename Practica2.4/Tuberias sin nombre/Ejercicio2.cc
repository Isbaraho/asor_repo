#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv) 
{
    int p_h[2]; 
    int h_p[2]; 
    pid_t pid; 
    int contM = 0;
    char buf;
    char buf2;
    int i = 0;

    if (pipe(p_h) == -1) 
    {
        perror("Error al crear la tubería sin nombre p_h");
        exit(EXIT_FAILURE);
    } 
    
    if (pipe(h_p) == -1) 
    {
        perror("Error al crear la tubería sin nombre h_p");
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

            close(p_h[1]);
            close(h_p[0]);

            while ((read(p_h[0], &buf, 1) > 0) && i < 10) 
            {
                if(buf == '\n') // No se por que, pero cuando se manda un mensaje cuenta el intro como parte de el 
                {
                    printf("Hijo: Mensaje recibido: Intro \n");
                }
                else
                {
                    printf("Hijo: Mensaje recibido: %c \n", buf);
                }
                sleep(1);

                write(h_p[1], "l\n", 1);

                i++;
            }
            write(h_p[1], "q", 1);

            close(p_h[0]);
            close(h_p[1]);

        break;

        default:

 
            close(p_h[0]);
            close(h_p[1]);

            while(read(STDIN_FILENO, &buf2,1) > 0 )
            {
                write(p_h[1], &buf2,1);
                read(h_p[0], &buf2,1);

                if(buf2 == 'q')
                {
                    break;
                }
            }

            close(p_h[1]);
            close(h_p[0]);

            wait(NULL);
            exit(EXIT_SUCCESS);

        break;  
    }

    return 1;
}
