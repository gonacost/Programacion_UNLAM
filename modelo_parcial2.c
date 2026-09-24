/*
Ej 2:  Un centro odontológico administra una agenda de 40 turnos para un día determinado. Cada turno se representa mediante una estructura con los siguientes datos:

 DNI del Paciente (entero).

Nombre del Paciente (cadena de hasta 50 caracteres).

Estado del Turno (entero: 1 “Pendiente", 2  "Atendido", 3  "Cancelado").

Se deben ingresar los datos de los 40 turnos , Al ingresar el DNI, se debe validar que el paciente no tenga ya un turno asignado en el vector.

Finalizada la carga, se ingresará una secuencia de DNI de pacientes que van llegando a la recepción, terminando con DNI = 0.

Si el DNI existe, se debe cambiar el estado del turno a 2: "Atendido”.

Si el DNI no existe, se lo contabilizara como “Paciente No Registrados".

Informar:

a) La cantidad total de pacientes que asistieron, pero no tenían turno.
b) El listado completo de la agenda ordenado de forma ascendente por DNI, mostrando DNI, Nombre y el estado.
Implementar al menos tres funciones: Una para la carga, otra para el ordenamiento y otra para la  búsqueda del código en el vector de estructuras,
*/

#include <stdio.h>
#include <string.h>

typedef struct
{
    int dni;
    char nombre[51];
    int estado;
} sPACIENTES;

int busqueda(sPACIENTES[], int, int);
void carga(sPACIENTES[]);
void ordenamiento(sPACIENTES[], int);
int validarint(int);
int validarRango(int, int);

int main()
{
    int no_cargados = 0;
    int dni, pos;
    sPACIENTES paciente[40];

    carga(paciente);

    printf("\n------------TURNOS DE PACIENTES------------\n");

    printf("Ingrese el DNI del paciente que llega. (0 para fin): \n");
    dni = validarint(-1);

    while(getchar() != '\n');

    while (dni != 0)
    {
        pos = busqueda(paciente, dni, 40);

        if (pos != -1)
        {
            paciente[pos].estado = 2;
        }
        else
        {
            no_cargados++;
        }

        printf("Ingrese el DNI del paciente que llega. (0 para fin): \n");
        dni = validarint(-1);

        while(getchar() != '\n');
    }

    printf("CANTIDAD DE PACIENTES QUE NO TENIAN TURNO: %d\n", no_cargados);

    ordenamiento(paciente, 40);

    printf("\n----------LISTA DE AGENDA----------\n");

    for (int i = 0; i < 40; i++)
    {
        printf("DNI: %d -- NOMBRE: %s -- ESTADO: %d\n", paciente[i].dni, paciente[i].nombre, paciente[i].estado);
    }

    return 0;
}

int busqueda(sPACIENTES paciente[], int x, int ce)
{
    int pos = -1, i = 0;

    while (pos == -1 && i < ce)
    {
        if (paciente[i].dni == x)
        {
            pos = i;
        }
        else
        {
            i++;
        }
    }

    return pos;
}

void carga(sPACIENTES paciente[])
{
    int pos, dni, estado, len;

    for (int i = 0; i < 40; i++)
    {
        printf("Ingrese el DNI del paciente %d: \n", i + 1);
        dni = validarint(0);

        while (getchar() != '\n');

        pos = busqueda(paciente, dni, i);

        while (pos != -1)
        {
            printf("DNI ya cargado. Reingrese: \n");
            dni = validarint(0);

            while(getchar() != '\n');

            pos = busqueda(paciente, dni, i);
        }

        paciente[i].dni = dni;

        printf("Ingrese el NOMBRE del paciente: \n");
        fgets(paciente[i].nombre, 51, stdin);

        len = strlen(paciente[i].nombre);

        if (paciente[i].nombre[len - 1] == '\n')
        {
            paciente[i].nombre[len - 1] = '\0';
        }

        printf("Ingrese el ESTADO del paciente (1-'pendiente', 2-'atendido', 3-'cancelado'): ");
        estado = validarRango(1, 3);

        paciente[i].estado = estado;

        while (getchar() != '\n');
    }
}

int validarint(int lim)
{
    int dato;

    scanf("%d", &dato);

    while (dato <= lim)
    {
        printf("ERROR. reingrese: \n");
        scanf("%d", &dato);
    }

    return dato;
}

int validarRango(int linf, int lsup)
{
    int dato;

    scanf("%d", &dato);

    while (dato < linf || dato > lsup)
    {
        printf("ERROR. tiene que estar entre %d y %d. reingrese: \n", linf, lsup);
        scanf("%d", &dato);
    }

    return dato;
}

void ordenamiento(sPACIENTES paciente[], int ce)
{
    int i, j, cota = ce - 1;
    sPACIENTES aux;

    for (i = 0; i < cota; i++)
    {
        for (j = 0; j < cota; j++)
        {
            if (paciente[j].dni > paciente[j + 1].dni)
            {
                aux = paciente[j];
                paciente[j] = paciente[j + 1];
                paciente[j + 1] = aux;
            }
        }
    }
}
