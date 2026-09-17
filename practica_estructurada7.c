/*
Cargar un vector de enteros con números aleatorios de 3 cifras máximo.
Realizar una función que retorne un puntero al mayor valor del vector.
Mostrar el máximo valor mediante el puntero y la posición en la cual se encuentra.
*/

#include <stdio.h>
#include <stdlib.h>

void cargaVector(int *vec, int cant);
void mostrarVector(int *vec, int cant);
int *buscarMayor(int *vec, int cant);

int main()
{
    int *vector, *punt, num, tam;

    printf("Ingrese el tamaño del vector: ");
    scanf("%d", &tam);

    vector = (int *)malloc(tam * sizeof(int));

    cargaVector(vector, tam);

    system("cls");

    mostrarVector(vector, tam);

    punt = buscarMayor(vector, tam);

    printf("\nEl maximo valor es: %d", *punt);

    printf("\nLa posicion es %d: ", (punt - vector) + 1);

    free(vector);
    return 0;
}

void cargaVector(int *vec, int cant)
{
    int i, num;

    for (i = 0; i < cant; i++)
    {
        printf("\nIngrese un numero entero de 3 cifras(%d): ", i + 1);
        scanf("%d", &num);

        while (num < 100 || num > 999)
        {
            printf("\nIncorrecto. Ingrese un numero entero de 3 cifras(%d): ", i + 1);
            scanf("%d", &num);
        }

        vec[i] = num;
    }
}

void mostrarVector(int *vec, int cant)
{
    int i;

    printf("\nTU VECTOR ES\n");

    for (i = 0; i < cant; i++)
    {
        printf("\n%d", vec[i]);
    }
}

int *buscarMayor(int *vec, int cant)
{
    int i, mayor = 0;

    for (i = 0; i < cant; i++)
    {
        if (vec[i] > vec[mayor])
        {
            mayor = i;
        }
    }

    return &vec[mayor];
}
