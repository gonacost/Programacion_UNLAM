/*
Ej 1. Realizar un programa en “C” que contenga una función llamada registrarMedicion que permita cargar por teclado los datos de un reporte meteorológico:

Número de estación meteorológica (entero).
Temperatura registrada en °C (flotante).
Categoría del clima: 'S' para soleado, 'N' para nublado, 'L' para lluvioso (carácter).
La función no debe retornar ningún valor. Las tres variables deben estar declaradas en el main, 
ser modificadas dentro de la función y ser mostradas en la pantalla únicamente desde el main.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int numero_estacion;
    float temperatura_celsius;
    char categoria;
}sMEDICION;


void registrarMedicion(sMEDICION *);

int main()
{
    sMEDICION medicion;

    registrarMedicion(&medicion);

    printf("NUMERO DE ESTACION: %d\n", medicion.numero_estacion);
    printf("TEMPERATURA EN CELSIUS: %.2f\n", medicion.temperatura_celsius);
    printf("CATEGORIA DEL CLIMA: %c", medicion.categoria);

    return 0;
}

void registrarMedicion(sMEDICION *medicion)
{
    printf("Ingrese el NUMERO de estacion: \n");
    scanf("%d", &medicion->numero_estacion);

    printf("Ingrese la TEMPERATURA EN CELSIUS: \n");
    scanf("%f", &medicion->temperatura_celsius);

    printf("Ingrese la CATEGORIA del clima: \n");
    scanf(" %c", &medicion->categoria);
}