# Tarea-N2-Stalker

# Guía de compilación y ejecución del programa: Tarea 2  STALKER


## Pasos para compilar y ejecutar el programa

Para compilar y ejecutar el programa, sigue estos pasos:

1. Clona el repositorio desde GitHub ejecutando el siguiente comando en tu terminal:
    ```
    git clone https://github.com/ignacio-ave/Tarea-N2-Stalker.git
    ```
    
2. Abre una terminal en el directorio en el que se encuentran los archivos `main.c` y los archivos que componene el programa:
    - hashmap.c: Implementación de la tabla hash.
    - hashmap.h: Encabezado para la tabla hash.
    - list.c: Implementación de la lista enlazada.
    - list.h: Encabezado para la lista enlazada.
    - main.c: Código principal del programa.
    - Makefile: Archivo Makefile para compilar y enlazar el proyecto.
    - printformato.c: Funciones de formato para la salida impresa.
    - printformato.h: Encabezado para las funciones de formato.
    - README.md: Documentación del proyecto.
    - stack.h: Encabezado para la estructura de datos de pila

3. Escribe el comando `make -s` para compilar el programa:
    ```
    make -s
    ```
    
4. Escribe el comando `./main` para ejecutar el programa:
    ```
    ./main.c
    ```

## Opciones que funcionan:
1.  Crear perfil (nombre)
2.  Mostrar perfil (nombre)
3.  Agregar item (nombre, item)
4.  Eliminar item (nombre, item)
5.  Agregar puntos de habilidad (nombre, puntos)
6.  Mostrar jugador@s con item (item)
7.  Deshacer última acción (nombre)
8.  Importar/exportar datos a archivo CVS.

### 1.  Crear perfil (nombre)
La función crearPerfil permite crear un perfil de jugador en el programa. Esta función toma como argumento un puntero al HashMap jugadores que almacena los perfiles de los jugadores.

Primero, la función solicita al usuario que ingrese el nombre del jugador. Si el jugador ya existe en el mapa, se muestra un mensaje informando que el jugador ya está registrado y se libera la memoria reservada para el nombre. Si el jugador no existe, se muestra un mensaje de éxito en la creación del perfil.

Luego, se crea un objeto de tipo Jugador y se inicializan sus datos. Se crea un mapa items para almacenar los objetos del jugador y una pila versiones para almacenar las acciones realizadas.

Finalmente, se inserta el perfil del jugador en el mapa de jugadores.


### 2.  Mostrar perfil (nombre)
La función mostrarDatosJugador se encarga de mostrar la información detallada del perfil de un jugador, incluyendo su nombre, puntos de habilidad e inventario. Si no hay objetos en el inventario, se muestra un mensaje indicando que está vacío.

La función mostrarPerfil se encarga de buscar el perfil de un jugador en el sistema utilizando su nombre. Primero, verifica si hay jugadores registrados en el sistema. Si no hay jugadores registrados, muestra un mensaje indicando esto. Si hay jugadores, pide al usuario que ingrese el nombre del jugador que desea buscar y luego busca el perfil de ese jugador en el mapa de jugadores. Si el jugador no existe, muestra un mensaje indicándolo. Si el jugador existe, muestra los datos del perfil utilizando la función mostrarDatosJugador.


### 3.  Agregar item (nombre, item)
La función agregarItemDef se encarga de agregar un ítem al inventario del jugador y actualizar el mapa de ítems con la información de qué jugadores tienen cada ítem.

La función agregarItemBuscar pide al usuario el nombre del jugador y del ítem a agregar, busca al jugador en el mapa de jugadores y, si existe, agrega el ítem al inventario del jugador llamando a agregarItemDef. También guarda esta acción en el historial del jugador.


### 4.  Eliminar item (nombre, item)
La función eliminarItemJugadores se encarga de eliminar un ítem del inventario de un jugador y actualizar el mapa de ítems con la información de qué jugadores tienen cada ítem.

Primero, la función pide al usuario que ingrese el nombre del jugador. Luego, busca al jugador en el mapa de jugadores utilizando el nombre ingresado. Si el jugador no existe, muestra un mensaje indicando esto y retorna. Si el jugador existe, pide al usuario que ingrese el nombre del ítem a eliminar.

Posteriormente, la función eliminaItemDelJugador se encarga de buscar el ítem en el inventario del jugador y, si lo encuentra, lo elimina del inventario y actualiza el mapa de ítems correspondiente. Si el ítem no existe en el inventario del jugador, muestra un mensaje indicándolo.

Si se logra eliminar el ítem, se guarda esta acción en el historial del jugador utilizando la estructura Acciones y la pila versiones del jugador.


### 5.  Agregar puntos de habilidad (nombre, puntos)
La función agregarPuntos se encarga de agregar puntos de habilidad a un jugador específico. Para ello, toma como argumento un puntero al HashMap jugadores que almacena los perfiles de los jugadores.

La función solicita al usuario que ingrese el nombre del jugador al que se le agregarán los puntos de habilidad.
Verifica si el nombre ingresado existe en el mapa de jugadores. Si el jugador no existe, se muestra un mensaje indicándolo y la función retorna.
Si el jugador existe, la función solicita al usuario que ingrese la cantidad de puntos de habilidad que se agregarán al jugador.
Luego, se accede a los datos del jugador y se le suman los puntos de habilidad ingresados por el usuario.
Se crea un objeto de tipo Acciones para almacenar la información de esta acción (agregar puntos de habilidad) y se guarda en la pila versiones del jugador.
Finalmente, se muestra un mensaje informando que se agregaron los puntos de habilidad al jugador.


