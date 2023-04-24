#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "pila.h"
#include "printformato.h"

int MAXCAR = 30;
int CantidadInicialDeJugadores = 100;
int CantidadInicialDeItems     = 10;


/////////////////////////////////////////////////////////////////////////////////////////
/*1. Crear perfil de jugador/a (nombre): El/la usuario/a ingresa un nombre de jugador/a y se crea un perfil en la aplicación. La cantidad de puntos de habilidad se inicializa en 0, y se genera un inventario vacío que almacenará los items que obtenga el/la jugador/a  a lo largo del juego.*/  

//╭────────────────────────────────────────────────────────────╮
//│           Agregar función para expandir el HashMap         │
//╰────────────────────────────────────────────────────────────╯
// Se necesita actualizar size del hashMap 
// comprobar si size es == capacity y aumentar la capacidad
// se podria realizar una funcion para ir aumentando la capacidad * factor

Data *igualarDatas(Data base) {
  Data *aux = (Data*) malloc(sizeof(Data));
  aux->puntosHabilidad = base.puntosHabilidad;
  aux->nObjetos = base.nObjetos;
  aux->items = base.items;
  return aux;
}


HashMap *crearPerfil(HashMap *jugadores)
{

  // Si no hay jugadores registrados, se crea el mapa
  if (jugadores == NULL) {
    printf("No hay jugadores registrados\n");
    jugadores=createMap(CantidadInicialDeJugadores); 
  }
  
// Agregar función para expandir el HashMap 

  // Se pide el nombre del jugador
  char *nombre = malloc(sizeof(char)*MAXCAR);
  printf("Ingrese el nombre del jugador: ");
  scanf("%s",nombre);
   
  if(searchMap(jugadores, nombre)!=NULL){
    printMensajeJugadorRepetido();
    free(nombre);
    return jugadores;
  }
  if(nombre!=NULL) printMensajeGeneroJugadorCorrectamente();
  // Se inserta el jugador en el mapa
  insertMap(jugadores,nombre);
  
  // Se busca el jugador en el mapa
 // Inicializa el espacio para 10 items

  //           Agregar codigo para expandir el HashMap         
  //           Agregar codigo para crear pila y guardar
  
  return jugadores;

  }


/////////////////////////////////////////////////////////////////////////////////////////
/*2. Mostrar perfil de jugador/a (nombre): El/la usuario/a ingresa el nombre de un/a jugador/a y la aplicación muestra su nombre, cantidad de puntos de habilidad y su inventario de items que ha obtenido hasta el momento.*/

void mostrarPerfil( HashMap *jugadores ) {
  //HashMap *local = jugadores; 

  // No hay jugadores registrados
  if (jugadores == NULL) {
    printf("No hay jugadores registrados\n");
    return;
  }

  // Se pide el nombre del jugador
  char *nombre = malloc (sizeof ( char ) * MAXCAR );
  printf( "Ingrese el nombre del jugador : ");
  scanf("%s", nombre);

  // Se busca el jugador en el mapa
  Pair *par = searchMap(jugadores, nombre);

  // No existe el jugador
  if( par == NULL){
    printf("No existe el jugador \n");
    return; 
  }
  // Se muestran los datos del jugador
  mostrarDatosJugador(par);

}

/////////////////////////////////////////////////////////////////////////////////////////
/*3. Agregar item a jugador/a (nombre, item): El/la usuario/a ingresa el nombre de un/a jugador/a y el nombre de un item que ha obtenido. La aplicación agrega el item al inventario de el/la jugador/a. Si el/la jugador/a no existe, se debe mostrar un aviso.*/

//╭────────────────────────────────────────────────────────────╮
//│           Agregar función para expandir el inventario      │
//╰────────────────────────────────────────────────────────────╯
// Se necesita agregar una variable para saber cuantos objetos se pueden guardar en el jugador
// Comparar con CapacidadItems con nObjetos y si son iguales aumentar


void agregarItem (HashMap *jugadores){
  // Se pide el nombre del jugador 
  char *nombre= malloc(sizeof(char) * MAXCAR ); 
  printf("Ingrese el nombre del jugador : ");
  scanf("%s", nombre) ;

  // Si no existe el mapaHash o nombre no se guardo bien
  if ( nombre == NULL && jugadores == NULL ){
    printf("No existe el jugador \n") ; 
    return;
  }
  
  // Se busca el jugador en el mapa
  Pair *jugador = searchMap(jugadores, nombre); 

  // No existe el jugador
  if(jugador == NULL) {
    printf("No existe el jugador \n");
    return; 
  }
  // Se pide el nombre del item
  char *item = malloc (sizeof( char ) * MAXCAR );
  printf( "Ingrese el nombre del item : " );
  scanf("%s", item);

  // Item igual a NULL
  if(item==NULL){ 
    printf("No existe el item\n");
    return;
  }

/// Agregar función para expandir el inventario ///
  
  // Se agrega el item al inventario
  Data *temp = firstList(jugador->versionesJugador);
  Data *aux = igualarDatas(*temp);

  aux->items[aux->nObjetos] = item;
  aux->nObjetos++;
  pushFront(jugador->versionesJugador, aux);
  printf("Se agrego el item %s al jugador %s\n",item,nombre);
}


