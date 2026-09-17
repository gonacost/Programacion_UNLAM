/*
 Se debe realizar un programa para ingresar los DNI de los asistentes a un evento. Se cargan todos los DNI
hasta que se recibe un DNI igual 0. Al finalizar mostrar el listado de todoslos DNI ingresados. Los datos deben
almacenarse en un vector en memoria dinámica al no saber la cantidad comenzar con un vector de 5
elementos y si es necesario y el vector se llena ir aumentando la capacidad del vector de 5 en 5.
*/

#include <stdio.h>
#include <stdlib.h>

int *cargaVector(int *, int, int *);
void mostrarVector(int *, int);

int main()
{
    int *vec, dni;
    int cantidadReal;

    vec = (int *)malloc(5 * sizeof(int));

    vec = cargaVector(vec, 5, &cantidadReal);

    mostrarVector(vec, cantidadReal);

    free(vec);
    return 0;
}

int *cargaVector(int *vector, int cant, int *cant_cargada)
{
    int i = 0, dni;
    int *aux;

    printf("A continuacion cargue 5 dni (dni = 0, para fin): \n");
    scanf("%d", &dni);

    while (dni > 0)
    {
        if (i == cant)
        {
            aux = realloc(vector, (cant + 5) * sizeof(int));
            if (aux == NULL)
            {
                printf("\nERROR. no hay lugar en memoria... fin del programa");
                exit(1);
            }
            else
            {
                vector = aux;
                cant = cant + 5;
            }
        }

        vector[i] = dni;

        printf("A continuacion cargue 5 dni (dni = 0, para fin): \n");
        scanf("%d", &dni);

        i++;
    }

    *cant_cargada = i;

    return vector;
}

void mostrarVector(int *vector, int cant)
{
    int i;

    printf("\n---------SU LISTA DE DNI---------\n");
    for (i = 0; i < cant; i++)
    {
        printf("%d\n", vector[i]);
    }
}
