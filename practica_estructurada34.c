/*
La librería "Ateneo Universitario" almacena la lista de libros en el archivo binario Libros.dat utilizando la siguiente estructura:
codigo (entero)
titulo (hasta 50 caracteres)
precio (float)
Para incentivar las ventas o ajustar márgenes, la librería requiere un programa en C que realice lo siguiente:
Ajuste condicional de precios: Solicite un valor límite de precio y un porcentaje de ajuste. Si el libro tiene un precio inferior al limite
ingresado, se le aplicará un incremento. Si supera o iguala dicho valor, el precio no se modificará. La actualización debe realizarse sobre el archivo Libros.dat.
Informar la cantidad total de libros registrados utilizando cálculo directo sobre la longitud total del archivo binario con las funciones vistas en el curso
Exportación en formato CSV: Generar el archivo libros_actualizados.csv con los títulos de las columnas (Codigo,Titulo,Precio) separado por comas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int codigo;
    char titulo[51];
    float precio;
}sLIBROS;

int main()
{
    FILE * archlibros, * csv;
    sLIBROS libros;
    float limprecio, porcentaje;
    int cantidad_libros;

    archlibros = fopen("Libros.dat", "r+b");
    csv = fopen("Libros_actualizados.csv", "w");

    if (archlibros == NULL || csv == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO!");
        getch();
        exit(1);
    }

    printf("Ingrese un valor limite de precio para los ajustes: \n");
    scanf("%f", &limprecio);

    printf("Ingrese un porcentaje a modificar: \n");
    scanf("%f", &porcentaje);

    fread(&libros, sizeof(sLIBROS), 1, archlibros);

    fprintf(csv, "Codigo,Titulo,Precio\n");

    while (!feof(archlibros))
    {
        if (libros.precio < limprecio)
        {
            libros.precio = libros.precio * (1 + porcentaje / 100);

            fseek(archlibros, -(long)sizeof(sLIBROS), 1);
            fwrite(&libros, sizeof(sLIBROS), 1, archlibros);
            fflush(archlibros);
        }
        
        fprintf(csv, "%d,%s,%.2f\n", libros.codigo, libros.titulo, libros.precio);
        
        fread(&libros, sizeof(sLIBROS), 1, archlibros);
    }

    fseek(archlibros, 0, SEEK_END);
    cantidad_libros = ftell(archlibros) / sizeof(sLIBROS);

    printf("Cantidad de libros en el archivo: %d\n", cantidad_libros);
    
    fclose(archlibros);
    fclose(csv);

    return 0;
}
