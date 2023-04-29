#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
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

//para poder imprimir el formato de salida de forma correcta debido a los acentos
int printInventario(char *palabra){
  
    setlocale(LC_ALL, ""); 
    mbstate_t state = {0};
    const char *s = palabra;
    size_t len = strlen(palabra);
    wchar_t wc;
    int tiene_acento = 0;
    
    while (s < palabra + len) {
        size_t n = mbrtowc(&wc, s, len - (s - palabra), &state);
        if (n == (size_t) -2 || n == (size_t) -1) {
            break;
        }
        s += n;

        if (iswalpha(wc) && wc > 127) {
            tiene_acento++;
            
        }
    }
    len-=tiene_acento;
    return len;
}

void printEspacios(int cantidad){

  while(cantidad!=0){
    printf(" ");
    cantidad--;
  }
}




/*1*/  


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



/*2*/

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
          //printf("  -  %-*s│\n",53,temp->key);
          printf("  -  ");
          printf("%s",temp->key);
          int cantidadSpace=53-printInventario(temp->key);
          printEspacios(cantidadSpace);
          //printInventario(temp->key, 55);
          printf("│\n");
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

/*3*/

void agregarItemDef(char *nombre, Jugador *datos, char *item, HashMap *itemsMap) {
  insertMap(datos->items,item,NULL);
  datos->nObj++;
  
  //Verifica si el item fue ingresado
  Pair *temp = searchMap(itemsMap,item);
  if (!temp){
    HashMap *loTienen = createMap(10);
    insertMap(loTienen,nombre, NULL);
    insertMap(itemsMap,item,loTienen);
  }
  else {
    if (!searchMap(temp->value,nombre)) {
        insertMap(temp->value,nombre,NULL);
    }
  }
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

  
  // Se agrega el item al inventario y se agrega al historial
  
  agregarItemDef(jugador->key, jugador->value, item, itemsMap);
  printf("Se agrego el item %s al jugador %s\n",item,jugador->key);
  Jugador *aux = jugador->value;
  Acciones *new = (Acciones*) malloc(sizeof(Acciones));
  new->ultimaAcc = 3;
  new->objeto = item;
  stackPush(aux->versiones,new);
}


/*4*/


// //busca el item y lo elimina con eliminarItem
int eliminaItemDelJugador(char *nombre, Jugador *jugador,char *item, HashMap *itemsMap){
  Pair *itemBuscado=searchMap(jugador->items, item);
  if(itemBuscado || itemBuscado->key){
    jugador->nObj--;
    eraseMap(jugador->items, item);
    Pair *parItem = searchMap(itemsMap, item);
    HashMap *loTienen = parItem->value;
    eraseMap(loTienen, nombre);
    if (!firstMap(loTienen)) {
      eraseMap(itemsMap, item);
    }
    printf("Item eliminado correctamente\n");
    return 1;
  }
  printf("El item ingresado no existe en el inventario del jugador");
  return 0;

}

