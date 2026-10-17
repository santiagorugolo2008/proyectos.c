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


int pedirTipo(unsigned char* tipo)
{
    int valR = ERROR;
    int aux;

    printf("tipo (0 a 255): ");
    if(scanf(" %d", &aux) == 1 && aux>= 0 && aux<=255)
    {
        *tipo = (unsigned char)aux;
        valR = IMPOLUTO;
    }

    return valR;
}

int pedirUmbral(umbral_t *u, const char* texto)
{
    int valR = ERROR;

    printf("%s (magnitud y unidad): ", texto);
    if(scanf("%f %9s", &u->magnitud, &u->unidad)==2)
    {
        valR = IMPOLUTO;
    }
    return valR;
}

int pedirAccion(accion_t *a)
{
    int valR = ERROR;
    int aux;

    printf("Accion (0 a 5)");
    printf("0-aperturaR 1-aperturaN 2-aperturaL\n");
    printf("3-cierreR 4-cierreN 5-cierreL\n");
    scanf("%d", &aux);
    if(aux>=0 && aux<=255)
    {
        *a=(accion_t)aux;
        valR = IMPOLUTO;
    }
    return IMPOLUTO;
}


int pedirDatos(sensor_t *p)
{
    int valR = ERROR;

    printf("Id: ");
    if(scanf("%d", &p->id)==1)
    {
        printf("Nombre(Ubicacion): ");
        if(scanf(" %22s", p->NombreExt)==1)
        {
            printf("Marca-Modelo: ");
            if(scanf(" %22s", p->MarMod)==1)
            {
                
                if(pedirTipo(&p->Tipo)== IMPOLUTO && pedirAccion(&p->accion)==IMPOLUTO && pedirUmbral(&p->umbralSup, "Umbral Superior")==IMPOLUTO)
                {
                    if(pedirUmbral(&p->umbralInf, "Umbral Inferior")==IMPOLUTO)
                    {
                        valR=IMPOLUTO;
                    }
                    
                }
            }
        }
    }

    return valR;
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
            pedirDatos(&aux[*pcant]);
        }
        
    }
    return valR;
}

int IDEq(sensor_t *dato, void *valor)
{
    int valR = FALSE;

    if(dato != NULL && valor != NULL)
    {
        if(dato->id == *(int*)valor)
        {
            valR = TRUE;
        }
    }

    return valR;
}

int NombreExtEq(sensor_t *dato, void* valor)
{
    int valR = FALSE;
    if(dato != NULL && valor != NULL)
    {
        if(strcmp(dato->NombreExt, (char*)valor)==0)
        {
            valR = TRUE;
        }
    }


    return valR;
}


int MarModEq(sensor_t *dato, void* valor)
{
    int valR = FALSE;
    if(dato != NULL && valor != NULL)
    {
        if(strcmp(dato->MarMod, (char*)valor)==0)
        {
            valR = TRUE;
        }
    }


    return valR;
}

int TipoEq(sensor_t* dato, void* valor)
{
    int valR = FALSE;

    if(dato != NULL && valor != NULL)
    {
        if(dato->Tipo == *(unsigned char*)valor)
        {
            valR = TRUE;
        }
    }

    return valR;
}

int UmbralSupEq(sensor_t *dato, void* valor)
{
    int valR = FALSE;
    umbral_t* p = (umbral_t*)valor;
    if(dato != NULL && valor != NULL)
    {
        if(dato->umbralSup.magnitud == p->magnitud)
        {
            if(strcmp(dato->umbralSup.unidad, p->unidad)==0)
            {
                valR = TRUE;
            }
        }
    }


    return valR;
}

int UmbralInfEq(sensor_t *dato, void* valor)
{
    int valR = FALSE;
    umbral_t* p = (umbral_t*)valor;
    if(dato != NULL && valor != NULL)
    {
        if(dato->umbralInf.magnitud == p->magnitud)
        {
            if(strcmp(dato->umbralInf.unidad, p->unidad)==0)
            {
                valR = TRUE;
            }
        }
    }


    return valR;
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
}
