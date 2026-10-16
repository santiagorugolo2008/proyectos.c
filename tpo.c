#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sensor.h"

sensor_t *ajustar(sensorF_t* origen)
{
    sensor_t* nuevo = NULL;
    nuevo = (sensor_t*)malloc(sizeof(sensor_t));
    if(nuevo != NULL)
    {
            //pasar los datos 
        nuevo->id = origen->id;
        nuevo->Tipo = origen->Tipo;
        nuevo->accion = origen->accion;
        nuevo->umbralSup = origen->umbralSup;
        nuevo->umbralInf = origen->umbralInf;
            //copiar nombre
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

sensorF_t * ajustarBack(sensor_t* origen)
{
    sensorF_t* nuevo = NULL;
    int i = 0, j = 0;
    nuevo = (sensorF_t*)malloc(sizeof(sensorF_t));
    if(nuevo != NULL)
    {
        nuevo->id = origen->id;
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

        i = 0;
        j = 0;

        while(origen->MarMod[i] != ' ' && origen->MarMod[j] != '\0')
        {
            nuevo->Marca[j]=origen->MarMod[i];
            i++;
            j++;
        }
        nuevo->Marca[i] = '\0';
        i = i + 3;
        j=0;
        while( origen->MarMod != '\0')
        {
            nuevo->Modelo[j] = origen->MarMod[i];
            i++;
            j++;
        }
        nuevo->Modelo[j] = '\0';
    }

    return nuevo;
}

int agregar (sensor_t** listado, int* pcant)
{
    int valR = ERROR;
    sensor_t* aux = NULL;

    if(*listado != NULL && pcant != NULL)
    {
        aux = realloc(*listado, sizeof(sensor_t) * (*pcant + 1));
        if (aux != NULL)
        {
            *listado = aux;
            printf("id:\n");
            if(scanf(" %d", &aux->id) == 1);
        
            printf("Ingrese el nombre\n");
            if(scanf(" %22s", &aux->NombreExt) == 1)
            {
                printf("ingresar marca y modelo\n ");
            
                if(scanf(" %22s", &aux->MarMod)==1);
                {
                    printf("ingrese el tipo de 0 a 255 \n");
                
                    if(scanf(" %c", aux->Tipo)==1 && aux->Tipo >=0 && aux->Tipo <= 255);
                    {
                        printf("ingresar accion\n");
                        if(scanf(" %d", aux->accion) == 1);
                        {
                            printf("ingresar umbral superior primero magnitud y luego su unidad\n");
                            if(scanf(" %.2f, %9s", aux->umbralSup.magnitud, aux->umbralSup.unidad) == 1)
                            {
                                printf("ingresar umbral inferior primero magnitud y luego su unidad\n");
                                {
                                    if(scanf(" %.2f, %9s", aux->umbralInf.magnitud, aux->umbralInf.unidad) == 1);
                                    {
                                        valR= IMPOLUTO;
                                        *listado = aux;
                                    }
                                }
                            }
                        }

                    }
                }
            }
            (*pcant)++;
        }
        if(valR == ERROR)
        {
            free(aux);
        }
    }
    else 
    {
        printf("la lista esta vacia\n ");
        valR = ERROR;
        
    }



    return valR;
}

void quitar(sensor_t** listado, int* pcant)
{
    sensor_t* aux = NULL;
    int criterio, id, tipo, i =0;
    int coincide;
    char  valor[24];
    if(*listado != NULL && pcant != NULL)
    {
        printf("Buscar por ID (1)\n, Buscar por NombreExt(2)\n Buscar MarMod(3)\n Buscar tipo(4)\n");
        scanf(" %d", &criterio);
        if(criterio == 1)
        {
            scanf(" %d", &id);
            while(id>0 && i<*pcant)
            {
                if(listado[i]->id == id)
                {
                    free(*listado);
                }
                
                
                i++;
            }
        }
        else if(criterio == 2 || criterio == 3)
        {
            scanf(" %23s", &valor);
            while (i<*pcant)
            {
                if(listado[i]->NombreExt == valor || listado[i]->MarMod == valor)
                {
                    free(*listado);
                }
                i++;
            }
        }
        else if(criterio == 4)
        {
            scanf(" %d", &tipo);
            while (i<*pcant)
            {
                if(listado[i]->Tipo == tipo)
                {
                    free(*listado);
                }
            }
        }
        else
        {
            printf("Error al poner el criterio\n");
        }

    }
    
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
                agregar(&listado, &cant);
            }
            else if(op==2)
            {
                quitar(&listado, &cant);
            }
            else if(op==3)
            {
                //listar
            }
        } while (op != 4);
        
    }



    return 0;
}
