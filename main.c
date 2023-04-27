#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "stack.h"
#include "printformato.h"

int MAXCAR = 30;
int CantidadInicialDeJugadores = 100;
int CantidadInicialDeItems     = 10;

typedef struct {
  int ultimaAcc;
  long ptosH;    // Solo cuando agrega PH
  char *objeto;  // Solo en caso de eliminar o agregar
}Acciones;

typedef struct {
  long pH;
  int nObj;
  HashMap *items;
  Stack *versiones;
} Jugador;





/////////////////////////////////////////////////////////////////////////////////////////
/*1. Crear perfil de jugador/a (nombre): El/la usuario/a ingresa un nombre de jugador/a y se crea un perfil en la aplicación. La cantidad de puntos de habilidad se inicializa en 0, y se genera un inventario vacío que almacenará los items que obtenga el/la jugador/a  a lo largo del juego.*/  


void crearPerfil(HashMap *jugadores)
{
  
  
// Agregar función para expandir el HashMap 

  // Se pide el nombre del jugador
  char *nombre = malloc(sizeof(char)*MAXCAR);
  printf("Ingrese el nombre del jugador: ");
  scanf("%[^\n]",nombre);
  getchar();

   
  if(searchMap(jugadores, nombre)){
    printMensajeJugadorRepetido();
    free(nombre);
    return;
  }
  if(nombre) printMensajeGeneroJugadorCorrectamente();

  //Inicia sus datos
  Jugador *datos = (Jugador*) malloc(sizeof(Jugador));
  if (!datos) {
    printf("Error al reservar memoria\n");
    return;
  }
  datos->pH = 0;
  datos->nObj = 0;
  datos->items = createMap(CantidadInicialDeItems);
  datos->versiones = stackCreate();
  Acciones *aux = (Acciones*) malloc(sizeof(Acciones));
  aux->ultimaAcc = 1;
  stackPush(datos->versiones, aux);
  
  // Se inserta el jugador en el mapa
  insertMap(jugadores,nombre, datos);
  

  return;

}


/////////////////////////////////////////////////////////////////////////////////////////
/*2. Mostrar perfil de jugador/a (nombre): El/la usuario/a ingresa el nombre de un/a jugador/a y la aplicación muestra su nombre, cantidad de puntos de habilidad y su inventario de items que ha obtenido hasta el momento.*/

void mostrarDatosJugador(Pair *par) {
    // Se muestran los datos del jugador
    Jugador *aux = par->value;
    printf("\n");
    printf("╭──────────────────────────────────────────────────────────╮\n");
    printf("│                DATOS DEL JUGADOR                         │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Nombre        : %-40s │\n", par->key);
    printf("│ Puntos        : %-40ld │\n", aux->pH);
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│                        INVENTARIO                        │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");

    // Si no hay items en el inventario, se muestra un mensaje
    if (aux->nObj == 0) {
        printf("│  No hay items en el inventario                           │\n");
    } else {
        Pair *temp = firstMap(aux->items);
        // Se muestran los items
        
        while (temp) {
          printf("│");
          printf("  -  %-*s│\n",53,temp->key);
          temp = nextMap(aux->items);
        }
    }
    printf("╰──────────────────────────────────────────────────────────╯\n");
}

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
  scanf("%[^\n]",nombre);
  getchar();

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



void agregarItemDef(Pair *jugador, char *item, HashMap *itemsMap) {
  Jugador *aux = jugador->value;
  insertMap(aux->items,item,NULL);
  aux->nObj++;
  
  //Verifica si el item fue ingresado
  Pair *temp = searchMap(itemsMap,item);
  if (!temp){
    HashMap *loTienen = createMap(10);
    insertMap(loTienen,jugador->key, NULL);
    insertMap(itemsMap,item,loTienen);
  }
  else {
    if (!searchMap(temp->value,jugador->key)) {
        insertMap(temp->value,jugador->key,NULL);
    }
  }

  printf("Se agrego el item %s al jugador %s\n",item,jugador->key);
}


