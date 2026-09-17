/*
Se ingresan código y precio unitario de los productos que vende un negocio. No se sabe la cantidad exacta de
productos, pero sí se sabe que son menos de 50. El código es alfanumérico de 3 caracteres y la carga de los
datos de productos termina con un código igual al “FIN”. Luego se registran las ventas del día y por cada venta
se ingresa el código de producto y cantidad de unidades vendidas terminando con una cantidad igual a 0. Se
solicita:
a. Calcular la recaudación total del día y el producto del cual se vendió menor cantidad de unidades.
b. Mostrar el listado de productos con su precio ordenado en forma alfabética por código de producto.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int carga(char[][4], float[]);
void cargaVenta(char[][4], float[], int[], int, float[]);
void mostrarVector(char[][4], float[], int);
int busqueda_cod(char[][4], char[], int);

int main()
{
    float precioUnitario[50], recaudacion_total[50] = {0}, acum_dia = 0;
    char codigo_producto[50][4];
    int acum_ventas[50] = {0}, cantidad_productos, menor_cant = 0;

    cantidad_productos = carga(codigo_producto, precioUnitario);

    cargaVenta(codigo_producto, recaudacion_total, acum_ventas, cantidad_productos, precioUnitario);

    system("cls");

    printf("\n-----------RECAUDACION DEL DIA-----------\n");

    for (int i = 0; i < cantidad_productos; i++)
    {
        acum_dia += recaudacion_total[i];
    }

    printf("La recaudacion del dia fue de $%.2f\n", acum_dia);

    for (int i = 0; i < cantidad_productos; i++)
    {
        if (acum_ventas[i] < acum_ventas[menor_cant])
        {
            menor_cant = i;
        }
    }

    printf("Producto con menor cantidad de ventas: %s\n", codigo_producto[menor_cant]);
    printf("Con: %d producto(s) vendido(s)", acum_ventas[menor_cant]);

    mostrarVector(codigo_producto, precioUnitario, cantidad_productos);

    return 0;
}

int carga(char cod[][4], float prec[])
{
    float precio;
    int i = 0, pos;
    char codigo[4];

    printf("Ingrese el codigo del producto. ('FIN' para terminar): \n");
    fgets(codigo, 4, stdin);

    codigo[strcspn(codigo, "\n")] = '\0';

    while ((strcmp(codigo, "FIN") != 0) && i < 50)
    {
        printf("Ingrese el precio unitario del producto: \n");
        scanf("%f", &precio);

        getchar();

        pos = busqueda_cod(cod, codigo, i);

        if (pos == -1)
        {
            prec[i] = precio;
            strcpy(cod[i], codigo);

            i++;
        }
        else
        {
            printf("Producto ya existente.");
        }

        printf("Ingrese el codigo del producto. ('FIN' para terminar): \n");
        fgets(codigo, 4, stdin);

        codigo[strcspn(codigo, "\n")] = '\0';
    }

    return i;
}

int busqueda_cod(char cod[][4], char busq[], int cant)
{
    int i = 0, pos = -1;

    while (pos == -1 && i < cant)
    {
        if (strcmp(cod[i], busq) == 0)
        {
            pos = i;
        }
        else
        {
            i++;
        }
    }

    return pos;
}

void cargaVenta(char cod[][4], float recaudacion[], int acum[], int cant, float prec[])
{
    int cant_unidades = 0, pos;
    float acum_monto = 0;
    char prod[4];

    printf("\n-----------REGISTRO DE VENTAS-----------\n");

    printf("Ingrese la cantidad de unidades a vender. (0 para fin): \n");
    scanf("%d", &cant_unidades);

    getchar();

    while (cant_unidades != 0)
    {
        printf("Ingrese el codigo del producto a vender: \n");
        fgets(prod, 4, stdin);

        prod[strcspn(prod, "\n")] = '\0';

        pos = busqueda_cod(cod, prod, cant);

        if (pos != -1)
        {
            acum[pos] += cant_unidades;
            acum_monto = cant_unidades * prec[pos];
            recaudacion[pos] += acum_monto;
        }
        else
        {
            printf("Codigo inexistente. \n");
        }

        printf("Ingrese la cantidad de unidades a vender. (0 para fin): \n");
        scanf("%d", &cant_unidades);

        getchar();
    }
}

void mostrarVector(char cod[][4], float prec[], int ce)
{
    float auxprec;
    int cota = ce - 1;
    char auxCode[4];

    for (int i = 0; i < cota; i++)
    {
        for (int j = 0; j < cota; j++)
        {
            if (strcmp(cod[j], cod[j + 1]) > 0)
            {
                strcpy(auxCode, cod[j]);
                strcpy(cod[j], cod[j + 1]);
                strcpy(cod[j + 1], auxCode);

                auxprec = prec[j];
                prec[j] = prec[j + 1];
                prec[j + 1] = auxprec;
            }
        }
    }

    for (int i = 0; i < ce; i++)
    {
        printf("Codigo %s - Precio %.2f\n", cod[i], prec[i]);
    }
}
