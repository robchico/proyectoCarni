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
int menu(baseDeDatos bd);
