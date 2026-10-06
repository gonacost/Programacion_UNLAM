/*
1. Los datos de los alumnos de una comisión de Computación Transversal son:
• Número de DNI (entero)
• Nombre y Apellido (80 caracteres)
• Nota1, Nota2 (entero)
• Nota Promedio (real, calculado según Nota1 y Nota2)
a. Declarar un tipo de dato que contenga la información del alumno.
b. Con la información indicada para los alumnos. Grabar los datos en el archivo “ALUMNOS.dat”. Esta
información de grabación finaliza con DNI cero.
c. Leer los datos del archivo, mediante la Función LECTURA.
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef struct
{
    int dni;
    char nombre_apellido[81];
    int nota1;
    int nota2;
    float promedio;
} sALUMNOS;

void lectura(FILE *);
void limpieza(char[]);

int main()
{
    FILE *fp;
    sALUMNOS alumno;
    int i, dni, suma;
    float promedio;

    fp = fopen("ALUMNOS.dat", "wb");

    if (fp == NULL)
    {
        printf("Error al crear el archivo\n");
        getch();
        exit(1);
    }

    printf("Ingrese el DNI del alumno. (0 para fin): \n");
    scanf("%d", &dni);

    while (dni != 0)
    {
        alumno.dni = dni;

        printf("Ingrese el NOMBRE y APELLIDO del alumno: \n");
        fgets(alumno.nombre_apellido, 81, stdin);

        limpieza(alumno.nombre_apellido);

        printf("Ingrese la NOTA 1: \n");
        scanf("%d", &alumno.nota1);

        printf("Ingrese la NOTA 2: \n");
        scanf("%d", &alumno.nota2);

        suma = alumno.nota1 + alumno.nota2;

        promedio = (float)suma / 2;

        fwrite(&alumno, sizeof(sALUMNOS), 1, fp);

        printf("Ingrese el DNI del alumno. (0 para fin): \n");
        scanf("%d", &dni);
    }

    fclose(fp);

    fp = fopen("ALUMNOS.dat", "rb");

    if (fp == NULL)
    {
        printf("ERROR al abrir el archivo: \n");
    }

    lectura(fp);

    fclose(fp);

    return 0;
}

void limpieza(char mensaje[])
{
    int longitud;

    longitud = strlen(mensaje);

    for (int i = 0; i < longitud; i++)
    {
        if (mensaje[i] == '\n')
        {
            mensaje[i] = '\0';
        }
    }
}

void lectura(FILE *fp)
{
    sALUMNOS alumno;

    fread(&alumno, sizeof(sALUMNOS), 1, fp);

    while (!feof(fp))
    {
        printf("%d | %s | %d | %d | %.2f\n", alumno.dni, alumno.nombre_apellido, alumno.nota1, alumno.nota2, alumno.promedio);
        fread(&alumno, sizeof(sALUMNOS), 1, fp);
    }
}