/*
De una persona se conoce los siguientes datos:
• Número de Legajo (int, entre 1 y 10.000)
• Apellido (string, 15 caracteres)
• Nombre (string, 15 caracteres)
• Altura (float, mayor de 0)
• Sexo (char, F o M)
• Día de Nacimiento (int, entre 1 y 31
• Mes de Nacimiento (int, ente 1 y 12)
• Año de Nacimiento (int, ente 1950 y 2019)

Se solicita realizar los siguientes procesos:
a. Con datos ingresados por teclado: Crear una Estructura de Datos con los datos enunciados
anteriormente y llamarla PERSONA.
b. Mostrar los datos de la Estructura de Datos del punto a.
c. Con datos ingresados por teclado: Modificar la Estructura de Datos del punto a., crear una Estructura
de Datos que contenga Nombre y Apellido y otra Estructura de Datos que contenga Día/Mes/Año
utilizarla en una nueva Estructura de Datos llamada PERSONA2.
d. Mostrar los datos de la Estructura de Datos del punto c.
e. Crear una FUNCION que cargue los datos de la Estructura de Datos del punto c y que retorne los datos
al programa principal (main).
f. Con datos ingresados por teclado: Modificar la Estructura de Datos llamada PERSONA2 del punto c.
y agregarle un campo/miembro que contenga los códigos de las Materias Aprobadas (pueden llegar a
ser hasta 36 materias) y llamarla PERSONA3.
g. Crear una FUNCION que realice el punto f.
h. Mostrar los datos de la Lista creada en el punto f.
i. Crear una FUNCION que realice el punto h.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int numero_legajo;
    char apellido[16];
    char nombre[16];
    float altura;
    char sexo;
    int dia_nacimiento;
    int mes_nacimiento;
    int anio_nacimiento;
}sPERSONA;

typedef struct 
{
    char nombre[16];
    char apellido [16];
}sNOMBRE;

typedef struct 
{
    int dia;
    int mes;
    int anio;
}sFECHA;

typedef struct 
{
    int legajo;
    sNOMBRE nombreCompleto;
    float altura;
    char sexo;
    sFECHA nacimiento;
}sPERSONA2;




int ingrIntEntre(char[], int, int);
void ingrString(char[], char[], int);
char ingrCharValido(char, char);
float ingrFloatValido(float);

int main()
{
    sPERSONA persona;
    sPERSONA2 persona2;
    char nombre_completo[40], nombre_completo2[40];

    //PUNTO A
    persona.numero_legajo = ingrIntEntre("Ingrese el LEGAJO", 1, 10000);

    ingrString("Ingrese el APELLIDO", persona.apellido, 16);
    ingrString("Ingrese el NOMBRE", persona.nombre, 16);

    persona.altura = ingrFloatValido(0);

    persona.sexo = ingrCharValido('F', 'M');

    persona.dia_nacimiento = ingrIntEntre("Ingrese el DIA de nacimiento", 1, 31);
    persona.mes_nacimiento = ingrIntEntre("Ingrese el MES de nacimiento", 1, 12);
    persona.anio_nacimiento = ingrIntEntre("Ingrese el ANIO de nacimiento", 1950, 2019);

    //PUNTO B
    printf("\n-------INFORMACION DE LA PERSONA-------\n");
   
    strcpy(nombre_completo, persona.apellido);
    strcat(nombre_completo, ", ");
    strcat(nombre_completo, persona.nombre);

    printf("Legajo: %d\n", persona.numero_legajo);
    printf("Nombre completo: %s\n", nombre_completo);
    printf("Altura: %.2f\n", persona.altura);
    printf("Sexo: %c\n", persona.sexo);
    printf("Fecha de nacimiento: %d/%d/%d\n", persona.dia_nacimiento, persona.mes_nacimiento, persona.anio_nacimiento);

    //PUNTO C
    persona2.legajo = ingrIntEntre("Ingrese el LEGAJO", 1, 10000);

    ingrString("Ingrese el NOMBRE", persona2.nombreCompleto.nombre, 16);
    ingrString("Ingrese el APELLIDO", persona2.nombreCompleto.apellido, 16);

    persona2.altura = ingrFloatValido(0);

    persona2.sexo = ingrCharValido('F', 'M');

    persona2.nacimiento.dia = ingrIntEntre("Ingrese el DIA de nacimiento", 1, 31);
    persona2.nacimiento.mes = ingrIntEntre("Ingrese el MES de nacimiento", 1, 12);
    persona2.nacimiento.anio = ingrIntEntre("Ingrese el ANIO de nacimiento", 1950, 2019);

    //PUNTO D
    printf("\n-------INFORMACION DE LA PERSONA 2-------\n");

    strcpy(nombre_completo2, persona2.nombreCompleto.apellido);
    strcat(nombre_completo2, ", ");
    strcat(nombre_completo2, persona2.nombreCompleto.nombre);

    printf("Legajo: %d\n", persona2.legajo);
    printf("Nombre completo: %s\n", nombre_completo2);
    printf("Altura: %.2f\n", persona2.altura);
    printf("Sexo: %c\n", persona2.sexo);
    printf("Fecha de nacimiento: %d/%d/%d\n", persona2.nacimiento.dia, persona2.nacimiento.mes, persona2.nacimiento.anio);

    return 0;
}

int ingrIntEntre(char mensaje[], int linf, int lsup)
{
    int dato;

    printf("%s (entre %d y %d): \n", mensaje, linf, lsup);
    scanf("%d", &dato);

    while (dato < linf || dato > lsup)
    {
        printf("Error. Reingrese (%d - %d): \n", linf, lsup);
        scanf("%d", &dato);
    }

    while (getchar() != '\n')
        ;

    return dato;
}

void ingrString(char mensaje[], char destino[], int ce)
{
    printf("%s: \n", mensaje);
    fgets(destino, ce, stdin);

    for (int i = 0; destino[i] != '\0'; i++)
    {
        if (destino[i] == '\n')
        {
            destino[i] = '\0';
        }
    }
}

float ingrFloatValido(float lim)
{
    float dato;

    printf("Ingrese la ALTURA: \n");
    scanf("%f", &dato);

    while (dato <= lim)
    {
        printf("ERROR. reingrese: \n");
        scanf("%f", &dato);
    }
    
    while (getchar() !='\n');
    
    return dato;
}

char ingrCharValido(char op1, char op2)
{
    char dato;

    printf("Ingrese el SEXO (%c - %c): \n", op1, op2);
    scanf(" %c", &dato);

    dato = toupper(dato);

    while (dato != op1 && dato != op2)
    {
        printf("ERRO. Ingrese el SEXO (%c - %c): \n", op1, op2);
        scanf(" %c", &dato);

        dato = toupper(dato);
    }

    while (getchar() != '\n');
    
    return dato;
}