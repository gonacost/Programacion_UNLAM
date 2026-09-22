/*
Se sabe que como máximo en una comisión de Elementos de Programación hay 80 alumnos. De cada alumno
se conoce:
• Número de DNI (entero).
• Apellido y Nombre (80 caracteres).
• Nota1, Nota2 (entero).
• Nota Promedio (real, calculado según Nota1 y Nota2).
Se solicita:
a. Declarar un tipo de dato que contenga la información del alumno.
b. Declarar un vector de estructuras del tipo de dato creado en el punto a.
c. Cargar en un vector de estructuras, los datos referentes a los alumnos de la comisión, esta
información termina con DNI igual al 0. Función INGRESO.
d. Indicar cuántos alumnos aprobaron (ambos parciales con nota >= 4 y cuántos reprobaron la materia.
Función RESULTADO.
e. Informar los datos de los alumnos de (DNI – Apellido y Nombre – Nota Promedio) de los alumnos.
PROMOCIONADOS (ambas notas >= 7). Función INFORME_PROMO.
*/

#include <stdio.h>
#include <string.h>

typedef struct
{
    int numero_dni;
    char apellido_nombre[81];
    int nota[2];
    float promedio;
} sALUMNO;

int INGRESO(sALUMNO[], int);
void RESULTADO(sALUMNO[], int, int *, int *);
void INFORME_PROMO(sALUMNO[], int);
void quitar_salto(char[]);

int main()
{
    int aprobados = 0, desaprobados = 0, cantidad_de_alumnos;
    sALUMNO alumnos[80];

    cantidad_de_alumnos = INGRESO(alumnos, 80);

    RESULTADO(alumnos, cantidad_de_alumnos, &aprobados, &desaprobados);

    printf("Cantidad de alumnos aprobados: %d -------- Cantidad de alunos desaprobados: %d", aprobados, desaprobados);

    INFORME_PROMO(alumnos, cantidad_de_alumnos);

    return 0;
}

void quitar_salto(char mensaje[])
{
    int i = 0, len;

    len = strlen(mensaje);

    for (i = 0; i < len; i++)
    {
        if (mensaje[i] == '\n')
        {
            mensaje[i] = '\0';
        }
    }
}

int INGRESO(sALUMNO alumnos[], int ce)
{
    int i = 0, dni;

    printf("Ingrese el DNI del alumno %d. (0 para fin): \n", i + 1);
    scanf("%d", &dni);

    while (getchar() != '\n')
        ;

    while (dni != 0 && i < ce)
    {
        alumnos[i].numero_dni = dni;

        printf("Ingrese el nombre y apellido del alumno: \n");
        fgets(alumnos[i].apellido_nombre, 81, stdin);

        quitar_salto(alumnos[i].apellido_nombre);

        for (int j = 0; j < 2; j++)
        {
            printf("Ingrese la nota %d: ", j + 1);
            scanf("%d", &alumnos[i].nota[j]);
        }

        alumnos[i].promedio = (alumnos[i].nota[0] + alumnos[i].nota[1]) / 2.0;

        i++;

        printf("Ingrese el DNI del alumno %d. (0 para fin): \n", i + 1);
        scanf("%d", &dni);

        while (getchar() != '\n')
            ;
    }

    return i;
}

void RESULTADO(sALUMNO alumnos[], int ce, int *aprobado, int *desaprobado)
{
    for (int i = 0; i < ce; i++)
    {
        if (alumnos[i].nota[0] >= 4 && alumnos[i].nota[1] >= 4)
        {
            (*aprobado)++;
        }
        else
        {
            (*desaprobado)++;
        }
    }
}

void INFORME_PROMO(sALUMNO alumnos[], int ce)
{
    printf("\n--------ALUMNOS PROMOCIONADOS--------\n");

    for (int i = 0; i < ce; i++)
    {
        if (alumnos[i].nota[0] >= 7 && alumnos[i].nota[1] >= 7)
        {
            printf("Nombre y apellido: %s\n", alumnos[i].apellido_nombre);
            printf("DNI: %d\n", alumnos[i].numero_dni);
            printf("Nota promedio: %.2f\n", alumnos[i].promedio);
            printf("\n");
        }
    }
}