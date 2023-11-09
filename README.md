# ProyectoFinal_Programacion3
## PARCIAL 2
### INTRODUCCION

**El programa consiste de 7 posibles argumentos.**

- total_art_dif: Muestra la cantidad total de artículos *diferentes*.
- total_art: Muestra la cantidad total de artículos.
- min_stock [n]: Muestra todos los artículos que tengan la cantidad n o menor de stock.
- min_stock [n] [depósito]: Muestra según el depósito, la cantidad de stock que hay en el menor o igual a n.
- stock [nombre_articulo]: Muestra el stock total del artículo ingresado.
- stock [nombre_articulo] [depósito]: Muestra el stock del artículo ingresado según el depósito.
- max_stock [n]: Muestra todos los artículos que tengan una cantidad mayor o igual a n.

### MANUAL DE USO

Primero, se compila el programa con el siguiente comando en consola:

> g++ -o Procesador_inventario.exe main.cpp .\HashMap\HashEntry.h .\HashMap\HashLista.h .\Lista\Lista.h .\Lista\nodo.h .\Cola\Cola.h .\Cola\nodo.h .\Arbol\ArbolBinarioContenedor.h .\Arbol\NodoArbolContenedor.h .\structs.h

Para usar el programa hay que, mediante consola, escribir el archivo .exe del programa (Procesador_invetario.exe) y posteriormente el argumento que querramos.

**Ejemplo**: Si queremos saber la cantidad total de artículos diferentes del negocio, deberemos de introducir lo siguiente en la terminal y posteriormente ejecutarlo.

> Procesador_inventario.exe total_art_dif

Y si queremos saber el mínimo de stock (n) según un depósito, entonces tendremos que introducir lo siguiente:

> Procesador_inventario.exe min_stock 3 5

En este caso estoy pidiendo que me imprima por pantalla la cantidad de stock que sea igual a 3 o menor, en el depósito número 5.

* IMPORTANTE: Para ingresar nombres de artículos se lo tienen que ingresar entre comillas. 

> Procesador_inventario.exe stock "ANAFE VITROCERAMICO VITRO COOK 4" 5

### CONSIDERACIONES

* Se pueden ingresar 2 argumentos o más en una sola ejecución.
* Los argumentos min_stock [n] y max_stock [n] solo se pueden ingresar una vez por ejecución.
* El argumento min_stock [n] [deposito] solo se puede ingresar una vez por depósito.
