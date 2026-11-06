/*
Dado el archivo pagos.dat con los pagos realizados por los alumnos a un curso, se desea registrar los
pagos de las cuotas. El archivo tiene el siguiente formato:
• DNI
• Fecha de último pago (3 enteros, día, mes y año)
Para registrar los pagos se ingresa el número de DNI (7 a 8 dígitos) y la fecha de pago. Se debe actualizar
el archivo de pagos, y si el DNI no se encuentra se pregunta al usuario si desea agregar un nuevo alumno.
En caso afirmativo se debe agregar un nuevo registro en dicho archivo con el nuevo pago y además
agregar el nuevo alumno al archivo alumnos.dat, dicho archivo contiene el DNI y nombre completo del
alumno (40 caracteres máximo).
Todos los datos de ingreso deben estar validados (para simplificar al validar la fecha considerar día de 1 a
31 para todos los meses).
Se procesan varios pagos hasta que se ingresa un DNI 0. Al finalizar mostrar un listado de los alumnos,
DNI y nombre de todos aquellos que adeudan la última cuota (del mes de febrero 2024)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

typedef struct
{
    int dni;
    int dia;
    int mes;
    int anio;
} sPAGOS;

typedef struct
{
    int dni;
    char nombreCompleto[41];
} sALUMNOS;

int validarRango(int, int);
int validarDni(int linf, int lsup);
sPAGOS busqueda(int, FILE *);
void limpieza(char[]);
void informeDeudores(void);

int main()
{
    FILE *fp, *aux;
    sALUMNOS alumnos;
    sPAGOS pagos;
    int dni, dia, mes, anio;
    char nombreCompleto[41], opcion;

    fp = fopen("pagos.dat", "r+b");

    if (fp == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO!");
        getch();
        exit(1);
    }

    aux = fopen("alumnos.dat", "r+b");

    if (aux == NULL)
    {
        aux = fopen("alumnos.dat", "a+b");

        if (aux == NULL)
        {
            printf("ERROR AL ABRIR EL ARCHIVO!");
            getch();
            exit(1);
        }
    }

    printf("Ingrese el DNI. (0 para fin): \n");
    dni = validarDni(1000000, 99999999);

    while (dni > 0)
    {
        printf("Ingrese el DIA: \n");
        dia = validarRango(1, 31);

        printf("Ingrese el MES: \n");
        mes = validarRango(1, 12);

        printf("Ingrese el ANIO: \n");
        anio = validarRango(2000, 2024);

        pagos = busqueda(dni, fp);

        if (pagos.dni != -1)
        {
            printf("PAGO REGISTRADO! \n");

            pagos.dia = dia;
            pagos.mes = mes;
            pagos.anio = anio;

            fseek(fp, -(long)sizeof(sPAGOS), SEEK_CUR);
            fwrite(&pagos, sizeof(sPAGOS), 1, fp);

            fflush(fp);
        }
        else
        {
            getchar();
            printf("DNI no encontrado. Desea agregar un nuevo alumno? (S/N): \n");
            scanf(" %c", &opcion);

            opcion = toupper(opcion);

            if (opcion == 'S')
            {
                getchar();
                printf("Ingrese el NOMBRE COMPLETO del nuevo alumno: \n");
                fgets(nombreCompleto, 41, stdin);

                limpieza(nombreCompleto);

                pagos.dni = dni;
                pagos.dia = dia;
                pagos.mes = mes;
                pagos.anio = anio;

                alumnos.dni = dni;
                strcpy(alumnos.nombreCompleto, nombreCompleto);

                fseek(fp, 0, SEEK_END);
                fwrite(&pagos, sizeof(sPAGOS), 1, fp);

                fflush(fp);

                fseek(aux, 0, SEEK_END);
                fwrite(&alumnos, sizeof(sALUMNOS), 1, aux);

                fflush(aux);
            }
        }

        printf("Ingrese el DNI. (0 para fin): \n");
        dni = validarDni(1000000, 99999999);
    }

    fclose(fp);
    fclose(aux);

    informeDeudores();

    return 0;
}

int validarRango(int linf, int lsup)
{
    int dato;

    scanf("%d", &dato);

    while (dato < linf || dato > lsup)
    {
        printf("Dato invalido. Reingrese: \n");
        scanf("%d", &dato);
    }

    return dato;
}

int validarDni(int linf, int lsup)
{
    int dato;

    scanf("%d", &dato);

    while (dato != 0 && (dato < linf || dato > lsup))
    {
        printf("Dato invalido. Reingrese: \n");
        scanf("%d", &dato);
    }

    return dato;
}

sPAGOS busqueda(int abuscar, FILE *fp)
{
    sPAGOS pagos;
    int encontrado = 0;

    rewind(fp);

    fread(&pagos, sizeof(sPAGOS), 1, fp);

    while (!feof(fp) && !encontrado)
    {
        if (pagos.dni == abuscar)
        {
            encontrado = 1;
        }
        else
        {
            fread(&pagos, sizeof(sPAGOS), 1, fp);
        }
    }

    if (!encontrado)
    {
        pagos.dni = -1;
    }

    return pagos;
}

void limpieza(char mensaje[])
{
    int tam;

    tam = strlen(mensaje);

    for (int i = 0; i < tam; i++)
    {
        if (mensaje[i] == '\n')
        {
            mensaje[i] = '\0';
        }
    }
}

void informeDeudores(void)
{
    FILE *fp, *fa;
    sPAGOS pagos;
    sALUMNOS alumnos;
    int encontrado;

    fp = fopen("pagos.dat", "rb");
    fa = fopen("alumnos.dat", "rb");

    if (fp == NULL || fa == NULL)
    {
        printf("ERROR AL ABRIR LOS ARCHIVOS PARA EL INFORME!\n");
        if (fp != NULL)
            fclose(fp);
        if (fa != NULL)
            fclose(fa);
        return;
    }

    printf("\nALUMNOS QUE ADEUDAN LA CUOTA DE FEBRERO 2024\n");
    printf("DNI        NOMBRE\n");

    fread(&pagos, sizeof(sPAGOS), 1, fp);

    while (!feof(fp))
    {
        if (pagos.anio * 100 + pagos.mes < 202402)
        {
            rewind(fa);
            encontrado = 0;

            fread(&alumnos, sizeof(sALUMNOS), 1, fa);

            while (!feof(fa) && !encontrado)
            {
                if (alumnos.dni == pagos.dni)
                {
                    encontrado = 1;
                }
                else
                {
                    fread(&alumnos, sizeof(sALUMNOS), 1, fa);
                }
            }

            if (encontrado)
            {
                printf("%-10d %s\n", pagos.dni, alumnos.nombreCompleto);
            }
        }

        fread(&pagos, sizeof(sPAGOS), 1, fp);
    }

    fclose(fp);
    fclose(fa);
}