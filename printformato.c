#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
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

//Al parecer, cuando una cadena que corresponde a la clave del inventario contiene un carácter con acento, la función "strlen" detecta el carácter con acento como si fuera dos caracteres, debido a que es un carácter ancho cuya representación en bits es mayor que la de un solo carácter. Esto causaba problemas al imprimir los marcos en el menú, ya que necesitábamos saber el tamaño exacto de la cadena pero nos daba problemas al detectar caracteres demás debido a los acentos en algunos caracteres. Para solucionar esto, manejamos la situación de la siguiente manera:

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

//esta funcion solo imprime los espacios necesarios
void printEspacios(int cantidad){

  while(cantidad!=0){
    printf(" ");
    cantidad--;
  }
}
