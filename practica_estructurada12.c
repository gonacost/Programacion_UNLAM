/*
Ingresar dos Strings, uno con el nombre y el otro con el apellido de una persona. Utilizando las funciones de
la biblioteca string.h generar un tercer string formado por: NOMBRE, APELLIDO (nombre coma espacio y
apellido) y mostrarlo
*/

#include <stdio.h>
#include <string.h>

int main()
{
    char nombre[25], apellido[25];
    char nombreCompleto[55];
    int tamanio, seguir = 1;

    printf("Ingrese su nombre: \n");
    fgets(nombre, 25, stdin);

    for (int i = 0; i < 25; i++)
    {
        if (nombre[i] == '\n')
        {
            nombre[i] = '\0';
        }
    }

    tamanio = strlen(nombre);

    for (int i = tamanio - 1; i >= 0; i--)
    {
        if (nombre[i] == ' ' && seguir == 1)
        {
            nombre[i] = '\0';
        }
        else if (nombre[i] != ' ')
        {
            seguir = 0;
        }
    }

    seguir = 1;

    printf("Ingrese su apellido: \n");
    fgets(apellido, 25, stdin);

    for (int i = 0; i < 25; i++)
    {
        if (apellido[i] == '\n')
        {
            apellido[i] = '\0';
        }
    }

    tamanio = strlen(apellido);

    for (int i = tamanio - 1; i >= 0; i--)
    {
        if (apellido[i] == ' ' && seguir == 1)
        {
            apellido[i] = '\0';
        }
        else if (apellido[i] != ' ')
        {
            seguir = 0;
        }
    }

    strcpy(nombreCompleto, nombre);

    strcat(nombreCompleto, ", ");
    strcat(nombreCompleto, apellido);

    printf("\nEl nombre completo es: %s", nombreCompleto);
}