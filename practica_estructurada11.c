/*
Ingresar una frase de hasta 500 caracteres y contar cuántas palabras contiene dicha frase.
a. Considerar que las palabras están separadas por un único espacio.
*/

#include <stdio.h>
#include <string.h>

int main()
{
    char frase[500];
    int i = 0, cant = 0;

    printf("Ingrese un texto. maximo 500 palabras: \n");
    fgets(frase, 500, stdin);

    while (i < strlen(frase))
    {
        while (frase[i] == ' ' && i <= strlen(frase))
        {
            i++;
        }

        if (i <= strlen(frase) && frase[i] != ' ' && frase[i] != '\n')
        {
            cant++;
        }

        while (frase[i] != ' ' && i < strlen(frase))
        {
            i++;
        }
    }

    printf("\nLa cantidad de palabras es de %d: ", cant);

    return 0;
}
