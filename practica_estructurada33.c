/*
En una ferretería se cuenta con un archivo binario llamado Productos.dat que contiene los productos comercializados. Se definió la siguiente estructura para el archivo:
codigo (entero)
descripcion (hasta 50 caracteres)
categoria (entero: 1 = Herramientas, 2 = Pinturas, 3 = Electricidad)
precio (float)
Debido a cambios en los costos de proveedores, se solicita realizar un programa en C que:
Ajuste masivo de precios: Solicite por teclado un porcentaje de aumento y el número de categoría a la cual aplicarlo. Actualice en el propio archivo Productos.dat
únicamente el precio de los productos que pertenezcan a esa categoría.
Conteo e informe: Informe por pantalla la cantidad total de registros grabados 
en el archivo y cuántos productos pertenecen a la categoría actualizada.
Exportación: Genere un archivo de texto plano denominado productos_actualizados.csv con encabezados
(Codigo;Descripcion;Categoria;Precio) que contenga el catálogo
completo con los precios ya ajustados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int codigo;
    char descripcion[51];
    int categoria;
    float precio;
}sPRODUCTOS;

int main()
{
    FILE  * archproductos, * csv;
    sPRODUCTOS productos;
    int categoria, cant_registros = 0, encategoria = 0;
    float porcentaje;

    archproductos = fopen("Productos.dat", "r+b");
    csv = fopen("productos_actualizados.csv", "w");

    if (archproductos == NULL || csv == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO!");
        getch();
        exit(1);
    }

    printf("Ingrese el numero de categoria del producto a incrementar: \n");
    scanf("%d", &categoria);
    
    printf("Ingrese el porcentaje a incrementar: \n");
    scanf("%f", &porcentaje);

    fread(&productos, sizeof(sPRODUCTOS), 1, archproductos);

    fprintf(csv, "Codigo;Descripcion;Categoria;Precio\n");

    while (!feof(archproductos))
    {
        cant_registros++;

        if (productos.categoria == categoria)
        {
            encategoria++;

            productos.precio = productos.precio * (1 + porcentaje / 100);

            fseek(archproductos, -(long)sizeof(sPRODUCTOS), 1);
            fwrite(&productos, sizeof(sPRODUCTOS), 1, archproductos);
            fflush(archproductos);
        }

        fprintf(csv, "%d;%s;%d;%.2f\n", productos.codigo, productos.descripcion, productos.categoria, productos.precio);

        fread(&productos, sizeof(sPRODUCTOS), 1, archproductos);
    }

    printf("Total de registros en el archivo: %d", cant_registros);
    printf("Productos de la categoria %d actualizados %d\n", categoria, encategoria);
    
    fclose(archproductos);
    fclose(csv);

    return 0;
}