### 6.  Mostrar jugador@s con item (item)
La función mostrarItemJugadores se encarga de mostrar la lista de jugadores que tienen un ítem específico en su inventario. Para ello, toma como argumentos punteros a los HashMap jugadores y itemsMap que almacenan los perfiles de los jugadores y la información de los ítems, respectivamente.

La función solicita al usuario que ingrese el nombre del ítem del cual se desea conocer los jugadores que lo tienen.
Busca en el mapa de ítems itemsMap el ítem ingresado por el usuario. Si no encuentra el ítem, muestra un mensaje indicando que ningún jugador tiene dicho ítem y retorna.
Si el ítem existe, se obtiene el mapa loTienen que contiene la información de los jugadores que tienen el ítem.
Se imprime un encabezado con el nombre del ítem en el centro y se itera sobre el mapa loTienen para mostrar los nombres de los jugadores que poseen dicho ítem en su inventario.
Finalmente, se muestra un mensaje indicando el fin de la lista de jugadores con el ítem especificado.

    
### 7.  Deshacer última acción (nombre)
La función deshacerUltimaAccion permite deshacer la última acción realizada en el perfil de un jugador. Esta función toma como argumentos punteros a los HashMap jugadores e itemsMap, que almacenan los perfiles de los jugadores y los objetos disponibles en el juego.

Primero, la función solicita al usuario que ingrese el nombre del jugador. Si el jugador no existe, se muestra un mensaje informando que el jugador no existe y se retorna.

Luego, se busca el jugador en el mapa de jugadores y se obtiene un puntero a su estructura Jugador. Se obtiene la última acción realizada por el jugador desde la pila de versiones.

A continuación, se evalúa el tipo de acción realizada para determinar cómo deshacerla. Si la última acción fue agregar un objeto al jugador, se elimina el objeto del jugador. Si la última acción fue eliminar un objeto del jugador, se agrega nuevamente el objeto al jugador. Si la última acción fue agregar puntos de habilidad, se restan los puntos de habilidad añadidos previamente. Si la última acción fue una acción base (estado inicial), se muestra un mensaje informando que no se puede deshacer.

Finalmente, se elimina la última acción de la pila de versiones del jugador.

### 8.  Importar/exportar datos a archivo CVS.
Estas funciones permiten importar y exportar datos de jugadores a un archivo en formato CSV.

__Exportar datos (HashMap *jugadores)__

La función exportarDatos toma como argumento un puntero al HashMap jugadores que almacena los perfiles de los jugadores. Primero, verifica si hay jugadores para exportar y solicita al usuario que ingrese el nombre del archivo donde se guardarán los datos.

Luego, crea un archivo con el nombre especificado y escribe en él la cabecera del archivo CSV con los nombres de las columnas. A continuación, recorre el mapa de jugadores y escribe los datos de cada jugador en una nueva línea del archivo CSV. Los datos incluyen el nombre del jugador, los puntos de habilidad, la cantidad de objetos y los nombres de los objetos.

Finalmente, se cierra el archivo y se muestra un mensaje informando que los jugadores se exportaron correctamente.

__Importar jugadores (HashMap *jugadores, HashMap *itemsMap)__

La función importarJugadores permite importar perfiles de jugadores desde un archivo CSV. Toma como argumentos punteros a los HashMap jugadores e itemsMap, que almacenan los perfiles de los jugadores y los objetos disponibles en el juego.

Primero, solicita al usuario que ingrese el nombre del archivo a abrir. Luego, abre el archivo en modo lectura y verifica si se pudo abrir correctamente.

A continuación, llama a la función maximoCaracteres que lee los datos del archivo CSV y crea perfiles de jugadores con la información leída, insertándolos en el mapa de jugadores. Además, asigna los objetos correspondientes a cada jugador según los datos del archivo.

Finalmente, se cierra el archivo y se muestra un mensaje informando la cantidad de jugadores importados exitosamente.

## Herramientas usadas para el desarrollo:
  - replit (Para desarrollar el programa en conjunto)
  - Visual Studio Code (Para desarrollar el programa individualmente)
  - Github (Para guardar un backup del programa)
  - GPT (Para redactar parcialmente el archivo readme y archivos printformato)

## Coevaluación equipo
- Participación activa y equitativa: 20 
- Resolución de conflictos: 20
- Colaboración: 20 
- Responsabilidad: 20 
- Comunicación: 15
- Puntaje total: 95

## Coevaluación del aporte individual
| Integrante | Participación | Responsabilidad | Comunicación | Calidad del trabajo | Trabajo en equipo | Pje Total |
|------------|--------------|----------------|--------------|------------------|------------------|------------------|
| Ignacio    | 20           | 15             |  20          | 20               | 20               | 95               |
| Vicente    | 20           | 20             |  15          | 20               | 20               | 95               |
| Antonia    | 20           | 20             |  15          | 20               | 20               | 95               |
| Carlos     | 20           | 20             |  20          | 20               | 20               | 100              |

