/*
 Crear una función que defina en memoria dinámica un vector de 10 elementos cargados de forma aleatoria
con números de 2 cifras, la función debe mostrar los datos generados en forma ordenada de mayor a menor.
Desde el main invocar la función 5 veces para visualizar 5 vectores distintos. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 10

void generarYMostrarVector();

int main() 
{
    srand(time(NULL)); // importante: llamar solo una vez, fuera del bucle

    for (int i = 0; i < 5; i++) 
    {
        printf("Vector %d:\n", i + 1);
        generarYMostrarVector(); 
    }

    return 0;
}

void generarYMostrarVector() 
{
    int *vector = (int *) malloc(TAM * sizeof(int));

    if (vector == NULL) 
    {
        printf("Error al reservar memoria\n");
        return;
    }

    // Cargar el vector con numeros aleatorios de 2 cifras (10 a 99)
    for (int i = 0; i < TAM; i++) 
    {
        vector[i] = rand() % 90 + 10;
    }

    // Ordenar de mayor a menor (burbuja)
    for (int i = 0; i < TAM - 1; i++) 
    {
        for (int j = 0; j < TAM - 1 - i; j++) 
        {
            if (vector[j] < vector[j + 1]) 
            {
                int aux = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = aux;
            }
        }
    }

    // Mostrar el vector ordenado
    for (int i = 0; i < TAM; i++) 
    {
        printf("%d ", vector[i]);
    }
    printf("\n");

    free(vector);
}