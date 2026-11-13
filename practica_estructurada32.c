/*
Una empresa distribuidora de energia electrica posee un archivo binario llamado "consumo.dat". Cada registro almacena la lectura de un medidor con el siguiente formato:
-Zona Geografica (int)
-Numero de Cliente (int)
-Consumo en kWh (float)

El archivo está ordenado por el campo Zona Geografica. Se solicita diseñar unn programa en C que lea el archivo secuencialmente y aplique Corte de Control para informar:
1- El consumo promedio de kWh por cada Zona Geografica.
2- Cual fue la Zona Geografica que registro el mayor consumo total de energia.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int zona_geografica;
    int num_cliente;
    float consumo;
}sCONSUMO;

int main()
{
    FILE * archconsumo;
    int cant_zona = 0, zona_max = 0, zona_actual;
    float mayor_consumo = 0, promedio, consumo_total = 0;
    sCONSUMO consumos;

    archconsumo = fopen("consumo.dat", "rb");

    if (archconsumo == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO!\n");
        getch();
        exit(1);
    }
    
    fread(&consumos, sizeof(sCONSUMO), 1, archconsumo);

    while (!feof(archconsumo))
    {
        consumo_total = 0;
        zona_actual = consumos.zona_geografica;
        cant_zona = 0;

        while (!feof(archconsumo) && zona_actual == consumos.zona_geografica)
        {
            cant_zona++;
            consumo_total += consumos.consumo;

            fread(&consumos, sizeof(sCONSUMO), 1, archconsumo);
        }

        promedio = consumo_total / cant_zona;
        printf("Zona: %d -- Consumo promedio: %.2f kWh\n", zona_actual, promedio);

        if (consumo_total > mayor_consumo)
        {
            zona_max = zona_actual;
            mayor_consumo = consumo_total;
        }
    }

    printf("La zona con mayor consumo fue: %d con consumo de: %.2f\n", zona_max, mayor_consumo);
    
    fclose(archconsumo);

    return 0;
}
