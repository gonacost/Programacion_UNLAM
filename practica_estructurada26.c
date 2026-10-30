/*
Se dispone de un archivo llamado Stock.dat que contiene la información de los productos que vende una
fábrica. En el archivo se guarda:
• Código de artículo (entero)
• Descripción (50 caracteres máximo)
• Stock (entero)
Luego se ingresan por teclado las ventas a realizar indicando:
• Código de artículo
• Cantidad
 La carga por teclado de las ventas finaliza con un código de artículo igual a 0.
Por cada venta se debe controlar si hay stock suficiente y si lo hay, restar el stock de dicho producto, sino
hay stock se debe vender lo que quede disponible y grabar un registro en un archivo Faltantes.dat con la
cantidad que no pudo venderse, dicho registro debe contener:
• Código de artículo
• Cantidad faltante
Si ya hay un registro previo en dicho archivo de faltantes con el mismo producto debe incrementarse la
cantidad. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int codigo;
    char descripcion[51];
    int stock;
}sSTOCK;

typedef struct
{
    int codigo;
    int cant_falt;
}sFALTANTE;

sSTOCK busqueda(int, FILE *);
sFALTANTE busquedafalt(int, FILE *);

int main()
{
    FILE * fp, * falt;
    sSTOCK stock;
    sFALTANTE faltante;
    int codigo;
    int cantidad, cantFalt;

    fp = fopen("Stock.dat", "r+b");

    if (fp == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO");
        getch();
        exit(1);
    }

    falt = fopen("Faltantes.dat", "r+b");

    if (falt == NULL)
    {
        falt = fopen("Faltantes.dat", "w+b");

        if (falt == NULL)
        {
            printf("ERROR AL ABRIR EL ARCHIVO.");
            getch();
            exit(1);
        }
    }

    printf("Ingrese el codigo del producto a vender. (0 para fin): \n");
    scanf("%d", &codigo);

    while (codigo != 0)
    {
        stock = busqueda(codigo, fp);

        if (stock.codigo != -1)
        {
            printf("Ingrese la cantidad a vender: \n");
            scanf("%d", &cantidad);

            if (stock.stock >= cantidad)
            {
                stock.stock -= cantidad;
            }
            else
            {
                cantFalt = cantidad - stock.stock;
                stock.stock = 0;

                faltante = busquedafalt(codigo, falt);
                
                if (faltante.codigo != -1)
                {
                    faltante.cant_falt += cantFalt;
                    fseek(falt, -(long)sizeof(sFALTANTE), 1);
                }
                else
                {
                    faltante.codigo = codigo;
                    faltante.cant_falt = cantFalt;
                    fseek(falt, 0, 2);
                }

                fwrite(&faltante, sizeof(sFALTANTE), 1, falt);
            }
            
            fseek(fp, -(long)sizeof(sSTOCK), 1);
            fwrite(&stock, sizeof(sSTOCK), 1, fp);
        }
        else
        {
            printf("Producto no encontrado! \n");
        }
        
        printf("Ingrese el codigo del producto a vender. (0 para fin): \n");
        scanf("%d", &codigo);
    }

    fclose(fp);
    fclose(falt);
    
    return 0;
}

sSTOCK busqueda(int abuscar, FILE * fp)
{
    sSTOCK prod;
    int encontrado = 0;

    rewind(fp);

    fread(&prod, sizeof(sSTOCK), 1, fp);

    while (!feof(fp) && !encontrado)
    {
        if (prod.codigo == abuscar)
        {
            encontrado = 1;
        }
        else
        {
            fread(&prod, sizeof(sSTOCK), 1, fp);
        }
    }

    if (!encontrado)
    {
        prod.codigo = -1;
    }
    
    return prod;
}

sFALTANTE busquedafalt(int abuscar, FILE * fp)
{
    sFALTANTE prod;
    int encontrado = 0;

    rewind(fp);

    fread(&prod, sizeof(sFALTANTE), 1, fp);

    while (!feof(fp) && !encontrado)
    {
        if (prod.codigo == abuscar)
        {
            encontrado = 1;
        }
        else
        {
            fread(&prod, sizeof(sFALTANTE), 1, fp);
        }
    }

    if (!encontrado)
    {
        prod.codigo = -1;
    }
    
    return prod;
}