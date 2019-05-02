/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: mañana
 *
 * Created on 2 de mayo de 2019, 8:27
 */

#include <stdio.h>
#include <stdlib.h>

#include "estructura.h"


/*
 * 
 */
int main(int argc, char** argv) {
 int opcion = 0;
  baseDeDatos articulos;
  IniciarBaseDeDatos(&articulos);

  do
  {
    opcion = menu1(articulos);
    switch (opcion)
    {
      case 1: // abrir fichero
        menuAbrirBaseDeDatos(&articulos);
        break;
      case 2: // añadir registro al final del fichero
        menuAnyadirReg(&articulos);
        break;
      case 3: // modificar registro
        menuModificarReg(articulos);
        break;
      case 4: // eliminar registro
        menuEliminarReg(&articulos);
        break;
      case 5: // visualizar registros
        menuVisualizarRegs(articulos);
        break;
      case 6: // salir
        CerrarBaseDeDatos(&articulos);
    }
  }while(opcion != 6);
    return 0;
    
}

