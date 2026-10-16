/*
Realizar un programa que permite actualizar una lista de precios en forma masiva, ingresando un
porcentaje de incremento. El archivo se llama precios.dat y fue generado utilizando la siguiente
estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct
{
    int codigo;
    float precio;
    char descripcion[51];
} sLista;

void mostrarArchivo(FILE *);

int main()
{
    FILE *fp;
    sLista lista;
    float porcentaje;

    fp = fopen("precios.dat", "r+b");

    if (fp == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO.");
        getch();
        exit(1);
    }

    mostrarArchivo(fp);

    printf("\n");

    printf("Ingrese el porcentaje a incrementar: \n");
    scanf("%f", &porcentaje);

    fread(&lista, sizeof(sLista), 1, fp);

    while (!feof(fp))
    {
        lista.precio = lista.precio * (1 + porcentaje / 100);

        fseek(fp, -(long)sizeof(sLista), 1);
        fwrite(&lista, sizeof(lista), 1, fp);

        fflush(fp);

        fread(&lista, sizeof(sLista), 1, fp);
    }

    fclose(fp);
    return 0;
}

void mostrarArchivo(FILE *fp)
{
    sLista lista;

    rewind(fp);

    fread(&lista, sizeof(sLista), 1, fp);

    while (!feof(fp))
    {
        printf("%d | %.2f | %s\n", lista.codigo, lista.precio, lista.descripcion);
        fread(&lista, sizeof(sLista), 1, fp);
    }
}
