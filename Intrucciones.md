Tarea 2 (en equipo)

Objetivos
● Uso de TDAs en el lenguaje de programación C.
● Diseñar y proponer una solución eficiente para el problema planteado.

Actividad
En un videojuego, l@s personajes tienen diferentes habilidades e items que pueden ser obtenidos a lo largo del juego. Se desea implementar un sistema que permita a l@s jugador@s guardar su progreso, incluyendo los items y puntos de habilidad que han obtenido.

Ejemplo de archivo con datos de los jugadores.

Nombre, Puntos de habilidad, #items, Item 1, Item 2, ...
Jugador1,40,4,Espada,Escudo,Poción de vida,Poción de fuerza
Jugador2,25,3,Arco y flechas,Capa de invisibilidad,Poción de velocidad
Jugador3,20,3,Espada,Daga,Armadura de cuero
...

En este archivo, cada línea representa a un/a jugador/a y los campos están separados por comas. El primer campo indica el nombre de el/la jugador/a, el segundo campo indica la cantidad de puntos de habilidad que tiene, el siguiente campo la cantidad de items que tiene y los campos restantes indican los nombres de estos items.

Se propone el siguiente menú para la aplicación:

1. Crear perfil de jugador/a (nombre): El/la usuario/a ingresa un nombre de jugador/a y se crea un perfil en la aplicación. La cantidad de puntos de habilidad se inicializa en 0, y se genera un inventario vacío que almacenará los items que obtenga el/la jugador/a  a lo largo del juego.

2. Mostrar perfil de jugador/a (nombre): El/la usuario/a ingresa el nombre de un/a jugador/a y la aplicación muestra su nombre, cantidad de puntos de habilidad y su inventario de items que ha obtenido hasta el momento.

3. Agregar item a jugador/a (nombre, item): El/la usuario/a ingresa el nombre de un/a jugador/a y el nombre de un item que ha obtenido. La aplicación agrega el item al inventario de el/la jugador/a. Si el/la jugador/a no existe, se debe mostrar un aviso.

4. Eliminar item de jugador/a (nombre, item): El/la usuario/a ingresa el nombre de un/a jugador/a y el nombre de un item que desea eliminar. La aplicación elimina el item del inventario de el/la jugador/a. Si el/la jugador/a no existe o el item no está en el inventario, se debe mostrar un aviso.

5. Agregar puntos de habilidad a el/la jugador/a (nombre, puntos): El/la usuario/a ingresa el nombre de un/a jugador/a y la cantidad de puntos de habilidad obtenidos. Los puntos son sumados a la habilidad de el/la jugador/a.

6. Mostrar jugador@s con item específico (item): Se muestran todos los jugadores que tienen el item especificado.

7. Deshacer última acción de jugador/a (nombre): El/la usuario/a ingresa el nombre de un/a jugador/a y la aplicación deshace la última acción realizada por el/la jugador/a, ya sea agregar/eliminar un item o aumentar los puntos de habilidad. Si no hay acciones que deshacer para el/la jugador/a, se debe mostrar un aviso.

8. Exportar datos de jugadores a archivo de texto (nombre_archivo): La aplicación exporta los datos de todos los/las jugadores/as registrados a un archivo de texto indicado por el/la usuario/a. 

9. Cargar datos de jugadores desde un archivo de texto (nombre_archivo): La aplicación carga los datos de los/las jugadores/as registrados desde un archivo de texto indicado por el/la usuario/a. 

 
Requerimiento no funcional
Además de cumplir con los requerimientos funcionales (opciones del menú), se desea que la solución presentada sea​ eficiente en tiempo (esto se logra con una ​adecuada elección de los TDAs, estructuras de datos ​y una ​correcta implementación​).
 
Revisión de avance
Para la revisión de avance todo el equipo debe estar presente. Luego, se pedirá a un/a integrante al azar que explique el avance. 
Se espera que:
- El/la integrante escogido/a entienda el código
- Se puedan crear jugador@s (1), agregar items (2) y mostrar jugador@s con sus items (3)

Consideraciones
La tarea se puede realizar en equipo.
Copia será calificada con nota 1.0.
Tareas que no compilen serán calificadas con nota 1.0. (Sugerencia: prefiera entregar poco y que funcione bien a mucho y que no funcione.)
Utilicen librerías estándar de C (ver aquí).
La fecha límite de entrega es el 29 de abril, hasta las 23:59 horas.
Deben subir la tarea a un repositorio github público y enviar link a través del aula virtual.
Además deben anexar un archivo README indicando: 
(1) cómo compilar y ejecutar la tarea; 
(2) las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas;
(3) coevaluación del trabajo en equipo (usando rúbrica);
(4) coevaluación del aporte individual de cada integrante (usando rúbrica).
