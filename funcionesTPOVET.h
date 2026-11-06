/**
    \file    funciones_cliente.h
    \brief   Prototipos de funciones correspondientes al Cliente
    \authors Romano, Iván | Rugolo, Santiago | Chaiman Hans, Matías David
    \date    2026.09.01
    \version 1.0.0
*/

#ifndef FUNCIONES_CLIENTE_H
#define FUNCIONES_CLIENTE_H

#include "protocolo.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define ARCHIVO_CFG "cfg/cliente.cfg"
typedef struct nfecha_t {
  unsigned int dia : 5;
  unsigned int mes : 4;
  unsigned int anio : 12;
} NFECHA_t;

typedef struct nhora_t {
  unsigned int hora : 4;
  unsigned int min : 6;
  unsigned int am_pm : 1;
} NHORA_t;

typedef struct paciente_t {
  unsigned char tipoID;
  int id;
  int pac;
  char nombre[CARACTERES];
  NFECHA_t nacimiento;
  int responID;
} PACIENTE_t;

typedef struct pac_t {
  PACIENTE_t paciente;
  struct pac_t *siguiente;
} NODO_PACIENTE_t;

typedef struct responsable_t {
  int responID;
  char apellido[CARACTERES];
  char nombre[CARACTERES];
  unsigned long int telcont;
} RESPONSABLE_t;

typedef struct res_t {
  RESPONSABLE_t responsable;
  struct res_t *siguiente;
} NODO_RESPONSABLE_t;



typedef struct turno_t {
  int responID;
  int pacID;
  NFECHA_t fecha;
  NHORA_t hora;
  TURNO_t *siguiente;
} TURNO_t;
typedef TURNO_t TURNOS_t;

typedef struct tipo_animal_wire_t {
  unsigned char tipoID;
  char nombre[CARACTERES];
} TIPO_ANIMAL_WIRE_t;

typedef struct consulta_paciente_resp_t {
  PACIENTE_t paciente;
  RESPONSABLE_t responsable;
  int resp_encontrado;
} CONSULTA_PACIENTE_RESP_t;

typedef struct consulta_turno_detalle_t {
  TURNO_t turno;
  char nombre_paciente[CARACTERES];
  char nombre_responsable[CARACTERES];
  char apellido_responsable[CARACTERES];
} CONSULTA_TURNO_DETALLE_t;
typedef struct tipoapac_t {
  unsigned char tipoID;
  char *nombre;
} TIPOAPAC_t;

// Punteros a función para los menús
typedef void (*accion_menu_t)(int sockfd);

// Conexión y configuración
int leer_configuracion_cliente(char *ip, int *puerto);
int conectar_con_servidor(const char *ip, int puerto);

// Control de Menús
void menu_principal(int sockfd);
void menu_consultar(int sockfd);
void menu_agregar_turno(int sockfd);
void menu_paciente(int sockfd);
void menu_responsable(int sockfd);
void menu_configuracion(int sockfd);

// Menú 1: Consultar Información
void verificar(int cant, NODO_PACIENTE_t* lista_pacientes, NODO_RESPONSABLE_t* lista_responsables, char *nombre, char *apellido);
NODO_PACIENTE_t* buscarPacientePorID(NODO_PACIENTE_t* lista, int id);
NODO_RESPONSABLE_t* buscarResponsablePorID(NODO_RESPONSABLE_t* lista, int id);
void mostrarPacienteDeResponsable(NODO_PACIENTE_t* lista_paciente, int responID);
void mostrarDatosPaciente(NODO_PACIENTE_t *paciente);
void mostrarDatosResponsable(NODO_RESPONSABLE_t *responsable);
void consultar_paciente_id(NODO_PACIENTE_t* lista_pacientes, NODO_RESPONSABLE_t* lista_responsables);
void consultar_paciente_nombre(NODO_PACIENTE_t* lista_pacientes, NODO_RESPONSABLE_t* lista_responsables);
void consultar_responsable_id_cli(NODO_RESPONSABLE_t* lista_responsables, NODO_PACIENTE_t* lista_pacientes);
void consultar_responsable_nombre_apellido(NODO_RESPONSABLE_t* lista_responsables, NODO_PACIENTE_t* lista_pacientes);
void consultar_turnos_paciente(NODO_PACIENTE_t* lista_pacientes, NODO_RESPONSABLE_t* lista_responsables, TURNO_t* turnos);
void consultar_turnos_representante(NODO_PACIENTE_t* lista_pacientes, NODO_RESPONSABLE_t* lista_responsables, TURNO_t* turnos);
void consultar_turnos_por_fecha(NODO_PACIENTE_t* lista_pacientes, NODO_RESPONSABLE_t* lista_responsables, NFECHA_t fecha, TURNO_t* turnos);
void consultar_todos_los_pacientes(NODO_PACIENTE_t* lista_pacientes);
void consultar_todos_los_responsables(NODO_RESPONSABLE_t* lista_responsables);

// Menú 2: Agregar turno
void agregar_turno(int sockfd);

// Menú 3: Paciente
void agregar_paciente(int sockfd);
void modificar_paciente(int sockfd);
void eliminar_paciente(int sockfd);
void modificar_paciente_nombre(int sockfd);
void modificar_paciente_responsable(int sockfd);

// Menú 4: Responsable
void agregar_responsable_cli(RESPONSABLE_t nuevo_responsable);
void modificar_responsable_cli(int sockfd);
void eliminar_responsable_cli(int sockfd);

// Menú 5: Configuración
void mostrar_tipos_animales(int sockfd);
void agregar_tipo_animal(int sockfd);
void modificar_tipo_animal(int sockfd);
void eliminar_tipo_animal(int sockfd);

// Validaciones y Captura de Entradas
int validar_nfecha(NFECHA_t fecha);
int validar_nhora(NHORA_t hora);
void limpiar_buffer_stdin(void);
void leer_cadena(char *cadena, int longitud);

#endif
