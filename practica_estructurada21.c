/*
Tomando como base el archivo ALUMNOS.DAT creado en el ejercicio anterior se desea desarrollar un
programa que, basado en la información del archivo, genere 3 archivos:
• Uno con los alumnos PROMOCIONADOS (ambas notas mayores o igual a 7).
• Otro archivo con los alumnos en condición CURSADO (ambas notas mayores o igual a 4 pero no
promocionados).
• Y un tercer archivo con los REPROBADOS (al menos una nota, menor que 4).
Para comprobar los datos guardados realizar una función que reciba por parámetro el nombre del archivo
a mostrar, lo abre y muestre su contenido. Se debe invocar a la función 3 veces para mostrar todos los
archivos generados.
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct
{
    int dni;
    char nombre_apellido[81];
    int nota1;
    int nota2;
    float promedio;
} sALUMNOS;

void mostrarFile(char[]);
void generarFile(sALUMNOS);

int main()
{
    sALUMNOS alumnos;

    generarFile(alumnos);

    mostrarFile("PROMOCIONADOS.dat");
    mostrarFile("CURSADO.dat");
    mostrarFile("REPROBADOS.dat");

    return 0;
}

void generarFile(sALUMNOS alumno)
{
    FILE *fp, *fprom, *fcur, *frep;

    fp = fopen("ALUMNOS.DAT", "rb");
    if (fp == NULL)
    {
        printf("Error al abrir. ");
        getch();
        exit(1);
    }

    fprom = fopen("PROMOCIONADOS.dat", "wb");
    fcur = fopen("CURSADO.dat", "wb");
    frep = fopen("REPROBADOS.dat", "wb");

    if (fprom == NULL || fcur == NULL || frep == NULL)
    {
        printf("Error al abrir. ");
        getch();
        exit(1);
    }

    fread(&alumno, sizeof(sALUMNOS), 1, fp);

    while (!feof(fp))
    {
        if (alumno.nota1 >= 7 && alumno.nota2 >= 7)
        {
            fwrite(&alumno, sizeof(sALUMNOS), 1, fprom);
        }
        else if (alumno.nota1 >= 4 && alumno.nota2 >= 4)
        {
            fwrite(&alumno, sizeof(sALUMNOS), 1, fcur);
        }
        else
        {
            fwrite(&alumno, sizeof(sALUMNOS), 1, frep);
        }

        fread(&alumno, sizeof(sALUMNOS), 1, fp);
    }

    fclose(fp);
    fclose(fprom);
    fclose(fcur);
    fclose(frep);
}

void mostrarFile(char nombre[])
{
    FILE *fp;
    sALUMNOS alumno;

    fp = fopen(nombre, "rb");

    if (fp == NULL)
    {
        printf("ERROR al abrir el archivo.");
        getch();
        exit(1);
    }

    printf("\n------%s------\n", nombre);

    fread(&alumno, sizeof(sALUMNOS), 1, fp);

    while (!feof(fp))
    {
        printf("DNI - %d // NOMBRE - %s // NOTA 1 - %d // NOTA 2 - %d // PROMEDIO - %.2f\n", alumno.dni, alumno.nombre_apellido, alumno.nota1, alumno.nota2, alumno.promedio);

        fread(&alumno, sizeof(sALUMNOS), 1, fp);
    }

    fclose(fp);
}