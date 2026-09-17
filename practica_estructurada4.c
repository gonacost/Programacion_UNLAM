#include <stdio.h>
#include <string.h>

int main()
{
    char correo[50];

    printf("Ingrese un correo:: ");
    fgets(correo, 50, stdin);

    if (strchr(correo, '@') != NULL)
    {
        printf("\nes correo");
    }
    else
    {
        printf("\n No es correo ");
    }
    
    return 0;
}