#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sensor.h"


sensor_t * ajustar (sensorF_t *origen) // Reserva memoria necesaria para almacenar info y cargara en base a la estructura origen
{
    sensor_t* nuevo = NULL;
    nuevo = (sensor_t*)malloc(sizeof(sensor_t));
    if (nuevo == NULL)
    {
        printf("Error al pedir memoria\n");
    }
    else 
    {
        nuevo->ID = origen->ID;
        nuevo->Tipo = origen->Tipo;
        nuevo->accion = origen->accion;
        nuevo->umbralSup = origen->umbralSup;
        nuevo->umbralInf = origen->umbralInf;
            //copiar del origen al nuevo
        strcpy(nuevo->NombreExt, origen->Nombre);
        strcat(nuevo->NombreExt, " (");
        strcat(nuevo->NombreExt, origen->Ubicacion);
        strcat(nuevo->NombreExt, ")");
            //copiar marca - modelo
        strcpy(nuevo->MarMod, origen->Marca);
        strcat(nuevo->MarMod, " - ");
        strcat(nuevo->MarMod, origen->Modelo);
    }

    return nuevo;
}

sensorF_t *ajustarBack(sensor_t *origen)
{
    sensorF_t* nuevo = NULL;
    int i = 0, j=0;
    nuevo = (sensorF_t*)malloc((sizeof(sensorF_t)));
    if(nuevo != NULL)
    {
        nuevo->ID = origen->ID;
        nuevo->Tipo = origen->Tipo;
        nuevo->accion = origen->accion;
        nuevo->umbralSup = origen->umbralSup;
        nuevo->umbralInf = origen->umbralInf;

        while (origen->NombreExt[i] != ' ' && origen->NombreExt[i] != '\0')
        {
            nuevo->Nombre[i]=origen->NombreExt[i];
            i++;
        }
        nuevo->Nombre[i]='\0';
        i = i + 2; //empezando desde el espacio para iniciar el nuevo texto quedan 2 caracteres
        while ( origen->NombreExt[i] != ')' && origen->NombreExt[i] != '\0')
        {
            nuevo->Ubicacion[j] = origen->NombreExt[i];
            i++;
            j++;
        }
        nuevo->Ubicacion[j]='\0';

        i=0;
        j=0;
    
        while (origen->MarMod[i] != '\0' && origen->MarMod[i] != ' ')
        {
            nuevo->Marca[j] = origen->MarMod[i];
            i++;
            j++;
        }

        nuevo->Marca[j] = '\0';

        i=i + 3;
        j=0;
        while(origen->MarMod[i] != '\0')
        {
            nuevo->Modelo[j] = origen->MarMod[i];
            i++;
            j++;
        }
        nuevo->Modelo[j]='\0';

    }

    return nuevo;
}



int main (int argc, char* argv[])
{
    int cant=0;
    int op = 0;
    sensor_t **listado = NULL;
   
    if (argc != 2)
    {
        printf("Error de argumento uso: %s\n", argv[0]);
    }
    else
    {
        do
        {
            printf("1. Agregar un item\n 2. Eliminar un item\n 3. Generar un listado\n 4. Salir\n");
            scanf(" %d", &op);
            
            if (op==1)
            {
                //agregar
            }
            else if(op==2)
            {
                //quitar
            }
            else if(op==3)
            {
                //listar
            }
        } while (op != 4);
        
    }



    return 0;
}
