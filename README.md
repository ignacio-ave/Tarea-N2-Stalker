# Tarea-N2-Stalker

# Guía de compilación y ejecución del programa: Tarea 2  STALKER


## Pasos para compilar y ejecutar el programa

Para compilar y ejecutar el programa, sigue estos pasos:

1. Clona el repositorio desde GitHub ejecutando el siguiente comando en tu terminal:
    ```
    git clone https://github.com/ignacio-ave/Tarea-N2-Stalkergit
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

### Crear perfil (nombre)
La función crearPerfil permite crear un perfil de jugador en el programa. Esta función toma como argumento un puntero al HashMap jugadores que almacena los perfiles de los jugadores.

Primero, la función solicita al usuario que ingrese el nombre del jugador. Si el jugador ya existe en el mapa, se muestra un mensaje informando que el jugador ya está registrado y se libera la memoria reservada para el nombre. Si el jugador no existe, se muestra un mensaje de éxito en la creación del perfil.

Luego, se crea un objeto de tipo Jugador y se inicializan sus datos. Se crea un mapa items para almacenar los objetos del jugador y una pila versiones para almacenar las acciones realizadas.

Finalmente, se inserta el perfil del jugador en el mapa de jugadores.

### Herramientas usadas para el desarrollo:
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
| Carlos     | 20           | 20             |  20          | 20               | 20               | 100               |

