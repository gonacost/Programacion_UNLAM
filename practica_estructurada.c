/*
Definir dos números enteros y dos punteros a dichos números. Accediendo mediante los punteros sumar
ambos números y mostrar el resultado por pantalla. 
*/

#include <stdio.h>

int main()
{
    int num1 = 2, num2 = 3;
    int *ptr1 = &num1, *ptr2 = &num2, resultado;
    
    resultado = *ptr1 + *ptr2;

    printf("Resultado de la suma: %d", resultado);

    return 0;
}