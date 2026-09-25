/*
El codigo postal argentino se compone de 8 caracteres donde el primero alfabetico indica provincia
los cuatro siguientes son el numero clasico y los tres restantes son alfabeticos que indican
zona y posicion de la manzana. Ejemplo: B1754JEC (UINLAM)
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validar_cp(char[]);

int main()
{
    char cp[9];
    int esValido, len;

    printf("Ingrese su codigo postal. (formato: X1111XXX): \n");
    fgets(cp, 9, stdin);

    len = strlen(cp);

    if (len > 0 && cp[len - 1] == '\n')
    {
        cp[len - 1] = '\0';
        len -= 1;
    }

    while (len != 8)
    {
        printf("ERROR. tiene que tener 8 caracteres, reingrese: \n");
        fgets(cp, 9, stdin);

        len = strlen(cp);

        if (len > 0 && cp[len - 1] == '\n')
        {
            cp[len - 1] = '\0';
            len -= 1;
        }
    }

    esValido = validar_cp(cp);

    if (esValido != 1)
    {
        printf("Formato de codigo postal invalido. \n");
    }
    else
    {
        printf("CODIGO POSTAL CORRECTO --> %s", cp);
    }
    
    return 0;
}

int validar_cp(char cp[])
{
    char *p;
    int valido = 1;

    p = cp;

    for (p = cp; p < cp + 8; p++)
    {
        if ((p - cp) == 0 && !isalpha(*p))
        {
            valido = 0;
        }
        else if(((p - cp) >= 1 && (p - cp) <= 4) && !isdigit(*p))
        {
            valido = 0;
        }
        else if(((p - cp) >= 5 && (p - cp) <= 7) && !isalpha(*p))
        {
            valido = 0;
        }
    }
    
    return valido;
}