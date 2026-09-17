/*
Realizar el juego del ahorcado. Primero se debe ingresar la palabra a adivinar de hasta 10 caracteres. Luego
se muestra por cada letra un guion bajo para que el jugador sepa la cantidad de letras a adivinar. Se irá
ingresando una a una las letras y si estas se encuentran en la palabra las deberá ir mostrando en el lugar
correspondiente. Por cada letra que no se encuentre en la palabra perderá una vida. El jugador dispondrá de
5 vidas para intentar ganar el juego.
Complemento:
• Ir completando el dibujo del muñeco del ahorcado cada vez que se comete un error.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int carga_palabra(char[]);
void inicializar_array(char[], char[], int);
void mostrar_estado(char[], int, int);
int busqueda(char[], char[], char, int);
void dibujar_ahorcado(int);

int main()
{
    char palabra_secreta[11], palabra_guiones[11], letra;
    int vidas = 5, gano = 0, longitud, cantidad;
    int bandera;

    longitud = carga_palabra(palabra_secreta);

    system("cls");

    inicializar_array(palabra_secreta, palabra_guiones, longitud);

    while (vidas > 0 && !gano)
    {
        system("cls");
       
        mostrar_estado(palabra_guiones, vidas, longitud);

        printf("Ingrese la palabra a adivinar: \n");
        scanf(" %c", &letra);

        cantidad = busqueda(palabra_secreta, palabra_guiones, letra, longitud);

        if (cantidad != 0)
        {
            printf("\n---LETRA ENCONTRADA!!---\n");

            bandera = 1;

            for (int i = 0; i < longitud; i++)
            {
                if (palabra_guiones[i] == '_')
                {
                    bandera = 0;
                }
            }

            gano = bandera;
        }
        else
        {
            printf("\n---LETRA INCORRECTA!!---");

            vidas--;
        }

        dibujar_ahorcado(5 - vidas);
    }

    return 0;
}

int carga_palabra(char palabra[])
{
    int longitud;

    printf("Por favor ingrese la palabra oculta: \n");
    fgets(palabra, 11, stdin);

    palabra[strcspn(palabra, "\n")] = '\0';

    longitud = strlen(palabra);

    return longitud;
}

void inicializar_array(char palabra_oculta[], char palabra_guion[], int longitud)
{
    int i;

    for (i = 0; i < longitud; i++)
    {
        palabra_guion[i] = '_';
    }

    palabra_guion[longitud] = '\0';
}

void mostrar_estado(char palabra[], int vidas, int longitud)
{

    printf("\n---CANTIDAD DE VIDAS: %d---", vidas);

    for (int i = 0; i < longitud; i++)
    {
        printf(" %c \t", palabra[i]);
    }
}

int busqueda(char palabra[], char guiones[], char letra, int longitud)
{
    int i = 0, contador = 0;

    for (i = 0; i < longitud; i++)
    {
        if (palabra[i] == letra)
        {
            guiones[i] = letra;
            contador++;
        }
    }

    return contador;
}

void dibujar_ahorcado(int vidas)
{
    switch (vidas)
    {
        case 0:
            printf("  +---+\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;

        case 1:
            printf("  +---+\n");
            printf("  O   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;

        case 2:
            printf("  +---+\n");
            printf("  O   |\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("=========\n");
            break;

        case 3:
            printf("  +---+\n");
            printf("  O   |\n");
            printf(" /|   |\n");
            printf("      |\n");
            printf("=========\n");
            break;

        case 4:
            printf("  +---+\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf("      |\n");
            printf("=========\n");
            break;

        case 5:
            printf("  +---+\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" /    |\n");
            printf("=========\n");
            break;
    }
}