/*
 @rob
 * inicion mocelo MVC
 * funciones creadas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * gets(char *);

#include "estructura.h"

//
void IniciarRegistro(registro *reg){
  *(reg->referencia) = 0;
  reg->precio = 0.0;
}

int Existe(char *nombreFichero){
  FILE *pf = NULL;
  int exis = 0; // no existe

  // ¿Existe el fichero?
  if ((pf = fopen(nombreFichero, "r")) != NULL)
  {
    exis = 1;   // existe
    fclose(pf);
  }
  return exis;
}

//
int EscribirRegistro( int i, registro reg, baseDeDatos bd ){
  if (i >= 0 && i <= bd.nregs)
  {
    // Situar el puntero de L/E en el registro i
    fseek(bd.fes, i * bd.tamreg, SEEK_SET);
    // Sobreescribir el registro con la nueva información
    fwrite(&reg, bd.tamreg, 1, bd.fes);
    if (!ferror(bd.fes)) return 1;
    printf("Error al escribir en el fichero\n");
  }
  else
    printf("Número de registro fuera de límites\n");
  return 0;
}

//
void AnyadirRegistro( registro reg, baseDeDatos *bd ){
  // Añadir un registro al final del fichero e incrementar
  // el número de registros
  if (EscribirRegistro( bd->nregs, reg, *bd )) bd->nregs++;
}

//
registro LeerRegistro( int i, baseDeDatos bd ){
  registro reg;
  IniciarRegistro(&reg);

  if (i >= 0 && i < bd.nregs){
    // Situar el puntero de L/E en el registro i
    fseek(bd.fes, i * bd.tamreg, SEEK_SET);
    // Leer la información correspondiente al registro i
    fread(&reg, bd.tamreg, 1, bd.fes);
  }
  else
    printf("Número de registro fuera de límites\n");

  // Devolver el registro correspondiente.
  return reg;
}

//
int BuscarRegistro( char *str, int nreg, baseDeDatos bd ){
  // Buscar un registro por una subcadena de la referencia
  // a partir de un registro determinado. Si se encuentra,
  // se devuelve el número de registro, o -1 en otro caso
  int reg_i = 0;
  registro reg;

  if (str == NULL) return -1;
  if (nreg < 0) nreg = 0;
  for ( reg_i = nreg; reg_i < bd.nregs; reg_i++ )
  {
    // Obtener el registro reg_i
    reg = LeerRegistro(reg_i, bd);
    // ¿str está contenida en referencia?
    if (strstr(reg.referencia, str))
      return reg_i; // devolver el número de registro
  }
  return -1; // la búsqueda falló
}

//
int EliminarRegistro( char *ref, baseDeDatos *bd){
  int reg_i = 0;
  registro reg;
  // Buscar la referencia y marcar el registro correspondiente
  // para poder eliminarlo cuando se requiera
  for ( reg_i = 0; reg_i < bd->nregs; reg_i++ )
  {
    // Obtener el registro reg_i
    reg = LeerRegistro(reg_i, *bd);
    // ¿Tiene la referencia ref?
    if (strcmp(ref, reg.referencia) == 0)
    {
      // Marcar el registro con la referencia "borrar"
      strcpy(reg.referencia, "borrar");
      // Grabarlo
      EscribirRegistro( reg_i, reg, *bd );

      bd->regsEliminados = 1;
      return 1;
    }
  }
  return 0;
}

void IniciarBaseDeDatos(baseDeDatos *bd){
  *(bd->nomFichero) = 0;
  bd->fes = NULL;
  bd->nregs = 0;
  bd->tamreg = sizeof(registro);
  bd->regsEliminados = 0;
}

//int ActualizarBaseDeDatos( baseDeDatos *bd );

void CerrarBaseDeDatos( baseDeDatos *bd ){
  if (bd->regsEliminados)
  {
    bd->regsEliminados = 0;
    ActualizarBaseDeDatos(bd);
  }
  if (bd->fes) fclose(bd->fes); // cerrar el fichero actual
  bd->fes = NULL;
  bd->nregs = 0;      // poner a cero el nº de registros
}

int ActualizarBaseDeDatos( baseDeDatos *bd ){
  int reg_i = 0;
  registro reg;
  baseDeDatos bdtemp;
  IniciarBaseDeDatos(&bdtemp);

  // Crear una bd temporal.
  bdtemp.fes = tmpfile();
  if (bdtemp.fes == NULL)
  {
    printf("Error: No se puede crear un fichero temporal\n");
    return 0;
  }
  
  // Copiar en el fichero temporal todos los registros del
  // fichero actual que no estén marcados para "borrar"
  for ( reg_i = 0; reg_i < bd->nregs; reg_i++ )
  {
    reg = LeerRegistro(reg_i, *bd);
    if (strcmp(reg.referencia, "borrar") == 0) continue;
    AnyadirRegistro(reg, &bdtemp);
  }
  // Copiar en el fichero actual todos los registros del temporal.
  // Para ello, creamos de nuevo el actual.
  CerrarBaseDeDatos(bd);
  if ((bd->fes = fopen(bd->nomFichero, "w+b")) == NULL)
  {
    printf("Error: No se puede crear el fichero\n");
    return 0;
  }
  rewind(bdtemp.fes); // volver al principio del fichero temporal
  for ( reg_i = 0; reg_i < bdtemp.nregs; reg_i++ )
  {
    reg = LeerRegistro(reg_i, bdtemp);
    AnyadirRegistro(reg, bd);
  }
  
  return 1;
}
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// Funciones que responderán a cada una de las opciones del menú
//
int menuAbrirBaseDeDatos(baseDeDatos *bd){
  char resp = 'n';
  char *modo;

  if (bd->fes)
  {
    printf("Ya hay un fichero abierto.\n");
    return 0;
  }

  printf("Nombre del fichero: ");
  gets(bd->nomFichero); // nombre fichero
  modo = "w+b";
  if (Existe(bd->nomFichero))
  {
    do
    {
      printf("Este fichero existe ¿Desea sobrescribirlo? (s/n) ");
      resp = tolower(getchar());
      fflush(stdin);
    }
    while (resp != 's' && resp != 'n');
    if (resp == 'n')
      modo = "r+b";
  }

  if ((bd->fes = fopen(bd->nomFichero, modo)) == NULL)
  {
    printf("Error: No se puede crear el fichero\n");
    bd->fes = 0; // fichero no abierto
    return 0;
  }
  // Establecer los datos longitud del registro y nº de registros
  bd->tamreg = sizeof(registro);
  fseek(bd->fes, 0, SEEK_END);
  bd->nregs = ftell(bd->fes)/sizeof(registro);
  rewind(bd->fes);
  printf("Fichero %s abierto\n", bd->nomFichero);
  return 1;
}

void menuAnyadirReg(baseDeDatos *bd){
  registro reg;
  
  printf("Referencia:    ");
  gets(reg.referencia);
  printf("Precio:        ");
  scanf("%lf", &reg.precio); fflush(stdin);
  AnyadirRegistro( reg, bd );
}

//
void menuModificarReg(baseDeDatos bd){
  registro reg;
  int op = 3, nreg = 0;
  
  if (bd.nregs == 0)
  {
    printf("fichero vacío\n");
    return;
  }

  // Solicitar el número de registro a modificar  
  printf("Número de registro entre 0 y %d: ", bd.nregs - 1); 
  scanf("%d", &nreg); fflush(stdin);

  // Leer el registro
  reg = LeerRegistro(nreg, bd);
  if (strcmp(reg.referencia, "") == 0 && reg.precio == 0.0) return;
  // Visualizarlo
  printf("%s\n", reg.referencia);
  printf("%g\n", reg.precio);
  
  // Modificar el registro
  do
  {
    printf("\n\n");
    printf("Modificar el dato:\n");
    printf("1. Referencia\n");
    printf("2. Precio\n");
    printf("3. Salir y salvar los cambios\n");
    printf("4. Salir sin salvar los cambios\n\n");
    printf("   Opción: ");
    scanf("%d", &op); fflush(stdin);
        
    switch( op )
    {
      case 1: // modificar referencia
        printf("Referencia:    ");
        gets(reg.referencia);
        break;
      case 2: // modificar precio
        printf("Precio:        ");
        scanf("%lf", &reg.precio); fflush(stdin);
        break;
      case 3: // guardar los cambios
        break;
      case 4: // salir sin guardar los cambios
        break;
    }
  }
  while( op != 3 && op != 4);

  if (op == 3) EscribirRegistro(nreg, reg, bd);             
}

//
int menuEliminarReg(baseDeDatos *bd){
  char referencia[20];
  int eliminado = 0;

  if (bd->nregs == 0)
  {
    printf("fichero vacío\n");
    return 0;
  }

  printf("Referencia: "); gets(referencia);
  eliminado = EliminarRegistro( referencia, bd);
  if (eliminado)
    printf("registro eliminado\n");
  else
    if (bd->nregs != 0)
      printf("referencia no encontrada\n");
    else
      printf("lista vacía\n");
  return eliminado;
}
  
//
void menuVisualizarRegs(baseDeDatos bd){
  registro reg;
  char str[20];
  int nreg = -1;

  IniciarRegistro(&reg);

  if (bd.nregs == 0)
  {
    printf("fichero vacío\n");
    return;
  }

  printf("conjunto de caracteres a buscar,'*' para buscar todos: ");
  gets(str);
  // str igual a * visualiza todos
  do
  {
    if ( *str != '*' )
      nreg = BuscarRegistro(str, nreg+1, bd);
    else
      if (++nreg == bd.nregs) break;
    if (nreg > -1)
    {
      reg = LeerRegistro(nreg, bd);
      printf("Registro: %d\n", nreg);
      printf("%s\n", reg.referencia);
      printf("%g\n\n", reg.precio);
    }
  }
  while (nreg != -1);

  if (strcmp(reg.referencia, "") == 0 && reg.precio == 0.0)
    printf("no se encontró ningún registro\n");
}
  
