# ProyectoFinal_Programacion3

# PROGRAMACIÓN III
## PARCIAL 2
### Introducción:
Una empresa Argentina realiza diariamente el Inventario Físico de una gran diversidad de productos con
diferentes códigos de QR y en diferentes depósitos. El software de escaneo que se usa en el inventariado físico,
lamentablemente, es muy elemental y arroja una tabla de Excel de infinidad de filas que resultan humanamente
ilegibles y difíciles de procesar para obtener información útil a la empresa:

* Area de Compras: no detecta a tiempo cuales artículos alcanzan el mínimo por el cuál tomar la decisión de
reponerlos.
* El área de ventas, se encuentra con la dificultad de no poder atender rápidamente a los clientes al no saber
la existencia o no de determinado artículo, al momento de consulta de la información.
* El área de Marketing hace lecturas extensas para detectar aquellos artículos de mayor cantidad para el
lanzamiento de promociones de liquidación de stock.
La empresa pone a disposición la tabla de Excel a un grupo de programadores con la finalidad de que le
ayuden a procesar la información de la misma.
Enunciado:
Realizar una aplicación informática que lea un archivo CSV (se comparte Excel también) que brinda la
empresa y por línea de comandos permita la visualización de la siguiente información:
* Cantidad total de artículos diferentes.
* Cantidad total de artículos.
* Listado de artículos que están en el mínimo de stock.
* Listado de artículos que están en el mínimo de stock y por depósito.
* Stock individual de cada artículo.
  Stock individual de cada artículo según depósito.
* Los artículos que igualan o superen determinada cantidad en stock

**Consideraciones del archivo CSV:**
  
* La cantidad de depósitos puede variar.
* La cantidad de artículos diferentes puede variar.
### Manual de Uso:
* **Uso normal:** *
Procesador_inventario.exe [Argumentos] inventariofisico.csv
* **Argumentos posibles:** *
- -total_art_dif Cantidad total de artículos diferentes.
- -total_art Cantidad total de artículos.
2
- -min_stock [n] Listado de artículos con cantidad n o menos de stock.
- -min_stock [n],[deposito] Listado de artículos con cantidad n o menos de stock según un depósito.
- -stock [nombre_articulo] El stock total del artículo ingresado como argumento.
- -stock [nombre_articulo],[depósito] El stock del artículo en un depósito.
- -max_Stock [n] Listado de aquellos artículos cuyo stock es igual o supera el número n.
**Objetivo:** Ejercitar y afianzar el uso de estructuras y algoritmos de datos mediante una aplicación concisa y de uso
general.
Formas de presentación: Exposición y defensa del programa e informe con código fuente y comentarios. Los
integrantes del grupo deben conocer, exponer y defender por igual cualquier parte del
código así como también todas las estructuras y algoritmos desarrollados durante en el
cursado haya o no sido usados en la resolución del problema del presente texto. Forma de
trabajo: Grupos de no más de 4 personas. En la presentación deberán estar todos los
integrantes del grupo (los del mismo país).
Forma de evaluación: Se evaluara de acuerdo a los siguientes parámetros:
* Correcto funcionamiento del programa
* Presentación (interfaz, código, prolijidad)
* Solución óptima al problema dado – eficiencia del código.
* Utilización y adaptación de los códigos proporcionados en clase y del libro.
* Conocimiento de la estructura realizada.
* Exposición y defensa del trabajo.
* Preguntas sobre las estructuras utilizadas a cada integrante.
Cada grupo tendrá 15 minutos para presentar lo desarrollado el día de la entrega.
