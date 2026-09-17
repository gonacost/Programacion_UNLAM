/*
Ingresar nombre y DNI de los alumnos de un curso. Como máximo el curso puede tener 50 alumnos. La carga
finaliza con un alumno de nombre FIN. Luego de cargar los alumnos se pide:
a. Ingresar nombres de a uno en uno y buscarlos. Si el nombre está en el curso mostrar su DNI y sino
informar que no está. Seguir ingresando nombres hasta que se ingrese un nombre igual a
NOBUSCARMAS.
b. Mostrar el listado de alumnos ordenado alfabéticamente de menor a mayor.
*/

#include <stdio.h>
#include <string.h>

#define TAM 50

int cargaAlumnos(char[][30], int[]);
int busqueda(char[][30], char[], int);
int busquedadni(int[], int, int);
void mostrarAlumno(char[][30], int[], int);
void ordenAlfabetico(char[][30], int[], int);

int main()
{
    int cant_alumnos, dnis[TAM], pos;
    char nombres[TAM][30], nombre[30];

    cant_alumnos = cargaAlumnos(nombres, dnis);

    printf("Ingrese un nombre a buscar.('NOBUSCARMAS' para dejar de buscar): \n");
    fgets(nombre, 30, stdin);

    nombre[strcspn(nombre, "\n")] = '\0';

    while (strcmp(nombre, "NOBUSCARMAS") != 0)
    {
        pos = busqueda(nombres, nombre, cant_alumnos);

        if (pos != -1)
        {
            printf("DNI: %d\n", dnis[pos]);
        }
        else
        {
            printf("No se encontro al alumno buscado.\n");
        }

        printf("Ingrese un nombre a buscar.('NOBUSCARMAS' para dejar de buscar): \n");
        fgets(nombre, 30, stdin);

        nombre[strcspn(nombre, "\n")] = '\0';
    }

    ordenAlfabetico(nombres, dnis, cant_alumnos);

    mostrarAlumno(nombres, dnis, cant_alumnos);

    return 0;
}

int cargaAlumnos(char nomb[][30], int dni[])
{
    int numdni, i = 0, pos;
    char nombre[30];

    printf("Cargue el nombre del alumno %d. ('FIN' para dejar de cargar alumnos): \n", i + 1);
    fgets(nombre, 30, stdin);

    nombre[strcspn(nombre, "\n")] = '\0';

    while ((strcmp(nombre, "FIN") != 0) && i < TAM)
    {
        printf("Cargue el DNI del alumno %d: \n", i + 1);
        scanf("%d", &numdni);

        while (getchar() != '\n');

        pos = busquedadni(dni, numdni, i);

        if (pos == -1)
        {
            dni[i] = numdni;
            strcpy(nomb[i], nombre);

            i++;
        }
        else
        {
            printf("El dni del alumno ya esta ingresado. \n");
        }

        printf("Cargue el nombre del alumno %d. ('FIN' para dejar de cargar alumnos): \n", i + 1);
        fgets(nombre, 30, stdin);

        nombre[strcspn(nombre, "\n")] = '\0';
    }

    return i;
}

int busqueda(char nomb[][30], char nombre[], int ce)
{
    int pos = -1, i = 0;

    while ((i < ce) && pos == -1)
    {
        if (strcmp(nomb[i], nombre) == 0)
        {
            pos = i;
        }
        else
        {
            i++;
        }
    }

    return pos;
}

int busquedadni(int dni[], int x, int ce)
{
    int i = 0, pos = -1;

    while (pos == -1 && i < ce)
    {
        if (dni[i] == x)
        {
            pos = i;
        }
        else
        {
            i++;
        }
    }

    return pos;
}

void ordenAlfabetico(char nomb[][30], int dni[], int ce)
{
    int auxdni, cota = ce - 1;
    char auxnombre[30];

    for (int i = 0; i < cota; i++)
    {
        for (int j = 0; j < ce - 1; j++)
        {
            if (strcmp(nomb[j], nomb[j + 1]) > 0)
            {
                strcpy(auxnombre, nomb[j]);
                strcpy(nomb[j], nomb[j + 1]);
                strcpy(nomb[j + 1], auxnombre);

                auxdni = dni[j];
                dni[j] = dni[j + 1];
                dni[j + 1] = auxdni;
            }
        }
    }
}

void mostrarAlumno(char nomb[][30], int dni[], int ce)
{
    int i;

    printf("\n------------LISTA DE ALUMNOS------------\n");
    for (i = 0; i < ce; i++)
    {
        printf("DNI: %d - NOMBRE: %s\n", dni[i], nomb[i]);
    }
    
}