/////////////////////////////////////////////////////////////////////////////////////////
/*4. Eliminar item de jugador/a (nombre, item): El/la usuario/a ingresa el nombre de un/a jugador/a y el nombre de un item que desea eliminar. La aplicación elimina el item del inventario de el/la jugador/a. Si el/la jugador/a no existe o el item no está en el inventario, se debe mostrar un aviso.*/

Data* eliminarItem(Data *base, long i){
  Data *temp = igualarDatas(*base);
  for(long aux=i;aux<base->nObjetos-1;aux++){

    temp->items[aux]=temp->items[aux+1];
  }
  temp->items[base->nObjetos-1]=NULL;
  temp->nObjetos--;
  return temp;
}

//busca el item y lo elimina con eliminarItem
void eliminaItemJugador(HashMap *jugadores,char *nombre,char *item){
 
  Pair *jugador=searchMap(jugadores, nombre);
  Data *aux = firstList(jugador->versionesJugador);
  for(long i=0;i<aux->nObjetos;i++)
    {
      if(strcmp(aux->items[i],item)==0){
        pushFront(jugador->versionesJugador, eliminarItem(aux, i));
        aux = firstList(jugador->versionesJugador);
        printf("Item eliminado correctamente\n");
        printf("╭──────────────────────────────────────────────────────────╮\n");
        printf("│                    NUEVO INVENTARIO                      │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        for(long u=0;u<aux->nObjetos;u++){
          printf("│");
          printf("  -  %-*s│\n",53,aux->items[u]);
        }
        printf("╰──────────────────────────────────────────────────────────╯\n");
        return;
      }
    }
  printf("Item no encontrado\n");
  return;


}

void eliminarItemJugadores(HashMap *jugadores){
  //se pide el nombre del jugador
  char *nombre=malloc(sizeof(char)* MAXCAR);
  printf("Ingrese el nombre del jugador :");
  scanf("%s",nombre);
  //se verifica que se introdujo algo
  Pair *jugador=searchMap(jugadores, nombre);
  if(jugador==NULL){
    printf("No existe el jugador\n");
    return;
  }
  Data *aux = firstList(jugador->versionesJugador);
  //objeto a eliminar
  char *item=malloc(sizeof(char)*MAXCAR);
  printf("╭──────────────────────────────────────────────────────────╮\n");
  printf("│                        INVENTARIO                        │\n");
  printf("├──────────────────────────────────────────────────────────┤\n");
  for(long i=0;i<aux->nObjetos;i++){
    printf("│");
    printf("  -  %-*s│\n",53,aux->items[i]);
  }
  printf("╰──────────────────────────────────────────────────────────╯\n");
  printf("Ingrese el objeto a eliminar:");
  scanf("%s",item);
  eliminaItemJugador(jugadores, nombre, item);
  return;
  
  
  
}



