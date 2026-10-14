/*
 El archivo ventas.dat contiene información histórica de las ventas realizadas por una empresa desde el
año 2014 al 2023. El formato de registro es el siguiente:
• Mes (entero)
• Año (entero)
• Dia (entero)
• Código de Producto (entero)
• Importe de la venta (real)
Se pide ingresar un rango de años y mostrar un cuadro ventas realizadas en cada mes de cada año. Por
ejemplo, si se ingresa desde 2020 a 2022 debe mostrar lo siguiente:
     Mes 1 Mes 2 Mes 3 ……. Mes 12
2020 xxx   xxx   xxx       xxx
2021 xxx   xxx   xxx       xxx
2022 xxx   xxx   xxx       xxx
Una vez configurados los años debe poder cambiarse la vista para en lugar de visualizar cantidad de
ventas, ver el detalle de importe por mes/año. El usuario podrá alternar las vistas las veces que quiera.
Agregar una opción para finalizar el programa.
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define ANIO_MAX 2023
#define ANIO_MIN 2014
#define CANT_ANIOS (ANIO_MAX - ANIO_MIN + 1)

typedef struct
{
    int mes;
    int anio;
    int dia;
    int codigo;
    float importe;
} sVENTAS;

void carga(int[][12], float[][12]);
void mostrarVentas(int[][12], int, int);
void mostrarImporte(float[][12], int, int);
int validaRango(int, int);

int main()
{
    int matrizVenta[CANT_ANIOS][12] = {0};
    float matrizImporte[CANT_ANIOS][12] = {0};
    int desde, hasta, opcion;

    printf("Ingrese anio DESDE (%d - %d): \n", ANIO_MIN, ANIO_MAX);
    desde = validaRango(ANIO_MIN, ANIO_MAX);

    printf("Ingrese anio HASTA (%d - %d): \n", ANIO_MIN, ANIO_MAX);
    hasta = validaRango(ANIO_MIN, ANIO_MAX);

    carga(matrizVenta, matrizImporte);

    opcion = 1;

    while (opcion != 3)
    {
        if (opcion == 1)
        {
            mostrarVentas(matrizVenta, desde, hasta);
        }
        else if (opcion == 2)
        {
            mostrarImporte(matrizImporte, desde, hasta);
        }

        printf("1) Ver cantidad de ventas.\n");
        printf("2) Ver importe vendido.\n");
        printf("3) Salir.\n");
        scanf("%d", &opcion);
    }

    printf("Programa Finalizado.");
    return 0;
}

void carga(int matrizventa[][12], float matrizimporte[][12])
{
    FILE *fp;
    sVENTAS venta;

    fp = fopen("ventas.dat", "rb");

    if (fp == NULL)
    {
        printf("ERROR AL ABRIR ARCHIVO.");
        getch();
        exit(1);
    }

    fread(&venta, sizeof(sVENTAS), 1, fp);

    while (!feof(fp))
    {
        matrizventa[venta.anio - ANIO_MIN][venta.mes - 1]++;
        matrizimporte[venta.anio - ANIO_MIN][venta.mes - 1] += venta.importe;

        fread(&venta, sizeof(sVENTAS), 1, fp);
    }

    fclose(fp);
}

void mostrarVentas(int matrizventa[][12], int linf, int lsup)
{
    int i, j;

    printf("\n     ");
    for (j = 1; j <= 12; j++)
    {
        printf("MES%-4d", j);
    }

    printf("\n");

    for (i = linf; i <= lsup; i++)
    {
        printf("%d ", i);

        for (j = 0; j < 12; j++)
        {
            printf("%-7d", matrizventa[i - ANIO_MIN][j]);
        }

        printf("\n");
    }
}

void mostrarImporte(float matrizimporte[][12], int linf, int lsup)
{
    int i, j;

    printf("\n     ");
    for (j = 1; j <= 12; j++)
    {
        printf("Mes%-9d", j);
    }
    printf("\n");

    for (i = linf; i <= lsup; i++)
    {
        printf("%d ", i);
        for (j = 0; j < 12; j++)
        {
            printf("%-12.2f", matrizimporte[i - ANIO_MIN][j]);
        }
        printf("\n");
    }
}

int validaRango(int linf, int lsup)
{
    int dato;

    scanf("%d", &dato);

    while (dato < linf || dato > lsup)
    {
        printf("ERROR. reingrese (%d - %d): ", ANIO_MIN, ANIO_MAX);
        scanf("%d", &dato);
    }
    
    return dato;
}