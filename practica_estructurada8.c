/*
Desarrolle un programa que solicite el ingreso de un numero entero, que indica a su vez cuantos números
enteros ingresara el usuario. Crear en memoria dinámica el vector para almacenar el tamaño exacto de los
datos y leer los enteros que serán guardados en el vector “dinámico”. Informar el promedio de los datos
ingresados.
*/

#include <stdio.h>
#include <stdlib.h>

void cargaVector(int *, int);
void mostrarVector(int *, int);
float calcPromedio(int *, int);

int main()
{
    int tam, *vector;
    float promedio;

    printf("Ingrese el tamanio del vector a cargar: ");
    scanf("%d", &tam);

    system("cls");

    vector = (int *)malloc(tam * sizeof(int));

    cargaVector(vector, tam);

    system("cls");

    mostrarVector(vector, tam);

    promedio = calcPromedio(vector, tam);

    printf("\nEl promedio de los numeros ingresados es de: %.2f", promedio);

    free(vector);
    return 0;
}

void cargaVector(int *vec, int cant)
{
    int i, num;

    for (i = 0; i < cant; i++)
    {
        printf("\nIngrese el numero %d ", i + 1);
        scanf("%d", &vec[i]);
    }
}

void mostrarVector(int *vec, int cant)
{
    int i;

    printf("\n---------TU VECTOR---------\n");

    for (i = 0; i < cant; i++)
    {
        printf("%d\n", vec[i]);
    }
}

float calcPromedio(int *vec, int cant)
{
    int i, acum = 0;
    float prom = 0;

    for (i = 0; i < cant; i++)
    {
        acum += vec[i];
    }

    prom = (float)acum / cant;

    return prom;
}