void eliminarItemJugadores(HashMap *jugadores, HashMap *itemsMap){
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
  if (eliminaItemDelJugador(jugadorPair->key, jugadorData, item, itemsMap)) {
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




/*5.*/
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



/*6*/

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
  /*if (long_dato % 2 == 0)
  {
    printf("│%*s%s%*s│\n", espacios, "", item, espacios, "");
  }
  else
  {
    printf("|%*s%s%*s |\n", espacios, "", item, espacios, "");
  }*/
  int espaciositemmedio=(58-printInventario(item))/2;
  if(espaciositemmedio%2==0){
    
    printf("│");
    printEspacios(espaciositemmedio);
    printf("%s",item);
    printEspacios(espaciositemmedio);
    printf("│");
    printf("\n");
  }
  else{
    printf("│");
    printEspacios(espaciositemmedio);
    printf("%s",item);
    printEspacios(espaciositemmedio);
    printf(" │");
    printf("\n");
  }
  
  
  printf("│                     en su inventario                     │\n");
  printf("├──────────────────────────────────────────────────────────┤\n");
  
  while (jugador) {
    printf("│");
    printf("  -  %-*s│\n",53,jugador->key);
    jugador = nextMap(loTienen);
  }
  
  printf("╰──────────────────────────────────────────────────────────╯\n");
  return;
}


/*7*/

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
      eliminaItemDelJugador(jugador->key, pj, ultima->objeto, itemsMap);
      break;
    case 4 : 
      agregarItemDef(jugador->key, jugador->value, ultima->objeto, itemsMap);
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

/*8 */

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
  fprintf(archivo, "Nombre,Puntos de habilidad,#items,Item 1,Item 2,Item 3,Item 4,Item 5,Item 6,Item 7,Item 8\n");
  
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

/*9. */


void maximoCaracteres(FILE *archivo, HashMap *jugadores, HashMap *itemsMap){

  char car;
  
  int Jugadoress=0;
  int saltarlinea=0;
  while(car!=EOF){
    if(saltarlinea==0){
      char *basura=malloc(sizeof(char)*500);
      fscanf(archivo,"%[^\n]",basura);
      fgetc(archivo);
      saltarlinea++;
    }
    else{
      Jugadoress++;
      char *nombre=malloc(sizeof(char)*MAXCAR);
      long poder;
      int numero;
      fscanf(archivo,"%[^,]",nombre);
      car=fgetc(archivo);
      if(nombre[0]=='\0'){
        break;
      }
      Jugador *aux=malloc(sizeof(Jugador)*CantidadInicialDeJugadores);
      fscanf(archivo,"%lu",&poder);
      car=fgetc(archivo);
      fscanf(archivo,"%d",&numero);
      car=fgetc(archivo);
      if(numero==0)
      {
        aux->items=createMap(CantidadInicialDeItems);
      }

      else{
        
        aux->items=createMap(CantidadInicialDeItems);
        for(int i=0;i<numero;i++){
          char *item=malloc(sizeof(char)*MAXCAR);
          if(i==numero-1)break;
          fscanf(archivo,"%[^,]",item);
          agregarItemDef(nombre, aux, item, itemsMap);
          car=fgetc(archivo);
        }
        
        char *item=malloc(sizeof(char)*MAXCAR);
        fscanf(archivo,"%[^\n]",item);
        agregarItemDef(nombre, aux, item, itemsMap);
        int indice_salto = strcspn(item, "\r\n"); 
        if (indice_salto < strlen(item)) {
          item[indice_salto] = '\0'; 
        }
        car=fgetc(archivo);
      }
      
      aux->nObj=numero;
      aux->pH=poder;
      aux->versiones = stackCreate();
      Acciones *inicio = (Acciones*) malloc(sizeof(Acciones));
      inicio->ultimaAcc = 1;
      stackPush(aux->versiones, inicio);
      insertMap(jugadores, nombre, aux);
    }
  }
}









void importarJugadores(HashMap *jugadores, HashMap *itemsMap){

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

  maximoCaracteres(archivo,jugadores, itemsMap);
  
  fclose(archivo);
  printf("Se han importado %lu jugadores de manera exitosa\n", sizeMap(jugadores));
  // Considero que no es necesario ponerlo, solo era para hacer test aa si era para probar
  // printf("La cantidad de jugadores actual es de %lu\n", sizeMap(jugadores));
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
            eliminarItemJugadores(jugadores, items);
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
            importarJugadores(jugadores, items);
            break ; 

          case '0':
            printf("¡Hasta luego!\n");
            exit(0);
          
          default:
            printf("Opción inválida. Por favor, ingrese un número válido.\n");
            valido = 0;
        }
    } while (!valido);


  }
  
  return 0;
}

    // Este codigo se puede usar para sacar la condicion del primer while
    // printf("\n¿Desea realizar otra acción? (s/n): ");
    // scanf(" %c", &continuar);