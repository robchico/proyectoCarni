/*
 @rob
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * gets(char *);

#include "estructura.h"

//menu principal
int menu1(baseDeDatos bd){
  int op;
  printf("\n\n");
  printf("1. Abrir fichero\n");
  printf("2. Añadir registro\n");
  printf("3. Modificar registro\n");
  printf("4. Eliminar registro\n");
  printf("5. Visualizar registros\n");
  printf("6. Salir\n\n");    
  printf("   Opcion: ");
  do
  {
    scanf("%d", &op); fflush(stdin);
    if (op < 1 || op > 6)
      printf("Opcion no válida. Elija otra: ");
  }
  while (op < 1 || op > 6);

  if (op > 1 && op < 6 && !bd.fes)
  {
    printf("No hay un fichero abierto.\n");
    return 0;
  }
  return op;
}

//menu clientes
int menu2(baseDeDatos bd,char cadena[10]){
    
    int op;
  printf("\n\n");
  printf("1. Abrir fichero %s\n",cadena);
  printf("2. Añadir registro %s\n",cadena);
  printf("3. Modificar registro %s\n",cadena);
  printf("4. Eliminar registro %s\n",cadena);
  printf("5. Visualizar registros %s\n",cadena);
  printf("6. Salir\n\n");    
  printf("   Opcion: ");
  
  do{
      
    scanf("%d", &op); fflush(stdin);
    if (op < 1 || op > 6)
      printf("Opcion no válida. Elija otra: ");
    
  }while (op < 1 || op > 6);

  if (op > 1 && op < 6 && !bd.fes)
  {
    printf("No hay un fichero abierto.\n");
    return 0;
  }
  return op;
}