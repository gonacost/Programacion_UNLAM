/* Ejercicio 1 Un local de electrodomésticos necesita un programa para actualizar el inventario y las ventas mensuales de sus artículos.
Primeramente, se ingresa la información de los productos existentes, cada uno compuesto por:
·       Código (entero)
·       Descripción (cadena de hasta 30 caracteres)
·       Precio Unitario (número real)
·       Unidades Vendidas (acumuladas hasta el mes anterior, entero)
·       Monto Total Recaudado (acumulado hasta el mes anterior, real)
Se sabe que el comercio maneja un máximo de 80 productos. La carga inicial de productos finaliza cuando se ingresa un código 0 .
A continuación, se procesan los comprobantes de venta del mes actual. Por cada venta se ingresa:
•             Código de Producto (entero)
•             Cantidad Vendida (entero)
El ingreso de las ventas del mes finaliza cuando la cantidad vendida es igual a 0. Validar los datos ingresados
Se solicita:
1. Actualización: Por cada venta procesada, buscar el producto por su código y actualizar la cantidad total de unidades vendidas y el importe total recaudado. (Nota: Si el código ingresado no existe, mostrar un mensaje de advertencia).
2. Listado Final: Al terminar el ingreso de ventas, emitir un informe con todos los productos registrados que contenga:
CÓDIGO: XXXXX DESCRIPCIÓN: XXXXXXXXXXXXXXXXXXXXXXXXXX | UNIDADES TOTALES: XXXX | MONTO TOTAL: $XXXXX.XX */

/*
Ejercicio 1-b 

Al ejercicio anterior , incorporamos el siguiente punto

Al finalizar el procesamiento de ventas, se requiere almacenar en memoria un resumen histórico con el monto total abonado por cada una de las ventas procesadas.

Escriba un fragmento de código en C que:

Solicite al usuario la cantidad V de ventas que se realizaron.
Reserve dinámicamente un arreglo de números reales (float) para V elementos
Realice la validación correspondiente para verificar si la memoria fue asignada con éxito.
Libere la memoria al finalizar
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int codigo;
    char descripcion[31];
    float precio_unitario;
    int unidades_vendidas;
    float monto_recaudado;
} sPRODUCTO;

int carga_productos(sPRODUCTO[], int);
void carga_mes(sPRODUCTO[], int);
int busqueda(sPRODUCTO[], int, int);
void limpieza(char[]);
void informe(sPRODUCTO[], int);

int main()
{
    int cantidad_productos, ventas;
    float *montos;
    sPRODUCTO productos[80];

    cantidad_productos = carga_productos(productos, 80);

    printf("\n----------CARGA DE ESTE MES----------\n");

    carga_mes(productos, cantidad_productos);

    montos = (float *)malloc(cantidad_productos * sizeof(float));

    if (montos == NULL)
    {
        printf("No se pudo asignar la memoria\n");
    }
    else
    {
        for (int i = 0; i < cantidad_productos; i++)
        {
            montos[i] = productos[i].monto_recaudado;
        }
    }

    for (int i = 0; i < cantidad_productos; i++)
    {
        printf("Posicion [%d] - Codigo: %d --> Monto Acumulado: %.2f \n", i + 1, productos[i].codigo, montos[i]);
    }
    

    informe(productos, cantidad_productos);

    free(montos);
    montos = NULL;
    
    return 0;
}

void limpieza(char mensaje[])
{
    int len, i = 0;

    len = strlen(mensaje);

    for (i = 0; i < len; i++)
    {
        if (mensaje[i] == '\n')
        {
            mensaje[i] = '\0';
        }
    }
}

int carga_productos(sPRODUCTO productos[], int ce)
{
    int i = 0, auxcod;

    printf("Ingrese el CODIGO del producto %d (0 para fin): \n", i + 1);
    scanf("%d", &auxcod);

    while (getchar() != '\n')
        ;

    while (auxcod != 0 && i < ce)
    {
        productos[i].codigo = auxcod;

        printf("Ingrese la DESCRIPCION del producto:  \n");
        fgets(productos[i].descripcion, sizeof(productos[i].descripcion), stdin);

        limpieza(productos[i].descripcion);

        printf("Ingrese el PRECIO UNITARIO del producto: \n");
        scanf("%f", &productos[i].precio_unitario);

        printf("Ingrese la cantidad de UNIDADES VENDIDAS del producto: \n");
        scanf("%d", &productos[i].unidades_vendidas);

        printf("Ingrese el MONTO RECAUDADO del producto: \n");
        scanf("%f", &productos[i].monto_recaudado);

        i++;

        printf("Ingrese el CODIGO del producto %d (0 para fin): \n", i + 1);
        scanf("%d", &auxcod);

        while (getchar() != '\n')
            ;
    }

    return i;
}

void carga_mes(sPRODUCTO productos[], int ce)
{
    int pos, aux, auxcod;

    printf("Ingrese la CANTIDAD VENDIDA del producto (0 para fin): \n");
    scanf("%d", &aux);

    while (getchar() != '\n')
        ;

    while (aux != 0)
    {
        if (aux < 0)
        {
            printf("Cantidad invalida \n");
        }
        else
        {
            printf("Ingrese el CODIGO DEL PRODUCTO: \n");
            scanf("%d", &auxcod);

            while (getchar() != '\n')
                ;

            pos = busqueda(productos, auxcod, ce);

            if (pos == -1)
            {
                printf("CODIGO NO ENCONTRADO\n");
            }
            else
            {
                productos[pos].unidades_vendidas += aux;
                productos[pos].monto_recaudado += aux * productos[pos].precio_unitario;
            }
        }

        printf("Ingrese la CANTIDAD VENDIDA del producto (0 para fin): \n");
        scanf("%d", &aux);

        while (getchar() != '\n')
            ;
    }
}

int busqueda(sPRODUCTO productos[], int x, int ce)
{
    int pos = -1, i = 0;

    while (pos == -1 && i < ce)
    {
        if (productos[i].codigo == x)
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

void informe(sPRODUCTO productos[], int ce)
{
    printf("\n------------INFORME DE PRODUCTOS------------\n");

    for (int i = 0; i < ce; i++)
    {
        printf("Codigo: %d -- Descripcion: %s \n", productos[i].codigo, productos[i].descripcion);
        printf("Unidades vendidas: %d -- Monto recaudado: %.2f \n", productos[i].unidades_vendidas, productos[i].monto_recaudado);
        printf("\n");
    }
}

