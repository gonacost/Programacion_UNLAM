/*
Se dispone de un archivo denominado INSCRIPTOS.dat que contiene la información de los inscriptos a un
curso de programación. El archivo aún no está completo ya que la inscripción se realiza por partes. Por
cada inscripto se tiene la siguiente información:
• DNI (entero)
• Apellido y Nombres (texto de 20 caracteres máximo)
• Pagado (campo entero donde 1 indica que pagó y 0 que aún adeuda la matrícula)

Se desea realizar un programa que cumpla con dos funciones:
a. Registrar los pagos de los alumnos ya inscriptos.
b. SI hay cupo, agregar nuevos inscriptos (el cupo máximo es de 60 alumno).

El programa solicitará el ingreso del DNI y lo buscará entre los inscriptos, en caso de que lo encuentre
dará la opción para registrar el pago (si es que no está pago ya). En caso de que no lo encuentre dará la
opción para inscribirlo al curso (el pago se realiza luego). En el momento que ya no quede cupo en el curso
si llega un nuevo inscripto se le preguntará si desea quedar registrado para un curso futuro, y en caso
afirmativo se le solicitará el teléfono y se guardará el nombre, DNI y teléfono en un archivo
Interesados.dat.

El ingreso de datos finaliza con un DNI negativo. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#define MAX 60

typedef struct 
{
    int dni;
    char nombre_completo[21];
    int pagado;
}sINSCRIPTO;

typedef struct 
{
    int numero_telefono;
    char nombre_completo[21];
    int dni;
}sINTERESADOS;


sINSCRIPTO busqueda(int, FILE*);

int main()
{
    FILE * fp, *interesado;
    sINSCRIPTO inscripto;
    sINTERESADOS interesados;
    int dni, numTelefono, pago, cantidad;
    char nombre_completo[21], opcion;

    fp = fopen("INSCRIPTOS.dat", "r+b");

    if (fp == NULL)
    {
        printf("ERROR. no se pudo abrir el archivo");
        getch();
        exit(1);
    }
    
    interesado = fopen("Interesados.dat", "rb");

    if (interesado == NULL)
    {
        interesado = fopen("Interesados.dat", "wb");

        if (interesado == NULL)
        {
            printf("ERROR AL ABRIR EL ARCHIVO");
            getch();
            exit(1);
        }
    }

    printf("Ingrese el DNI. (DNI negativo para fin): \n");
    scanf("%d", &dni);

    while (dni >= 0)
    {
        inscripto = busqueda(dni, fp);

        if (inscripto.dni != -1)
        {
            if (inscripto.pagado == 1)
            {
                printf("Alumno al dia! \n");
            }
            else
            {
                printf("Ingrese 1 para registrar el pago: \n");
                scanf("%d", &pago);

                if (pago == 1)
                {
                    inscripto.pagado = 1;

                    fseek(fp, -(long)sizeof(sINSCRIPTO), 1);
                    fwrite(&inscripto, sizeof(sINSCRIPTO), 1, fp);
                    fflush(fp);

                    printf("PAGO REGISTRADO CORRECTAMENTE! \n");
                }
                else
                {
                    printf("No se registro el pago! \n");
                }
            }
        }
        else
        {
            getchar();

            fseek(fp, 0, 2);
            cantidad = ftell(fp) / sizeof(sINSCRIPTO);

            if (cantidad < MAX)
            {
                printf("Ingrese el nombre para inscribirlo: \n");
                fgets(nombre_completo, 21, stdin);

                strcpy(inscripto.nombre_completo, nombre_completo);
                inscripto.dni = dni;

                inscripto.pagado = 0;

                fwrite(&inscripto, sizeof(sINSCRIPTO), 1, fp);
                fflush(fp);
                printf("INSCRIPTO CORRECTAMENTE! \n");
            }
            else
            {
                printf("SIN CUPOS!\n");
                printf("Desea registrar al alumno? (S/N): \n");
                scanf(" %c", &opcion);

                opcion = toupper(opcion);

                if (opcion == 'S')
                {
                    getchar();
                    printf("Ingrese el nombre completo: \n");
                    fgets(nombre_completo, 21, stdin);

                    printf("Ingrese el numero de telefono: \n");
                    scanf("%d", &numTelefono);

                    interesados.dni = dni;
                    strcpy(interesados.nombre_completo, nombre_completo);
                    interesados.numero_telefono = numTelefono;

                    fwrite(&interesados, sizeof(sINTERESADOS), 1, interesado);
                    fflush(interesado); 
                }
                
            }
        }

        printf("Ingrese el DNI (DNI negativo para fin): \n");
        scanf("%d", &dni);
    }

    fclose(fp);
    fclose(interesado);

    return 0;
}

sINSCRIPTO busqueda(int abuscar, FILE * fp)
{
    sINSCRIPTO alumno;
    int encontrado = 0;

    rewind(fp);

    fread(&alumno, sizeof(sINSCRIPTO), 1, fp);

    while (!feof(fp) && !encontrado)
    {
        if (alumno.dni == abuscar)
        {
            encontrado = 1;
        }
        else
        {
            fread(&alumno, sizeof(sINSCRIPTO), 1, fp);
        }
    }

    if (!encontrado)
    {
        alumno.dni = -1;
    }
    
    return alumno;
}





