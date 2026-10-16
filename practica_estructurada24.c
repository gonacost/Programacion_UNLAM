/*
Se desea realizar un programa que permita actualizar la lista de precios de una empresa en forma
individual a cada uno de sus productos.
Los productos que están guardados en el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Para modificar un precio se ingresa por teclado el código del producto y el nuevo precio. La modificación
de precios finaliza con un código de producto igual a 0. 
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct 
{
    int codigo;
    float precio;
    char descripcion[51];
}sPRODUCTO;

int main()
{
    FILE * fp;
    sPRODUCTO producto;
    int codigo, encontrado;
    float precio;

    fp = fopen("PRODUCTOS.DAT", "r+b");

    if (fp == NULL)
    {
        printf("ERROR AL ABRIR ARCHIVO");
        getch();
        exit(1);
    }
    
    printf("Ingrese el CODIGO del producto a modificar. (0 para fin): \n");
    scanf("%d", &codigo);

    while (codigo != 0)
    {
        printf("Ingrese el nuevo PRECIO: \n");
        scanf("%f", &precio);

        rewind(fp);
        encontrado = 0;

        fread(&producto, sizeof(sPRODUCTO), 1, fp);

        while (!encontrado && !feof(fp))
        {
            if (producto.codigo == codigo)
            {
                encontrado = 1;
            }
            else
            {
                fread(&producto, sizeof(sPRODUCTO), 1, fp);
            }
        }

        if (encontrado)
        {
            producto.precio = precio;

            fseek(fp, -(long)sizeof(sPRODUCTO), 1);
            fwrite(&producto, sizeof(sPRODUCTO), 1, fp);
            fflush(fp);

            printf("PRECIO ACTUALIZADO CON EXITO!\n");
        }
        else
        {
            printf("NO EXISTE EL CODIGO\n");
        }

        printf("\nIngrese el codigo del producto (0 para terminar): ");
        scanf("%d", &codigo);
    }
    
    fclose(fp);
    return 0;
}