/////////////////////////////////////////////////////////////////////////////////////////
/*5. Agregar puntos de habilidad a el/la jugador/a (nombre, puntos): El/la usuario/a ingresa el nombre de un/a jugador/a y la cantidad de puntos de habilidad obtenidos. Los puntos son sumados a la habilidad de el/la jugador/a.*/
void agregarPuntos(HashMap *jugadores) {
  // Se pide el nombre del jugador
  char *nombre = malloc (sizeof(char) * MAXCAR); 
  printf("Ingrese el nombre del jugador : ");
  scanf("%s", nombre) ; 

  // Si no existe el jugador
  if (nombre == NULL && jugadores == NULL ){
    printf("No existe el jugador \n" ) ; 
    return ;
  }

  // Se busca el jugador en el mapa
  Pair *jugador = searchMap(jugadores, nombre);
  if (!jugador || !jugador->key) {
    printf("No existe el jugador \n" ) ;
    return;
  }
  
  // Se piden los puntos a agregar
  long puntos; 
  printf("Ingrese los puntos a asignar : "); 
  scanf("%ld" , &puntos) ; 

  // Se agregan los puntos al jugador
  Data *temp = firstList(jugador->versionesJugador);
  Data *aux = igualarDatas(*temp);
  aux->puntosHabilidad+= puntos; 
  pushFront(jugador->versionesJugador, aux);
  printf("Se agregaron %ld puntos al jugador %s \n", puntos, nombre) ;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*6. Mostrar jugador@s con item específico (item): Se muestran todos los jugadores que tienen el item especificado.*/


//aun no terminadaaa como que tiene un problema con la entrada del item

void mostrarItemJugadores(HashMap *jugadores){


  if(jugadores==NULL)return;
  
  char *item=malloc(sizeof(char) * MAXCAR);
  if (item == NULL) {
    printf("Error al asignar memoria.\n");
    exit(1);
  }
  printf("Ingresa el item que quieres averiguar que jugadores lo tienen: ");
  scanf("%s",item);
  printf("%s",item);


  long mapsize=sizeMap(jugadores);


  char **jugadoresConItem=malloc(sizeof(char*)*mapsize);
  //current vendria siendo el jugador 

  Pair *current=firstMap(jugadores);
  Data *aux = firstList(current->versionesJugador);
  long indice=0;
  long xD=0;
  while(current || current->key){
    Data *aux = firstList(current->versionesJugador);
    for(int i=0;i<aux->nObjetos;i++)
      {
        if(strcmp(item,aux->items[i])==0){

          jugadoresConItem[indice]=current->key;
          printf("%s \n",current->key);
          indice++;
        }
      }
    //se le da el enxt para el proximo jugador
    xD++;
    current=nextMap(jugadores);
  }
  if(indice==0){
    printf("Ningun jugador tiene %s en su inventario\n",item);
    return;
    
  }
  else{
    printf("╭──────────────────────────────────────────────────────────╮\n");
    printf("│Jugadores que tienen %-37s en su inventario:│\n", item);
    printf("├──────────────────────────────────────────────────────────┤\n");
    for(long aux=0;aux<indice;aux++){
      printf("│");
      printf("  -  %-*s│\n",53,jugadoresConItem[aux]);
    }
    printf("╰──────────────────────────────────────────────────────────╯\n");
  }
  

    
  return;
}







/*7. Deshacer última acción de jugador/a (nombre): El/la usuario/a ingresa el nombre de un/a jugador/a y la aplicación deshace la última acción realizada por el/la jugador/a, ya sea agregar/eliminar un item o aumentar los puntos de habilidad. Si no hay acciones que deshacer para el/la jugador/a, se debe mostrar un aviso.*/

void deshacerUltimaAccion(HashMap *jugadores) {
  // Se pide el nombre del jugador
  char *nombre = malloc (sizeof(char) * MAXCAR); 
  printf("Ingrese el nombre del jugador : ");
  scanf("%s", nombre) ; 

  // Si no existe el jugador
  if (nombre == NULL && jugadores == NULL ){
    printf("No existe el jugador \n" ) ; 
    return ;
  }

  // Se busca el jugador en el mapa
  Pair *jugador = searchMap(jugadores, nombre);
  if (!jugador || !jugador->key) {
    printf("No existe el jugador \n" ) ;
    return;
  }
  popFront(jugador->versionesJugador);
}

/*8. Exportar datos de jugadores a archivo de texto (nombre_archivo): La aplicación exporta los datos de todos los/las jugadores/as registrados a un archivo de texto indicado por el/la usuario/a. */

/*9. Cargar datos de jugadores desde un archivo de texto (nombre_archivo): La aplicación carga los datos de los/las jugadores/as registrados desde un archivo de texto indicado por el/la usuario/a. */






////////////////////////////////////////////////////////////////////////////////////

int main(void) {
  
  HashMap *jugadores = NULL;
  
  char continuar = 's';
  char opcion;
  int valido;
  char input[250];
  
  while (continuar == 's' || continuar == 'S') {
    do {
        valido = 1;
        printMenu();
        scanf(" %c", &opcion);

        switch (opcion) {
          case '1':
            jugadores = crearPerfil(jugadores);
            break;
          case '2':
            mostrarPerfil(jugadores);
            break;
          case '3':
            agregarItem(jugadores);
            break;
          case '4' : 
            eliminarItemJugadores(jugadores);
            break; 
          case '5' :
            agregarPuntos(jugadores) ;
            break; 
          case '6' : 
            mostrarItemJugadores(jugadores);
            break; 
          case '7' :
            deshacerUltimaAccion(jugadores); 
            break ; 
//        case 8 : 
//          exportarDatosJugadores(jugadores);
//          break ;
//        case 9 : 
//          cargarDatos(jugadores);
//          break ; 

          case '0':
            printf("¡Hasta luego!\n");
            exit(0);
          
          default:
            printf("Opción inválida. Por favor, ingrese un número válido.\n");
            valido = 0;
        }
    } while (!valido);

    // Este codigo se puede usar para sacar la condicion del primer while
    // printf("\n¿Desea realizar otra acción? (s/n): ");
    // scanf(" %c", &continuar);
  }
  
  return 0;
}



