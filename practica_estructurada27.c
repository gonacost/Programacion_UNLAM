/*
Se dispone de un archivo que contiene información de los vuelos realizados por las distintas aerolíneas a
lo largo del mes. El archivo se denomina Vuelos.dat y guarda los registros con la siguiente estructura:
• Código Aerolínea (alfanumérico de 10 caracteres máximo)
• Día (entero)
• Número de Vuelo (entero)
• Costo del pasaje (real) 
• Pasajeros (inicialmente en el archivo viene en 0) 
Luego se dispone de un segundo archivo llamado Pasajeros.dat que incluye la información de los viajeros
del mes para la aerolínea con código “Aero1”, el archivo contiene los siguientes campos:
• DNI (entero)
• Número de Vuelo (entero)
Se desea realizar un programa que actualice la cantidad de pasajeros de la aerolínea con código “Aero1”
con la información de los pasajeros que realizaron los viajes. Tenga en cuenta que los números de vuelo se
repiten entre las distintas aerolíneas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct 
{
    char codigo[11];
    int dia;
    int numero_vuelo;
    float costo_pasaje;
    int pasajeros;
}sVUELOS;

typedef struct 
{
    int dni;
    int numero_vuelo;
}sPASAJERO;

int main()
{
    FILE * fp, * pasaj;
    sVUELOS vuelos;
    sPASAJERO pasajero;
    int encontrado = 0;

    fp = fopen("Vuelos.dat", "r+b");

    if (fp == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO");
        getch();
        exit(1);
    }
    
    pasaj = fopen("Pasajeros.dat", "rb");

    if (pasaj == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO");
        getch();
        exit(1);
    }

    fread(&pasajero, sizeof(sPASAJERO), 1, pasaj);

    while (!feof(pasaj))
    {
        rewind(fp);

        encontrado = 0;

        fread(&vuelos, sizeof(sVUELOS), 1, fp);

        while (!feof(fp) && !encontrado)
        {
            if ((strcmp(vuelos.codigo, "Aero1")==0) && vuelos.numero_vuelo == pasajero.numero_vuelo)
            {
                encontrado = 1;

                vuelos.pasajeros += 1;

                fseek(fp, -(long)sizeof(sVUELOS), 1);
                fwrite(&vuelos, sizeof(sVUELOS), 1, fp);
            }
            else
            {
                fread(&vuelos, sizeof(sVUELOS), 1, fp);
            }
        }

        fread(&pasajero, sizeof(sPASAJERO), 1, pasaj);
    }

    fclose(fp);
    fclose(pasaj);
    return 0;
}



