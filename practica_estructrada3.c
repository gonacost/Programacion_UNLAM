/*
Hacer un programa que cargue un vector de 10 enteros
y lo muestre usando una función para cargar y otra mostrar sin utilizar subíndices.
*/

#include <stdio.h>

#define TAM 10

// Declaración de funciones
void cargarVector(int *vec, int tam);
void mostrarVector(int *vec, int tam);

int main()
{
    int vector[TAM];

    // Llamadas a las funciones
    cargarVector(vector, TAM);
    mostrarVector(vector, TAM);

    return 0;
}

// Función para cargar el vector usando punteros
void cargarVector(int *vec, int tam)
{
    printf("CARGA DEL VECTOR:\n");
    for (int i = 0; i < tam; i++)
    {
        printf("Ingrese el elemento %d: ", i + 1);
        scanf("%d", vec + i); // equivalente a &vec[i]
    }
}

// Función para mostrar el vector usando punteros
void mostrarVector(int *vec, int tam)
{
    printf("\nELEMENTOS DEL VECTOR:\n");
    for (int i = 0; i < tam; i++)
    {
        printf("%d ", *(vec + i)); // equivalente a vec[i]
    }
    printf("\n");
}