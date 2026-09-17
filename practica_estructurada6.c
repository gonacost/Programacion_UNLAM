/*
Al programa anterior agregarle una función que reciba la dirección de inicio del vector y un número a buscar
y retorne un puntero al dato encontrado o NULL sino lo encuentra. En el main agregar un proceso de
búsqueda que se repita hasta ingresar un número negativo o cero a buscar. Si se lo encontró se debe indicar
en qué posición del vector estaba (calcular dicha posición utilizando la dirección retornada)
*/

#include <stdio.h>
#include <stdlib.h>

void cargaVector(int *vec, int tam);
int *busqueda(int *vec, int x, int ce);

int main ()
{
    int *vector = (int *)malloc(10 * sizeof(int));
    int buscado, *encontrado;
    cargaVector(vector, 10);
    
    printf("\nIngrese un numero a buscar. (0 o negativo para finalizar): ");
    scanf("%d", &buscado);

    while (buscado > 0)
    {
        encontrado = busqueda(vector, buscado, 10);

        if (encontrado != NULL)
        {
            printf("\nSe encuentra en la posicion %d", (int) (encontrado - vector));
        }
        else
        {
            printf("\nNo se encontro el numero");
        }
        

        printf("\nIngrese un numero a buscar. (0 o negativo para finalizar): ");
        scanf("%d", &buscado);
    }
    
    free(vector);
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

int *busqueda(int *vec, int x, int ce)
{
    int i = 0;

    while (i < ce)
    {
        if (*(vec + i) == x)
        {
            return (vec + i);
        }
        else
        {
            i++;
        }
        
    }
    
    return NULL;
}

