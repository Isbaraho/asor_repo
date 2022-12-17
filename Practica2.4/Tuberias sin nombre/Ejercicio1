
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    int pipefd[2]; // Array para almacenar los descriptores del extremo de lectura y escritura de la tubería sin nombre
    pid_t cpid; // Variable para almacenar el identificador del proceso hijo
    char *command1[argc]; // Array para almacenar los argumentos del primer comando
    char *command2[argc]; // Array para almacenar los argumentos del segundo comando
    int i;

    if (argc < 4) { // Verificamos que se hayan ingresado al menos 4 argumentos (nombre del programa, comando1, argumento1 y "|")
    fprintf(stderr, "Uso: %s comando1 argumento1 | comando2 argumento2\n", argv[0]);
    exit(EXIT_FAILURE);
    }

    // Copiamos los argumentos de los comandos en los arrays command1 y command2
    for (i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "|") == 0) 
        { // Si encontramos el separador "|", comenzamos a copiar los argumentos del segundo comando
            command1[i-1] = NULL; // Añadimos un elemento nulo al final del array para indicar el final de los argumentos del primer comando
            command2[0] = argv[i+1]; // El primer argumento del segundo comando es el siguiente al separador "|"
            i++; // Saltamos el separador "|"
        } 
        else 
        {
            if (command2[0] == NULL) 
            { // Si estamos procesando los argumentos del primer comando
                command1[i-1] = argv[i];
            } 
            else 
            { // Si estamos procesando los argumentos del segundo comando
                command2[i-1] = argv[i];
            }
        }
    }
    command2[argc-i] = NULL; // Añadimos un elemento nulo al final del array para indicar el final de los argumentos del segundo comando

    if (pipe(pipefd) == -1) 
    { // Creamos la tubería sin nombre
        perror("Error al crear la tubería sin nombre");
        exit(EXIT_FAILURE);
    }

    cpid = fork(); // Creamos un proceso hijo
    if (cpid == -1) 
    { // Si la llamada a fork() falló
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) 
    { // Si estamos en el proceso hijo
        // Cerramos el extremo de escritura de la tubería sin nombre, ya que no lo vamos a utilizar en el proceso hijo
        close(pipefd[1]);

        // Redirigimos la entrada estándar al extremo de lectura de la tubería sin nombre
        if (dup2(pipefd[0], STDIN_FILENO) == -1) 
        {
            perror("Error al redirigir la entrada estándar");
            exit(EXIT_FAILURE);
        }

        // Ejecutamos el segundo comando con sus argumentos
        if (execvp(command2[0], command2) == -1)
        {
            perror("Error al ejecutar el segundo comando");
            exit(EXIT_FAILURE);
        }
    } 
    else 
    { // Si estamos en el proceso padre
        // Cerramos el extremo de lectura de la tubería sin nombre, ya que no lo vamos a utilizar en el proceso padre
        close(pipefd[0]);

        // Redirigimos la salida estándar al extremo de escritura de la tubería sin nombre
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) 
        {
        perror("Error al redirigir la salida estándar");
        exit(EXIT_FAILURE);
        }

        // Ejecutamos el primer comando con sus argumentos
        if (execvp(command1[0], command1) == -1) 
        {
        perror("Error al ejecutar el primer comando");
        exit(EXIT_FAILURE);
        }
    }

    return 0;
}
