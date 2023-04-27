#include <stdio.h>
#include "hashmap.h"
#include "printformato.h"
#include "stack.h"

void printMenu() {
    printf("\n");
    printf("╭──────────────────────────────────────────────────────────╮\n");
    printf("│                     MENU PRINCIPAL                       │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ 1. Crear perfil de jugador/a                             │\n");
    printf("│ 2. Mostrar perfil de jugador/a                           │\n");
    printf("│ 3. Agregar item a jugador/a                              │\n");
    printf("│ 4. Eliminar item de jugador/a                            │\n");
    printf("│ 5. Agregar puntos de habilidad a el/la jugador/a         │\n");
    printf("│ 6. Mostrar jugador@s con item específico                 │\n");
    printf("│ 7. Deshacer última acción de jugador/a                   │\n");
    printf("│ 8. Exportar datos de jugadores a archivo de texto        │\n");
    printf("│ 9. Cargar datos de jugadores desde un archivo de texto   │\n");
    printf("│ 0. Salir                                                 │\n");
    printf("╰──────────────────────────────────────────────────────────╯\n");
    printf("\nIngrese el número de la opción deseada: ");
}

void printMensajeGeneroJugadorCorrectamente() {
    printf("\n╔══════════════════════════════════════╗\n");
    printf(  "║ ¡Se generó el jugador correctamente! ║\n");
    printf(  "╚══════════════════════════════════════╝\n\n");
}



/*
Funcion antigua:
void mostrarSoloInventario(Pair *par){
  
  // Si no hay items en el inventario, se muestra un mensaje
  if(par->nObjetos==0){
    printf("No hay items en el inventario\n");
    return;
  }
  char **items=par->items;
  
  // Se muestran los items
  for(int i=0;i<par->nObjetos;i++){
    printf("%s ",items[i]);
  }
  printf("\n");*/



void printMensajeJugadorRepetido(){
  printf("Este nombre de usuario ya existe\n");
}