/*
Un su almacena su información de productos en un archivo binario.

Cada registro dek archivo tiene el siguiente formato:
-Codigo (int)
-Nombre (char[40])
-Stock (int)
-Precio (float)
-Rubro (char) 'A'= Alimentos, 'B'= Bebidas, 'L'= Limpieza

El archivo ya existe y contiene información cargada previamente. Se pide:
a) Nodificar el archivo en el mismo lugar, aplicando el siguiente aumento según el rubro:
    Rubro A -> aumento del 8%
    Rubro B -> sin aumento
    Rubro C -> aumento del 3%
b) Crear un nuevo archivo binario que contenga solo los productos cuyo stock sea menor o igual a 15 unidades. Este archivo debe contener el mismo tipo de registro.
c) Informar la cantidad total de registros del archivo original utilizando las funciones vistas en el curso. No se permite ir leyendo para contarlos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int codigo;
    char nombre[41];
    int stock;
    float precio;
    char rubro;
}sPRODUCTOS;

int main()
{
    FILE * archproduct, * archmenorstock;
    sPRODUCTOS productos;
    int cantidad_registros = 0;

    archproduct = fopen("productos.dat", "r+b");
    archmenorstock = fopen("menorStock.dat", "w+b");

    if (archproduct == NULL || archmenorstock == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO!");
        getch();
        exit(1);
    }
    
    fread(&productos, sizeof(sPRODUCTOS), 1, archproduct);

    while (!feof(archproduct))
    {
        if (productos.rubro == 'A')
        {
            productos.precio = productos.precio * 1.08;
        }
        else if (productos.rubro == 'L')
        {
            productos.precio = productos.precio * 1.03;
        }
        
        fseek(archproduct, -(long)sizeof(sPRODUCTOS), 1);
        fwrite(&productos, sizeof(sPRODUCTOS), 1, archproduct);
        fflush(archproduct);

        if (productos.stock <= 15)
        {
            fwrite(&productos, sizeof(sPRODUCTOS), 1, archmenorstock);
        }
        
        fread(&productos, sizeof(sPRODUCTOS), 1, archproduct);
    }
    
    fseek(archproduct, 0, 2);
    cantidad_registros = ftell(archproduct) / sizeof(sPRODUCTOS);
    
    printf("Cantidad de registros en 'productos.dat': %d", cantidad_registros);

    fclose(archproduct);
    fclose(archmenorstock);

    return 0;
}
