/*
Dado el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Realizar un programa que permita eliminar productos dado su código
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int codigo;
    float precio;
    char descripcion[51];
} sPRODUCTO;

int borrarProducto(char[], int);

int main()
{
    int codigo, eliminadoband;

    printf("Ingrese el registro a borrar: \n");
    scanf("%d", &codigo);

    eliminadoband = borrarProducto("productos.dat", codigo);

    if (eliminadoband == 1)
    {
        printf("Registro eliminado! \n");
    }
    else if (eliminadoband == 0)
    {
        printf("Producto no encontrado! \n");
    }

    return 0;
}

int borrarProducto(char nombrearch[], int codigo)
{
    FILE *fp, *aux;
    sPRODUCTO producto;
    int encontrado = 0;

    fp = fopen(nombrearch, "rb");

    if (fp == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO. fin del programa");
        getch();
        exit(1);
    }

    aux = fopen("aux.dat", "wb");

    if (aux == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO. fin del programa");
        getch();
        exit(1);
    }

    fread(&producto, sizeof(sPRODUCTO), 1, fp);

    while (!feof(fp))
    {
        if (producto.codigo == codigo)
        {
            encontrado = 1;
        }
        else
        {
            fwrite(&producto, sizeof(sPRODUCTO), 1, aux);
        }

        fread(&producto, sizeof(sPRODUCTO), 1, fp);
    }

    fclose(fp);
    fclose(aux);

    if (encontrado)
    {
        remove(nombrearch);
        rename("aux.dat", nombrearch);
    }
    else
    {
        remove("aux.dat");
    }

    return encontrado;
}
