/*
Un laboratorio dispone de una lista con sus 50 medicamentos. De cada uno conoce:
• Código del medicamento (entero, de 3 cifras).
• Precio (real).
• Stock (entero).
Se solicita:
a. Declarar un tipo de dato que contenga la información del medicamento.
b. Declarar un vector de estructura de tipo de datos creado en a.
c. Cargar en un sector de estructuras, los datos referentes a los medicamentos. Función INGRESO.
d. Consultar el precio según código del medicamento. Función BUSQUEDA_MEDI.
e. Informar los códigos de los medicamentos cuyo stock es inferior a 10 unidades. Función INFORME.
*/

#include <stdio.h>
#include <string.h>

typedef struct
{
    int codigo;
    float precio;
    int stock;
} sMEDICAMENTO;

void INGRESO(sMEDICAMENTO[], int);
void BUSQUEDA_MEDI(sMEDICAMENTO[], int);
void INFORME(sMEDICAMENTO[], int);
int ingrEnteroRango(char[], int, int);

int main()
{
    sMEDICAMENTO medicamentos[50];
    int cantidad_medicamentos;

    printf("Ingrese la cantidad de medicamentos a ingresar: \n");
    scanf("%d", &cantidad_medicamentos);

    INGRESO(medicamentos, cantidad_medicamentos);

    BUSQUEDA_MEDI(medicamentos, cantidad_medicamentos);

    INFORME(medicamentos, cantidad_medicamentos);

    return 0;
}

int ingrEnteroRango(char mensaje[], int linf, int lsup)
{
    int dato;

    printf("%s: \n", mensaje);
    scanf("%d", &dato);

    while (dato < linf || dato > lsup)
    {
        printf("ERROR. reingrese: ");
        scanf("%d", &dato);
    }

    return dato;
}

void INGRESO(sMEDICAMENTO medicamentos[], int ce)
{
    for (int i = 0; i < ce; i++)
    {
        medicamentos[i].codigo = ingrEnteroRango("Ingrese el codigo del producto. (3 cifras)", 100, 999);

        printf("Ingrese el precio del producto: \n");
        scanf("%f", &medicamentos[i].precio);

        printf("Ingrese el stock del producto: \n");
        scanf("%d", &medicamentos[i].stock);
    }
}

void BUSQUEDA_MEDI(sMEDICAMENTO medicamentos[], int ce)
{
    int i, codigo_buscado, encontrado = 0;

    printf("Ingrese el CODIGO del medicamento a buscar: \n");
    scanf("%d", &codigo_buscado);

    for (i = 0; i < ce; i++)
    {
        if (medicamentos[i].codigo == codigo_buscado)
        {
            printf("El precio del producto %d es: %.2f\n", medicamentos[i].codigo, medicamentos[i].precio);

            encontrado = 1;
        }
    }

    if (encontrado == 0)
    {
        printf("No se encontro el producto buscado. \n");
    }
}

void INFORME(sMEDICAMENTO medicamentos[], int ce)
{
    int i;

    printf("\n--------MEDICAMENTOS CON STOCK MENOR A 10--------\n");

    for (i = 0; i < ce; i++)
    {
        if (medicamentos[i].stock < 10)
        {
            printf("Codigo: %d - Stock: %d\n", medicamentos[i].codigo, medicamentos[i].stock);
        }
        
    }
    
}