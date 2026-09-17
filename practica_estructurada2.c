/*
Realizar una función que permita ingresar por teclado un valor entero, un flotante y un carácter. La función
no debe retornar ningún valor. Las variables se declaran y se muestran en el programa principal.
*/

#include <stdio.h>

void ingrVariables(int *entr, float *decimal, char *carac);

int main()
{
    int entero;
    float real;
    char caracter;

    ingrVariables(&entero, &real, &caracter);

    printf("%d %f %c", entero, real, caracter);

    return 0;
}

void ingrVariables(int *entr, float *decimal, char *carac)
{
    printf("Ingrese un valor entero: ");
    scanf("%d", entr);

    printf("Ingrese un valor decimal: ");
    scanf("%f", decimal);

    printf("Ingrese un caracter: ");
    scanf(" %c", carac);
}