void agregarItemBuscar (HashMap *jugadores, HashMap *itemsMap){
  // Se pide el nombre del jugador 
  char *nombre= malloc(sizeof(char) * MAXCAR ); 
  printf("Ingrese el nombre del jugador : ");
  scanf("%[^\n]",nombre);
  getchar();

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
  scanf("%[^\n]", item);
  getchar();


  // Item igual a NULL
  if(item==NULL){ 
    printf("No existe el item\n");
    return;
  }

/// Agregar función para expandir el inventario ///
  
  // Se agrega el item al inventario
  
  agregarItemDef(jugador, item, itemsMap);
  Jugador *aux = jugador->value;
  Acciones *new = (Acciones*) malloc(sizeof(Acciones));
  new->ultimaAcc = 3;
  new->objeto = item;
  stackPush(aux->versiones,new);
}


/////////////////////////////////////////////////////////////////////////////////////////
/*4. Eliminar item de jugador/a (nombre, item): El/la usuario/a ingresa el nombre de un/a jugador/a y el nombre de un item que desea eliminar. La aplicación elimina el item del inventario de el/la jugador/a. Si el/la jugador/a no existe o el item no está en el inventario, se debe mostrar un aviso.*/


// //busca el item y lo elimina con eliminarItem
int eliminaItemDelJugador(Jugador *jugador,char *item){
  Pair *itemBuscado=searchMap(jugador->items, item);
  if(itemBuscado || itemBuscado->key){
    jugador->nObj--;
    eraseMap(jugador->items, item);
    printf("Item eliminado correctamente\n");
    return 1;
  }
  printf("El item ingresado no existe en el inventario del jugador");
  return 0;

}

void eliminarItemJugadores(HashMap *jugadores){
  //se pide el nombre del jugador
  char *nombre=malloc(sizeof(char)* MAXCAR);
  printf("Ingrese el nombre del jugador :");
  scanf("%[^\n]",nombre);
  getchar();
  //se verifica que se introdujo algo
  Pair *jugadorPair=searchMap(jugadores, nombre);
  if(jugadorPair==NULL){
    printf("No existe el jugador\n");
    return;
  }
  Jugador *jugadorData = jugadorPair->value;
  //objeto a eliminar
  char *item=malloc(sizeof(char)*MAXCAR);
 
  printf("Ingrese el objeto a eliminar:");
  scanf("%[^\n]",item);
  getchar();
  printf("%s",item);
  if(item==NULL){
    return;
  }
  if (eliminaItemDelJugador(jugadorData, item)) {
    Acciones *accionEliminar = malloc(sizeof(Acciones));
    if(accionEliminar==NULL){
      printf("error al asignar memoria");
      exit(1);
    }
    accionEliminar->objeto=item;
    accionEliminar->ultimaAcc=4;
    stackPush(jugadorData->versiones, accionEliminar);
  }
  return;
}

/*

printf("╭──────────────────────────────────────────────────────────╮\n");
   printf("│                        INVENTARIO                        │\n");
   printf("├──────────────────────────────────────────────────────────┤\n");
   for(long i=0;i<jugadorData->nObj;i++){
     printf("│");
     printf("  -  %-*s│\n",53,jugadorData->);
   }
   printf("╰──────────────────────────────────────────────────────────╯\n");
*/


// /////////////////////////////////////////////////////////////////////////////////////////
// /*5. Agregar puntos de habilidad a el/la jugador/a (nombre, puntos): El/la usuario/a ingresa el nombre de un/a jugador/a y la cantidad de puntos de habilidad obtenidos. Los puntos son sumados a la habilidad de el/la jugador/a.*/
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
  Jugador *datos = jugador->value;
  datos->pH += puntos;
  Acciones *new = (Acciones*) malloc(sizeof(Acciones));
  new->ultimaAcc = 5;
  new->ptosH = puntos;
  stackPush(datos->versiones, new);
  printf("Se agregaron %ld puntos al jugador %s \n", puntos, nombre) ;
}



