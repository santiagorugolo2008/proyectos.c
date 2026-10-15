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
    nuevo = (sensorF_t*)malloc((sizeof(sensorF_t)));
    if(nuevo == NULL)
    {
        printf("error al reservar memoria\n");
    }
    else
    {
        nuevo->ID = origen->ID;
        
    }



    return nuevo;
}



int main (int argc, char argv[])
{





    return 0;
}
