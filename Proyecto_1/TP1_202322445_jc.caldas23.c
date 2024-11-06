#include <stdio.h>
#include <stdlib.h>

//NOMBRE: Juan Camilo Caldas
//CODIGO: 202322445
//CORREO: jc.caldas23@uniandes.edu.co

#define NOMBRES_SIZE 70
#define CEDULA_SIZE 13
#define CODIGO_SIZE 4
#define DIA_SIZE 1
#define MESANYO_SIZE 2
#define NACIMIENTO_ISLAMICO 2
#define FILE_SIZE ( NOMBRES_SIZE + CEDULA_SIZE + CODIGO_SIZE + DIA_SIZE + MESANYO_SIZE + NACIMIENTO_ISLAMICO )

//TO DO: Declare el tipo y tamaño adecuados para que las variables puedan contener el correspondiente valor
//del archivo de entrada
// NO MODIFIQUE NINGUNA OTRA COSA EN EL PROGRAMA
// Estructura para manejar los datos de entrada.
struct Datos {
   unsigned int codigo;
   char nombres[70];
   char cedula[13];
   unsigned char dia;
   unsigned short mesanyo;
   short islamico;
} datos;

unsigned int getFileSize ( FILE * );
unsigned int loadData ( struct Datos *, char * );
unsigned int getNumber ( FILE *, char *, unsigned int );
void printChrs ( char *, unsigned int );

int main( int argc, char *argv[] )
{

   if ( argc != 2 ){
      printf( "*** ATENCION! Uso del comando:\n\tprograma archivo-de-datos\n" );
      return 1;
   }

   if ( loadData( &datos, argv[1] ) != FILE_SIZE ) return 1;

   printf( "Codigo:%u\n", datos.codigo );
   printf( "Nombres:" );
   printChrs( datos.nombres, sizeof( datos.nombres ) );
   printf( "\n" );
   printf( "Cedula:" );
   printChrs( datos.cedula, sizeof( datos.cedula ) );
   printf( "\n" );
   printf( "Dia:%u\n", datos.dia );
   printf( "Mes-Anyo:%u-%u\n", datos.mesanyo >> 12, datos.mesanyo & 0x0FFF );
   printf( "Diferencia anyo islamico:%d\n", datos.islamico);

   return 0;
} // main

/**
 * Calcula la longitud en bytes de un archivo.
 * Pre   El archivo esta abierto.
 * Parametros  f Apuntador al descriptor del archivo.
 * Retorna  la longitud en bytes del archivo apuntado por f.
 */
unsigned int getFileSize ( FILE * f ){

   unsigned int longArchivo;

   if ( fseek( f, 0, SEEK_END ) || ( longArchivo = ftell( f ) ) < 0 || fseek( f, 0, SEEK_SET ) ) {
      longArchivo = 0;
   }

  return longArchivo;
} // getFileSize

/**
 * Lee del archivo un número binario de n bytes en la variable apuntada por p.
 * El número se supone en formato big endian y lo convierte a little endian.
 */
unsigned int getNumber ( FILE * f, char * p, unsigned int n ){

   int i;

   p = p + n - 1;
   for ( i = 0; i < n && ( fread( p-i, sizeof( char ), 1, f ) == sizeof( char ) ); i++ );

   return i;
} // getNumber

/**
 * Inicializa una estructura con los datos del archivo.
 * Abre el archivo de datos, lo carga en memoria y los guarda en una estructura de datos.
 */
unsigned int loadData ( struct Datos * datosP, char * nombreArchivo ){

   FILE * f = NULL;
   unsigned int longFisica = 0;
   unsigned int nBytes;

   if ( !( f = fopen( nombreArchivo, "rb" ) ) ) {
      printf( "*** ATENCION! No se logro abrir el archivo %s\n", nombreArchivo );
   }
   else if ( getFileSize( f ) != FILE_SIZE ){
         printf( "*** ATENCION! Tamanyo del archivo %s no concuerda\n", nombreArchivo );
   }
   else {	   
      nBytes = CODIGO_SIZE;
      if ( getNumber( f, (char *)(&datosP->codigo), sizeof( datosP->codigo ) ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer bien el codigo del archivo %s\n", nombreArchivo );
         return longFisica;
      }
	  longFisica += nBytes;
	  
      nBytes = NOMBRES_SIZE;
      if ( fread( datosP->nombres, sizeof( char ), sizeof( datosP->nombres ), f ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer bien los nombres del archivo %s\n", nombreArchivo );
         return longFisica;
      }
      longFisica += nBytes;
	  
      nBytes = CEDULA_SIZE;
      if ( fread( datosP->cedula, sizeof( char ), sizeof( datosP->cedula ), f ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer bien la cedula del archivo %s\n", nombreArchivo );
         return longFisica;
      }
	  longFisica += nBytes;
	  
      nBytes = DIA_SIZE;
      if ( getNumber( f, (char *)(&datosP->dia), sizeof( datosP->dia ) ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer bien el dia del archivo %s\n", nombreArchivo );
         return longFisica;
      }
	  longFisica += nBytes;
	  
      nBytes = MESANYO_SIZE;
      if ( getNumber( f, (char *)(&datosP->mesanyo), sizeof( datosP->mesanyo ) ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer bien mes-anyo del archivo %s\n", nombreArchivo );
         return longFisica;
      }
	  longFisica += nBytes;
	  
      nBytes = NACIMIENTO_ISLAMICO;
      if ( getNumber( f, (char *)(&datosP->islamico), sizeof( datosP->islamico ) ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer bien la diferencia a anyo islamico %s\n", nombreArchivo );
         return longFisica;
      }
      longFisica += nBytes;
   }

   fclose( f );

   return longFisica;
} // loadData

/**
 * Imprime l caracteres a partir del caracter apuntado por p.
 */
void printChrs ( char * p, unsigned int l ){

   int i;

   for ( i = 0; i < l; i++ ){
      printf( "%c", p[i] );
   }

} // printChrs
