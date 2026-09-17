/*
Hacer un programa que cargue un vector de 10 enteros y lo muestre usando una función para cargar y otra
mostrar sin utilizar subíndice
*/

#include <stdio.h>
#include <stdlib.h>

void cargaVector(int *vec, int tam);
void mostrarVector(int *vec, int tam);

int main ()
{
    int *vector = (int *)malloc(10 * sizeof(int));
    
    cargaVector(vector, 10);
    mostrarVector(vector, 10);

    return 0;
}

void cargaVector(int *vec, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("Ingrese el valor %d:\n", i + 1);
        scanf("%d", vec + i);
    }
    
}

void mostrarVector(int *vec, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("%d\n", *(vec + i));
    }
    
    
}