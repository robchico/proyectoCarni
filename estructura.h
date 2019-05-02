/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estructura.h
 * Author: mañana
 *
 * Created on 2 de mayo de 2019, 9:01
 */

#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* ESTRUCTURA_H */

// Definición del tipo registro
typedef struct
{
  char referencia[20];
  double precio;
} registro;

// Definición del tipo baseDeDatos.
typedef struct
{
  char nomFichero[20]; // nombre del fichero
  FILE *fes;           // flujo hacia/desde el fichero
  int nregs;           // número de registros
  int tamreg;          // tamaño del registro en bytes
  int regsEliminados;  // 1 cuando se haya borrado algún registro
} baseDeDatos;

typedef struct{
  double codigoCli;  //primarykey
  char dniCli[15];
  char nombreCli[80];
  char direccionCli[100];
  char poblacionCli[50];
  char provinciaCli[30];
  char cpCli[6];
} regClientes;

typedef struct{
  double codigoPro;  //primarykey
  char dniPro[15];
  char nombrePro[80];
  char direccionPro[100];
  char poblacionPro[50];
  char provinciaPro[30];
  char cpPro[6];
} regProveedores;

typedef struct{
  char referenciaArt[20];//primarykey
  char descrpcionArt[80];
  double existencias;
  double precio;
  double stockMinimo;
  double codigoSec; //FORGEIN KEY tabla secciones
} regArticulos;

typedef struct{
  double codigoSec;//primarykey
  char descrpcionSec[80];
} regSecciones;

typedef struct{
  double codigoIva;//primarykey
  short descrpcionIva;
} regIva;

typedef struct{
  double codigoPago;//primarykey
  char descrpcionPago[80];
} regPagos;



void IniciarRegistro(registro *reg);
int Existe(char *nombreFichero);
int EscribirRegistro( int i, registro reg, baseDeDatos bd );
void AnyadirRegistro( registro reg, baseDeDatos *bd );
registro LeerRegistro( int i, baseDeDatos bd );
int BuscarRegistro( char *str, int nreg, baseDeDatos bd );
int EliminarRegistro( char *ref, baseDeDatos *bd);
void IniciarBaseDeDatos(baseDeDatos *bd);
int ActualizarBaseDeDatos( baseDeDatos *bd );
void CerrarBaseDeDatos( baseDeDatos *bd );
int menuAbrirBaseDeDatos(baseDeDatos *bd);
void menuAnyadirReg(baseDeDatos *bd);
void menuModificarReg(baseDeDatos bd);
int menuEliminarReg(baseDeDatos *bd);
void menuVisualizarRegs(baseDeDatos bd);
int menu1(baseDeDatos bd);
int menu2(baseDeDatos bd,char cadena[10]);
