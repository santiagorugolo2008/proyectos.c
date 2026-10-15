#ifndef SENSOR_H
#define SENSOR_H

 
/**
 * \file    sensor.h
 * \brief   Tipos y constantes del TPO N°2 (sensores).
 * \author  Santiago Rugolo
 */
 
/* Constantes simbólicas */
#define TRUE      1
#define FALSE     0
#define IMPOLUTO  0
#define ERROR     1
 
/* Tamaños (incluyen el '\0') */
#define LARGO_STR   11   /* string de 10 letras */
#define LARGO_EXT   24   /* string de 23 letras */
 
/**
 * \brief Acciones posibles del sensor.
 */
typedef enum
{
    aperturaR,
    aperturaN,
    aperturaL,
    cierreR,
    cierreN,
    cierre
} accion_t;
 
/**
 * \brief Umbral de un sensor.
 */
typedef struct
{
    float magnitud;
    char  unidad[LARGO_STR];
} umbral_t;
 
/**
 * \brief Estructura del archivo binario.
 */
typedef struct
{
    int           ID;
    char          Nombre[LARGO_STR];
    char          Ubicacion[LARGO_STR];
    char          Marca[LARGO_STR];
    char          Modelo[LARGO_STR];
    unsigned char Tipo;
    umbral_t      umbralSup;
    umbral_t      umbralInf;
    accion_t      accion;
} sensorF_t;
 
/**
 * \brief Estructura del sistema.
 *        NombreExt = Nombre + " (" + Ubicacion + ")"
 *        MarMod    = Marca + " - " + Modelo
 */
typedef struct
{
    int           ID;
    char          NombreExt[LARGO_EXT];
    char          MarMod[LARGO_EXT];
    unsigned char Tipo;
    umbral_t      umbralSup;
    umbral_t      umbralInf;
    accion_t      accion;
} sensor_t;
 
/* Prototipos */
sensor_t  * ajustar     (sensorF_t *origen);
sensorF_t * ajustarBack (sensor_t  *origen);
int   agregar (sensor_t ***listado, int *pcant);
void  quitar  (sensor_t ***listado, int *pcant);
void  listar  (sensor_t **listado, int cant);
/* Consultas de criterio (una por campo) */
int IDEq        (sensor_t *dato, void *valor);
int NombreExtEq (sensor_t *dato, void *valor);
int MarModEq    (sensor_t *dato, void *valor);
int TipoEq      (sensor_t *dato, void *valor);
int UmbralSupEq (sensor_t *dato, void *valor);
int UmbralInfEq (sensor_t *dato, void *valor);
int AccionEq    (sensor_t *dato, void *valor);
 
#endif
 
