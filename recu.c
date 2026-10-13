
#include <stdio.h>
#include <stdlib.h>
#define EXITO 0
#define ERROR -1
typedef struct 
{
    int id;
    float valor;
    int estado;
    int timestamp;
} Medicion;

// punto a

Medicion* reservarMemoria(int cantidad)
{
    Medicion *p = NULL;

    if (cantidad<=0)
    {
        printf("Error cantidad de mediciones invalida\n");
    }
    else
    {
        p = (Medicion *) malloc(cantidad * sizeof(Medicion));
        if(p == NULL)
        {
            printf("ERROR AL RESERVAR MEMORIA\n");
        }
        else
        {
            printf("MEMORIA SOLICITADA CON EXITO :)\n");
        }
    }

    return p;
}

// punto b

int CargarMedicion(Medicion* p)
{
    int valR = ERROR;
    printf("ingrese id, valor, estado, timestamp\n");
    if(scanf(" %d %f %d %d", &p->id, &p->valor, &p->estado, &p->timestamp) == 4)
    {
        valR = EXITO;
    }
    else
    {
        printf("ERROR: dato invalido\n");
    }

    return valR;
    
}

int CargarPorTeclado(Medicion *mediciones, int cantidad)
{
    int valR = EXITO;
    int i;
    if(mediciones == NULL || cantidad <= 0)
    {
        printf("Error No hay memoria\n");
        valR = ERROR;
    }
    else
    {
        for (i=0; (i<cantidad ) && (valR == EXITO) ; i++)
        {
           valR = CargarMedicion(mediciones + i);
        }
    }
    return valR;
}

//punto c 

void imprimirCampos(Medicion* estructura)
{
    
    if(estructura != NULL)
    {
        printf("El id es: %d\n", estructura->id);
        printf("valor: %.2f\n", estructura->valor);
        printf("estado: %d\n", estructura->estado);
        printf("timestamp: %d\n", estructura->timestamp);
    }
    else
    {
        printf ("puntero nulo\n");
    }
}

// punto d 

int promedio(Medicion* array, int cantidad, int estado, float *p)
{
    int valR = ERROR;
    float suma = 0;
    int i;
    int contador = 0;
    printf("calculando promedio\n");
    if(cantidad > 0 && array != NULL && p != NULL)
    {
        for(i=0; i<cantidad; i++)
        {
            if(array[i].estado == estado)
            {
                suma = suma + array[i].valor;
                contador ++;
            }
        }
        if (contador  > 0)
        {
            *p = suma/contador;
            valR = EXITO;
        }
        else
        {
            printf ("no hay mediciones con estado: %d\n" , estado);
        }
    }
    return valR;
}

//punto e

Medicion* buscarMedicion(Medicion *array, int cant, int id)
{
   int i;
   Medicion *p = NULL;
   if(cant>0 && array != NULL)
   {
        for (i=0; i<cant && p == NULL; i++)
        {
            if(array[i].id == id)
            {
                p = &(array[i]);
            }
        }
   }
   
    return p;
}

//PUNTO F

void ordenarArray(Medicion *array, int cant)
{
    int i, j;
    Medicion aux;
    if(array == NULL || cant <=0)
    {
        printf("Error\n");
    }
    else
    {
        for(i=0; i<cant - 1 ; i++)
        {
            for ( j = 0; j < cant -1 -i; j++)
            {
                if (array[j].valor > array[j+1].valor )
                {
                    aux = array[j];
                    array[j] = array[j+1];
                    array[j+1] = aux;
                }
            }
            
        }
    }
}

//punto g

int main(int argc, char *argv[])
{
    int cantidad;
    int valR = ERROR;
    float prom;
    int estado;
    int id;
    int i=0;
    Medicion *encontrada = NULL;
    Medicion *p = NULL;
    if(argc != 2 && argc != 3)
    {
        printf("error al cargar el argumento\n");

    }
    else
    {
        cantidad = atoi(argv[1]);
        if (cantidad <= 0)
        {
            printf("Error cantidad invalida\n");
        }
        else
        {
            p = reservarMemoria(cantidad);
            if(p==NULL)
                {
                    printf(":(");
                }
                else
                {
                    printf("cargar los valores\n");
                    valR = CargarPorTeclado(p, cantidad);
                    if (valR==EXITO)
                    {
                        printf("se cargo con exito\n");
                         if( argc == 3)
                        {
                            estado = atoi(argv[2]);
                            if (promedio(p, cantidad, estado, &prom) == EXITO)
                            {
                                printf("promedio = %.2f\n estado = %d\n",prom, estado );
                            }
                           
                        }
                        printf("Ingrese un id para buscar una medicion\n");
                         if (scanf(" %d", &id) == 1)
                      {
                         if(id < 0)
                            {
                                printf("id invalido\n");
                            }
                            else
                            {
                                encontrada = buscarMedicion(p, cantidad, id);
                                if(encontrada == NULL)
                                {
                                    printf("NO SE PUDO ENCONTRAR\n");
                                }
                                else
                                {
                                    imprimirCampos(encontrada);
                                }
                            }
                        }
                            printf("ordenar por valor de menor a mayor\n");
                            ordenarArray(p, cantidad);
                            for (i=0; i<cantidad;i++)
                            {
                                imprimirCampos(p + i);
                            }
                        }
                        else
                        {
                             printf("no se cargo de manera exitosa\n");
                        }
                
                    
                }
            
        
        
        }
    }
    free(p);

    return 0;
}

