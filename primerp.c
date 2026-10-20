#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1
#define VALIDO 0
#define ELEMENTOS 10000
/*
int * resumirVector (int * origen, int longitud, int limInf, int limSup, int * longResu)
{
    int i=0, j =0, encontrado, k;
    int * vec = NULL;
    int *aux = NULL;
  
    if(longitud <= 0 || origen == NULL || limInf>limSup || longResu == NULL)
    {
        printf("Error \n");
    }
    else
    {
        vec = malloc(sizeof(int)*longitud);
        if(vec == NULL)
        {
            printf("ERROR AL PEDIR MEMORIA\n");
            *longResu = -1;
        }
        else
        {
            for(i = 0; i<longitud; i++)
            {
                if(origen[i]>=limInf && origen[i]<=limSup)
                {
                   encontrado = 0;
                    for (k = 0; k < j && !encontrado; k++)
                    {
                        if (vec[k] == origen[i])
                        {
                            encontrado = 1;
                        }
                    }
                    if (!encontrado)
                    {
                        vec[j] = origen[i];
                        j++;
                    }
                }
            }
            if(j==0)
            {
                free(vec);
                vec = NULL;
            }
            else
            {
                aux = realloc(vec, sizeof(int)*j);
                if(aux != NULL)
                {
                    *longResu = j;
                    vec = aux;
                }
                else
                {
                    free(vec);
                    vec = NULL;
                    *longResu = ERROR;
                }
            }
        }
    }

    return vec;
}

// ej 2



int main(int argc, char* argv[])
{
    
    int num[ELEMENTOS];
    int longitud = ELEMENTOS;
    int i = 0;
    int limInf=0, limSup=0;
    int *resu = NULL;
    int longResu;
    
    if(argc == 3)
    {
        limInf=atoi(argv[1]);
        limSup=atoi(argv[2]);
        while (i<ELEMENTOS)
        {
            num[i] = rand() % 101;
            i++;  
        }
        resu = resumirVector(num, longitud, limInf, limSup, &longResu);
        if(longResu == ERROR)
        {
            printf("ERROR AL PEDIR MEMORIA\n");
        }
        else
        {
            printf("Cantidad de valores: %d\n", longResu);
            for(i=0; i<longResu; i++)
                printf("%d\n", num[i]);
        }
        
    }
    else
    {
        printf("ERROR DE ARGUMENTO\n");
    }
    free(resu);

    return 0;
}

// ej 3


int analisisT (unsigned char byte1, unsigned char byte2, int * valor, int * id)
{
    int valR = 0;
    int id_temp=0, parte_alta=0, parte_baja = 0;
    int docena =0, unidad =0;

    if((byte1 >> 7 & 1)==0)
    {
        *valor = byte1>>4;
        id_temp = (byte1 << 4) >> 4;
        if(id_temp >=0 && id_temp <= 9)
        {
            *id = id_temp;
        }
        else
        {
            valR = 1;
        }
    }
    else
    {
        parte_alta = (byte2>>4); //    0 0 0 1 1 0 0 0 
        parte_baja = (byte1<<1)>>5; // 0 0 0 0 0 0 1 1 
        *valor = (parte_alta<<3) | parte_baja;

        docena = (byte2<<4)>>4; 
        unidad= (byte1 << 1)>>4;     
        if(docena>= 0 && docena<= 9 && unidad >= 0 && unidad<= 9)
        {
            *id = docena*10 + unidad;
            valR = 0;
        } 
        else
        {
            valR = 1;
        }

    }

    return valR;
}
*/

int traducirS (char * origen, char * convertido)
{
    int valR = 1;
    int largo= 0;
    int i = 0, j = 0;
    int valorAscii = 0;
    int valido = 0;
    
    if(origen != NULL && convertido != NULL)
    {
        largo = strlen(origen);
        if((largo % 3)==0)
        {
            while(i<largo)
            {   
                if(origen[i]>'0' && origen[i] < '9')
                {
                   valido = 1;
                }
                i++;
            }
            if(valido)
            {
                i=0;
                while(i<largo)
                {
                    valorAscii = (origen[i]-'0')*100 + (origen[i+1]-'0')*10  + (origen[i+2]-'0');
                    if(valorAscii>= 32 && valorAscii <= 126)
                    {
                        convertido[j]= (char)valorAscii;
                        j++;
                    }
                    i = i + 3;
                }
                convertido[j] = '\0';
                valR = 0;
            }
        }
    }

    return valR;
}


