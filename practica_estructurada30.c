/*
Se dispone de un archivo llamado Rating.dat que guarda la información de los puntos obtenidos de rating
en los distintos programas de canales de cable a lo largo del día. Cada registro contiene: 
• Número de canal (entero)
• Programa (texto de 35 caracteres máximo)
• Rating (float)
El archivo se encuentra ordenado por canal.
Se solicita informar:
a. Aquellos canales que obtengan menos de 15 puntos en total.
b. El canal más visto.
c. Generar un archivo con el promedio de rating de cada canal que incluya dos campos:
• Número de canal.
• Promedio. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int numero_canal;
    char programa[36];
    float rating;
}sRATING;

typedef struct 
{
    int numero_canal;
    float promedio;
}sPROMEDIO;

int main()
{
    FILE * frating, * fpromedio;
    sRATING rating;
    sPROMEDIO promedio;
    int canal_actual, cant, masvisto = 0;
    float total, maxtotal = -1;

    frating = fopen("Rating.dat", "rb");

    if (frating == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO");
        getch();
        exit(1);
    }

    fpromedio = fopen("Promedio.dat", "wb");

    if (fpromedio == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO");
        getch();
        exit(1);
    }
    
    fread(&rating, sizeof(sRATING), 1, frating);

    while (!feof(frating))
    {
        canal_actual = rating.numero_canal;
        total = 0;
        cant = 0;

        while (!feof(frating) && rating.numero_canal == canal_actual)
        {
            total += rating.rating;
            cant++;

            fread(&rating, sizeof(sRATING), 1, frating);
        }
        
        if (total < 15)
        {
            printf("Canal actual: %d -- Rating: %.2f (Menor a 15) \n", canal_actual, total);
        }

        if (total > maxtotal)
        {
            maxtotal = total;
            masvisto = canal_actual;
        }

        promedio.numero_canal = canal_actual;
        promedio.promedio = total / cant;
        
        fwrite(&promedio, sizeof(sPROMEDIO), 1, fpromedio);
    }
    
    if (masvisto != 0)
    {
        printf("Canal mas visto: %d -- Rating: %.2f \n", masvisto, maxtotal);
    }
    
    fclose(frating);
    fclose(fpromedio);

    return 0;
}

