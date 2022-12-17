
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
    {
    int p_h[2]; // Tubería padre-hijo
    int h_p[2]; // Tubería hijo-padre
    pid_t cpid; // Variable para almacenar el identificador del proceso hijo
    char buf; // Buffer para leer y escribir en las tuberías
    int count = 0; // Contador de mensajes enviados

    // Creamos las tuberías
    if (pipe(p_h) == -1 || pipe(h_p) == -1) 
    {
        perror("Error al crear las tuberías");
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
        // Cerramos los extremos de escritura de las tuberías, ya que no los vamos a utilizar en el proceso hijo
        close(p_h[1]);
        close(h_p[1]);

        // Leemos mensajes enviados por el padre y los escribimos en la salida estándar
        while (read(p_h[0], &buf, 1) > 0) 
        {
            printf("Hijo: Mensaje recibido: %c\n", buf);
            sleep(1); // Esperamos 1 segundo
            write(h_p[1], "l", 1); // Enviamos confirmación al padre
        }

        // Cerramos los extremos de lectura de las tuberías
        close(p_h[0]);
        close(h_p[0]);

        // Finalizamos el proceso hijo
        exit(EXIT_SUCCESS);
    } 
    else 
    { // Si estamos en el proceso padre
        // Cerramos los extremos de lectura de las tuberías, ya que no los vamos a utilizar en el proceso padre
        close(p_h[0]);
        close(h_p[0]);

        // Leemos mensajes de la entrada estándar y los enviamos al hijo
        while (count < 10 && read(STDIN_FILENO, &buf, 1) > 0) 
        {
            write(p_h[1], &buf, 1); // Enviamos mensaje al hijo
            read(h_p[1], &buf, 1); // Leemos confirmación del hijo
            if (buf == 'l')
            { // Si hemos recibido la confirmación
                count++;
            }
            else if (buf == 'q')
            { // Si hemos recibido la señal de finalización
                break;
            }
        }

            // Cerramos los extremos de escritura de las tuberías
            close(p_h[1]);
            close(h_p[1]);

            // Esperamos a que el hijo finalice
            wait(NULL);

            // Finalizamos el proceso padre
            exit(EXIT_SUCCESS);
    }
}
