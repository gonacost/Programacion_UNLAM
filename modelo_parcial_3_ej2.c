/*
Se dispone de un talonario de facturas con las ventas de los 15 productos que se comercializan
de cada una nos interesa registrar en un unico vector.
   nro de producto(int de 3 cifras, sin dup)
   descripcion de producto (70 char)
   importe de factura (float > 0)
   cantidad de facturas de cada producto(int)

la carga culmina con un numero de producto de 99, si al registrar la factura el producto existe,
se acumula el importe, y la descripcion se carga solo si cambio. de no existir, se agregara
o rechazara si no es posible agregarla

al finalizar, crear un vector con el tamaño justo para hacer una copia de solo datos de
todos los productos que cambiaron su descripcion alguna vez, y luego imprimir sus descripciones.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
   int numero_producto;
   char descripcion[71];
   float importe_factura;
   int cantidad_facturas;
   int cambio;
} sFACTURAS;

int validarRango(int, int, int);
int busqueda(sFACTURAS[], int, int);
float validarFloat(float);
int carga(sFACTURAS[], int);
void quitar_salto(char[]);

int main()
{
   int cantidad_facturas, cant_cambio = 0, j = 0;
   sFACTURAS facturas[15], *p;

   cantidad_facturas = carga(facturas, 15);

   for (int i = 0; i < cantidad_facturas; i++)
   {
      if (facturas[i].cambio == 1)
      {
         cant_cambio++;
      }
   }

   p = (sFACTURAS *)malloc(cant_cambio * sizeof(sFACTURAS));

   printf("\n-----------INFORME DE PRODUCTOS QUE CAMBIARON-----------\n");

   if (cant_cambio == 0)
   {
      printf("Ningun producto cmabio su DESCRIPCION. \n");
   }
   else
   {
      for (int i = 0; i < cantidad_facturas; i++)
      {
         if (facturas[i].cambio == 1)
         {
            p[j] = facturas[i];
            j++;
         }
      }

      for (int i = 0; i < cant_cambio; i++)
      {
         printf("PRODUCTO: %d - DESCRIPCION: %s\n", p[i].numero_producto, p[i].descripcion);
      }
   }

   free(p);
   return 0;
}

int carga(sFACTURAS factura[], int ce)
{
   int nro, i = 0, pos;
   float importe;
   char descr[71];

   printf("Ingrese el NUMERO del producto (3 cifras - 99 = fin): \n");
   nro = validarRango(100, 999, 99);

   while (nro != 99)
   {
      pos = busqueda(factura, nro, i);

      printf("Ingrese el IMPORTE del producto: \n");
      importe = validarFloat(0.0);

      printf("Ingrese la DESCRIPCION del producto: \n");
      fgets(descr, 71, stdin);

      quitar_salto(descr);

      if (pos != -1)
      {
         factura[pos].importe_factura += importe;

         if (strcmp(descr, factura[pos].descripcion) != 0)
         {
            strcpy(factura[pos].descripcion, descr);

            factura[pos].cambio = 1;
         }

         factura[pos].cantidad_facturas++;
      }
      else
      {
         if (i < ce)
         {
            factura[i].numero_producto = nro;

            strcpy(factura[i].descripcion, descr);

            factura[i].cantidad_facturas = 1;

            factura[i].importe_factura = importe;

            factura[i].cambio = 0;

            i++;
         }
         else
         {
            printf("Rechazado.\n");
         }
      }

      printf("Ingrese el NUMERO del producto (3 cifras - 99 = fin): \n");
      nro = validarRango(100, 999, 99);
   }

   return i;
}

int validarRango(int linf, int lsup, int otro)
{
   int dato;

   scanf("%d", &dato);

   while (getchar() != '\n')
      ;

   while ((dato < linf || dato > lsup) && dato != otro)
   {
      printf("ERROR. reingrese (%d-%d): \n", linf, lsup);
      scanf("%d", &dato);

      while (getchar() != '\n')
         ;
   }

   return dato;
}

int busqueda(sFACTURAS factura[], int x, int ce)
{
   int i = 0, pos = -1;

   while (pos == -1 && i < ce)
   {
      if (factura[i].numero_producto == x)
      {
         pos = i;
      }
      else
      {
         i++;
      }
   }

   return pos;
}

float validarFloat(float lim)
{
   float dato;

   scanf("%f", &dato);

   while (getchar() != '\n')
      ;

   while (dato <= lim)
   {
      printf("ERROR. reingrese: \n");
      scanf("%f", &dato);

      while (getchar() != '\n')
         ;
   }

   return dato;
}

void quitar_salto(char mensaje[])
{
   int len;

   len = strlen(mensaje);

   for (int i = 0; i < len; i++)
   {
      if (mensaje[i] == '\n')
      {
         mensaje[i] = '\0';
      }
   }
}