// /////////////////////////////////////////////////////////////////////////////////////////
// /*6. Mostrar jugador@s con item específico (item): Se muestran todos los jugadores que tienen el item especificado.*/

void mostrarItemJugadores(HashMap *jugadores, HashMap *itemsMap){
  char *item=malloc(sizeof(char) * MAXCAR);
  if (item == NULL) {
    printf("Error al asignar memoria.\n");
    exit(1);
  }
  printf("Ingresa un item para averiguar que jugadores lo tienen: ");
  fgets(item, MAXCAR, stdin);
  if (item[strlen(item) -1] == '\n')
  {
    item[strlen(item) - 1] = '\0';
  }

  Pair *aux = searchMap(itemsMap, item);
  if(!aux)
  {
    printf("Ningun jugador tiene %s en su inventario\n",item);
    return;
  }
  HashMap *loTienen = aux->value;
  Pair* jugador = firstMap(loTienen);
  

  int long_dato = strlen(item);
  int espacios = (58 - long_dato) / 2;
  
  printf("╭──────────────────────────────────────────────────────────╮\n");
  printf("│                   Jugadores que tienen                   │\n");
  if (long_dato % 2 == 0)
  {
    printf("│%*s%s%*s│\n", espacios, "", item, espacios, "");
  }
  else
  {
    printf("|%*s%s%*s |\n", espacios, "", item, espacios, "");
  }
  
  printf("|                     en su inventario                     |\n");
  printf("├──────────────────────────────────────────────────────────┤\n");
  
  while (jugador) {
    printf("│");
    printf("  -  %-*s│\n",53,jugador->key);
    jugador = nextMap(loTienen);
  }
  
  printf("╰──────────────────────────────────────────────────────────╯\n");
  return;
}


// /*7. Deshacer última acción de jugador/a (nombre): El/la usuario/a ingresa el nombre de un/a jugador/a y la aplicación deshace la última acción realizada por el/la jugador/a, ya sea agregar/eliminar un item o aumentar los puntos de habilidad. Si no hay acciones que deshacer para el/la jugador/a, se debe mostrar un aviso.*/

void deshacerUltimaAccion(HashMap *jugadores, HashMap *itemsMap) {
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

  Jugador *pj = jugador->value;
  Acciones *ultima = stackTop(pj->versiones);
  switch (ultima->ultimaAcc) {
    case 1:
      printf("Jugador en estado base, no se puede deshacer\n");
      return;
      break;
    case 3:
      eliminaItemDelJugador(pj, ultima->objeto);
      break;
    case 4 : 
      agregarItemDef(jugador, ultima->objeto, itemsMap);
      break; 
    case 5 :
      pj->pH -= ultima->ptosH;
      break; 
    default:
      return;
  }
  stackPop(pj->versiones);
  return;
}

/*8. Exportar datos de jugadores a archivo de texto (nombre_archivo): La aplicación exporta los datos de todos los/las jugadores/as registrados a un archivo de texto indicado por el/la usuario/a. */

void exportarDatos(HashMap *jugadores){
  
  if(jugadores==NULL){
    printf("No hay jugadores para exportar\n");
    return;
  }
  char *nombre = malloc (sizeof(char) * MAXCAR); 
  printf("Ingrese el nombre del archivo : ");
  scanf("%s", nombre) ; 
  
  FILE *archivo = fopen(nombre,"w");
  if (!archivo){
    printf("No se pude abrir el archivo\n");
    return;
  }
  
  Pair *local=firstMap(jugadores);
  if (local == NULL) {
    printf("No hay jugadores para exportar\n");
    fclose(archivo);
    return;
  }
  Jugador *jugador=local->value;
  while(local!=NULL && local->key!=NULL){
    
    fprintf(archivo,"%s,",local->key);
    
    fprintf(archivo,"%lu,",jugador->pH);

    fprintf(archivo,"%i,",jugador->nObj);
    
    Pair *pairItem=firstMap(jugador->items);
    if(jugador->items!=NULL && pairItem!=NULL)
      
      while(pairItem!=NULL && pairItem->key!=NULL){
        fprintf(archivo,"%s",pairItem->key);
        pairItem=nextMap(jugador->items);
        if(pairItem!=NULL){
          fprintf(archivo,",");
        }
      }
    fprintf(archivo,"\n");
    local=nextMap(jugadores);
    if (local != NULL) {
        jugador=local->value;
    }
  }
  fclose(archivo);
  printf("Jugadores exportados correctamente\n");
  
}

/*9. Cargar datos de jugadores desde un archivo de texto (nombre_archivo): La aplicación carga los datos de los/las jugadores/as registrados desde un archivo de texto indicado por el/la usuario/a. */


void maximoCaracteres(FILE *archivo, HashMap *jugadores){

  char car;
  
  
  int saltarlinea=0;
  while(car!=EOF){
    if(saltarlinea==0){
      char *basura=malloc(sizeof(char)*500);
      fscanf(archivo,"%[^\n]",basura);
      fgetc(archivo);
      saltarlinea++;
    }
    else{
      char *nombre=malloc(sizeof(char)*MAXCAR);
      long poder;
      int numero;
      fscanf(archivo,"%[^,]",nombre);
      car=fgetc(archivo);
      Jugador *aux=malloc(sizeof(Jugador)*CantidadInicialDeJugadores);
      fscanf(archivo,"%lu",&poder);
      car=fgetc(archivo);
      fscanf(archivo,"%d",&numero);
      car=fgetc(archivo);
      if(numero==0)
      {
        aux->items=NULL;
      }

      else{

        aux->items=createMap(CantidadInicialDeItems);
        for(int i=0;i<numero;i++){
          char *item=malloc(sizeof(char)*MAXCAR);
          if(i==numero-1)break;
          fscanf(archivo,"%[^,]",item);
          
          car=fgetc(archivo);

          
          insertMap(aux->items, item, NULL);
        }
        char *item=malloc(sizeof(char)*MAXCAR);
        fscanf(archivo,"%[^\n]",item);
        int indice_salto = strcspn(item, "\r\n"); 
        if (indice_salto < strlen(item)) {
          item[indice_salto] = '\0'; 
        }

        car=fgetc(archivo);
        
        insertMap(aux->items, item, NULL);
      }
      aux->nObj=numero;
      aux->pH=poder;
  
      
      insertMap(jugadores, nombre, aux);
    }
    
    
  }
  
}









void importarJugadores(HashMap *jugadores){

  if(jugadores==NULL){
    jugadores = createMap(CantidadInicialDeJugadores);
  }
  char *ruta=malloc(sizeof(char)*MAXCAR);
  printf("ingrese el nombre del archivo a abrir: ");
  scanf("%[^\n]",ruta);
  getchar();

  FILE *archivo = fopen(ruta, "r");
  if(archivo==NULL){
    printf("No se pudo abrir el archivo");
    return;
  }

  maximoCaracteres(archivo,jugadores);
  
  fclose(archivo);
}



////////////////////////////////////////////////////////////////////////////////////

int main(void) {
  
  HashMap *jugadores = createMap(CantidadInicialDeJugadores);
  HashMap *items = createMap(CantidadInicialDeJugadores);
  
  char continuar = 's';
  char opcion;
  int valido;
  char input[250];
  
  while (continuar == 's' || continuar == 'S') {
    do {
        valido = 1;
        printMenu();
        scanf(" %c", &opcion);
        getchar();

        switch (opcion) {
          case '1':
            crearPerfil(jugadores);
            break;
          case '2':
            mostrarPerfil(jugadores);
            break;
          case '3':
            agregarItemBuscar(jugadores, items);
            break;
          case '4' : 
            eliminarItemJugadores(jugadores);
            break; 
          case '5' :
            agregarPuntos(jugadores) ;
            break; 
          case '6' : 
            mostrarItemJugadores(jugadores, items);
            break; 
          case '7' :
            deshacerUltimaAccion(jugadores, items); 
            break ; 
          case '8' : 
            exportarDatos(jugadores);
            break ;
          case '9' : 
            importarJugadores(jugadores);
            break ; 

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