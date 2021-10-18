# **Proyecto 1 Base de datos II**


<img src="https://upload.wikimedia.org/wikipedia/commons/7/7a/UTEC.jpg" width="200">

## **Integrantes**
* Melendez Cabezas, Jean Paul
* Neira Riveros, Jorge Luis
* Surco Salas, Marcelo Juan

## **Tabla de contenido**
* [Introducción](#introducción)
* [Técnicas a usar en el proyecto](#técnicas-a-usar)
  * [Extendible Hash](#extendible-hash)
  * [Sequential File](#sequential-file)
* [Resultados](#resultados)
  * [Tiempo de ejecución](#tiempo-de-ejecución)
  * [Gráficos de comparación](#gráficos-de-comparación)
  * [Acessos a memoria secundaria](#accesos-a-memoria-secundaria)
  * [Discusión y análisis de resultados experimentales](#discusión-y-análisis-de-resultados-experimentales)
* [Pruebas y video del proyecto](#pruebas)

# **Introducción**

## **Objetivo del proyecto**
El principal objetivo es desarrollar un Sistema Gestor de Bases de Datos (SGBD) con sus principales funciones para el manejo de datos, utilizando técnicas estudiadas en clase y que sean implementadas de tal forma de que el sistema sea eficiente y amigable para usuario.

## **Dominio de los datos**
Los datos a utilizar pertecen al repositorio público de bases de datos https://www.kaggle.com/datasets, del cual se obtuvieron dos bases de datos, uno de pokemones y otro de reviews de ramen. Estas tablas tienen columnas atributos del tipo entero, booleano y string. 

## **Resultados esperados**
Diseñar e implementar un SGDB funcional y que, mediante las técnicas implementadas, sea eficiente, además de poder mostrarlo en una GUI amigable para los usuarios.

# **Técnicas a usar**
- [Extendible Hash](#extendible-hash)
- [Sequential File](#sequential-file)
  
## **Extendible Hash**
<!--- >Explicación de la técnica <--->
La técnica de extendible hash corresponde a una técniga de hashing dinámica, en el que los registros se almacenan dentro de buckets, y estos se almacenan en un archivo de datos. Adicionalemnte, existe un archivo de índices en el que se encontrará, de manera estática, a todos los índices correspondientes con la máxima altura de la estructura, por ejemplo, si la altura máxima es 3 entonces tendremos 2^3 registros. Para gestionar el espacio liberado por la eliminación de registros y buckets, implementaremos la estrategia FreeList en modo LIFO, para lo cual necesitamos guardar un puntero al inicio del archivo de datos. La función hash que utilizaremos será la proporcionada por el STL en la librería functional, además de una operación para extraer los bits necesarios. Para esta técnica, definimos dos parámetros, el factor de bloque, que determina la máxima cantidad de registros por bucket, y la altura máxima de la estructura.

La clase implementada debe leer los índices en su constructor (si el archivo de índices está vacío, inicializarlo de acuerdo a la altura máxima) y almacenar dos mapas, uno donde se guarda la posición del bucket al que apunta, y el otro guarda la cantidad de registros asociados al índice. Inicialmente solo hay 2 buckets, uno para los que terminan en cero y otro para los que terminan en 1, ambos con una altura local de 1. De la misma forma, al destruir la clase, debemos regresar los índices a su archivo, así como el puntero del freeList.

### Manejo de memoria secundaria
<!--- >Manejo de memoria secundaria <--->
En el archivo "index" se encuentran todos los índices de la estructura, el cual contiene 2^D índices, los cuales apuntan a algún bucket en el archivo de datos. En el archivo de datos tenemos a los buckets, los cuales contienen a los registros, cuya cantidad máxima es un parámetro. Cada bucket tiene un ‘d’ (altura) local. El costo de accesos a memoria de las operaciones se define de acuerdo a las lecturas y escrituras de los buckets en el archivo de datos.

<!--- >Funcionamiento de inserción, eliminación y búsqueda <--->
### Inserción
Al insertar un registro, evaluamos el bucket al que deben ir a través de la función hash. Si hay espacio insertamos, de lo contrario, si la altura local es menor a la máxima, entonces hacemos una división del bucket y reacomodamos los registros hasta que el nuevo pueda insertarse. Si ya tiene la máxima altura, entonces creamos linked buckets. La creación de nuevos buckets será en los espacios dejados por los eliminados anteriormente, si es que el puntero de freeList apunta a alguno.

Para la inserción de un vector de registros, aplicamos la función insert a cada uno.

### Búsqueda
Evaluamos la función hash en la key a buscar, y buscamos en el bucket principal (bucket apuntado por algún índice), sino está, buscamos en los buckets linkeados si tiene. De lo contrario, no existe.

Para una búsqueda por rango, debemos buscar en todos los registros. Es la operación más ineficiente.

### Eliminación
Verificamos si existe el registro, y ubicamos el bucket donde se encuentra. Si el bucket tiene links hacia otros, entonces traemos un registro del último bucket linkeado para completarlo. Si se queda vacío evaluamos una eliminación de bucket. Si es uno de los buckets principales (a los que apuntan los índices) evaluamos una fusión de buckets hermanos, dependiendo de la cantidad total de registros entre ambos. En las eliminaciones de buckets, actualizamos el freeList.
 
## **Sequential File**
<!--- >Explicación de la técnica <--->
Esta técnica mantiene a la mayoría de registros ordenados en la región de datos, y utiliza una región auxiliar para insertar registros que no entren en la región de datos. Como es necesario mantener un orden, los registros tienen un parámetro next para apuntar al siguiente y un carácter para indicar la región. Se definen dos parámetros, uno para evaluar el tamaño máximo de la región auxiliar, y otro que evalúa la cantidad máxima de eliminados. Si se alcanza el valor de algún parámetro, es necesario reorganizar el archivo, es decir, llevar a todos los registros de forma ordenada a la región de datos. Esto se realiza con el fin de mantener una consistencia en los datos y en los archivos.

### Manejo de memoria secundaria
<!--- >Manejo de memoria secundaria <--->
El método usa dos archivos, uno para datos, donde están datos ordenados, y otro auxiliar, donde están datos que deberían estar en la otra región, pero no tuvieron espacio de inserción. Cada registro tiene un puntero hacia el siguiente registro, el cual puede estar en el principal o auxiliar. Cuando la cantidad de inserciones en el archivo auxiliar, o eliminaciones en total alcanza un límite, se realiza un refactor para reordenar todos los registros en el archivo principal. Además de la función de refactor, tenemos una función interna que realiza una búsqueda binaria en el archivo de datos, y devuelve una posición. El costo de accesos a memoria de las operaciones se define de acuerdo a las lecturas y escrituras de los regisros tanto en el archivo principal como en el auxiliar.

<!--- >Funcionamiento de inserción, eliminación y búsqueda <--->
### Inserción
Se realiza la búsqueda binaria de la posición donde debe insertarse, y, si tiene espacio, entonces se inserta en el archivo de datos, de lo contrario, se inserta en la región auxiliar y se configuran los punteros. Cuando se alcanza el tamaño máximo de la región auxiliar, se realiza una refactorización para ordenar todos los registros en el archivo principal. 

Para la inserción de un vector de registros, se ordena previamente el vector y luego se llama a la función insert por cada elemento.

### Búsqueda
Se realiza la búsqueda binaria de la posición donde debería estar el registro, y devolver en caso se encuentre ahí. De lo contrario, buscamos linealmente en la zona auxiliar si es que el registro encontrado la apunta. Sino, no se encuentra en la base de datos.

Para la búsqueda por rango, buscamos la primera key, y luego buscamos linealmente hasta llegar a la segunda key.

### Eliminación
Buscamos el registro y configuramos los punteros. Es necesario además, buscar al registro que apunta al registro a eliminar para configurar los punteros. Si se llega a una máxima cantidad de eliminaciones, se reorganizan los archivos.


# **Resultados**
Para la experimentación se tuvo en cuenta los siguiente parámetros
```C++
   //secuencial:
   #define SEQ_MAX_SIZE_OF_AUX_FILE 50
   #define SEQ_MAX_ERASED_RECORDS 100
   
   //hash:
   #define HASH_BUCKET_SIZE 10 //fb
   #define HASH_HEIGHT 10 //D
```

## Tiempo de Ejecución
Tiempo medido en segundos

### Inserción de registros

| Técnica | | | | | |
| :-------------------: | --- | --- | --- | --- | --- |
| | 500 registros | 1000 registros | 1500 registros | 2000 registros | 2500 registros |
| Secuencial | 0,038367 | 0,091864 | 0,125376 |0,167607 | 0,21283 | 
| Extendible Hash | 0,037854 | 0,080746 | 0,130043 | 0,190775 | 0,224702 |

### Búsqueda de un registro

| Técnica | | | | | |
| :-------------------: | --- | --- | --- | --- | --- |
| | 500 registros | 1000 registros | 1500 registros | 2000 registros | 2500 registros |
| Secuencial | 0,000194 | 0,000195 | 0,000203 | 0,000216 | 0,000241 | 
| Extendible Hash | 0,000181 | 0,000182 | 0,000182 | 0,000198 | 0,000209 |

Además, se midieron los tiempos para la búsqueda por rango.

### Búsqueda por rango

| Técnica | | | | | |
| :-------------------: | --- | --- | --- | --- | --- |
| | 500 registros | 1000 registros | 1500 registros | 2000 registros | 2500 registros |
| Secuencial | 0,001013 | 0,00171 | 0,001225 | 0,001679 | 0,001810 | 
| Extendible Hash | 0,002442 | 0,003149 | 0,003955 | 0,005072 | 0,005527 |

## Accesos a memoria secundaria
Para obtener los accesos a memoria secundaria dentro de las funciones especificadas, se contarán los "read" y "write" que haga la función en su tiempo de ejecución.

### Inserción de registros

| Técnica | | | | | |
| :-------------------: | --- | --- | --- | --- | --- |
| | 500 registros | 1000 registros | 1500 registros | 2000 registros | 2500 registros |
| Secuencial | 2491 | 4991 | 7491 | 9991 | 11996 | 
| Extendible Hash | 1184 | 2376 | 4235 | 5735 | 7538 |

### Busqueda de un registro

| Técnica | | | | | |
| :-------------------: | --- | --- | --- | --- | --- |
| | 500 registros | 1000 registros | 1500 registros | 2000 registros | 2500 registros |
| Secuencial | 12 | 13 | 14 | 14 | 14 | 
| Extendible Hash | 1 | 1 | 1 | 1 | 1 |


### Gráficos de comparación

#### Tiempo de ejecución
<img src="/imagenes/insercion_t.JPG" width="600">
<img src="/imagenes/busqueda_t.JPG" width="600">
<img src="/imagenes/busqueda_rt.JPG" width="600">

#### Accesos a memoria secundaria

<img src="/imagenes/accesos_insercion.JPG" width="600">
<img src="/imagenes/acceso_bregistro.JPG" width="600">

## Discusión y análisis de resultados experimentales
Los resultados experimentales muestran que entre ambas técnicas de almacenamiento de datos, existen diferencias, algunas significativas, entre sus tiempos de ejecución y cantidad de accesos a memoria secundaria para una cantidad de registros variable.

En cuanto a la inserción de los registros, el tiempo de ejecución es similar en ambas técnicas. La mayor complejidad en el Extendible Hashing se da en la creación de nuevos buckets para los registros, mientras que, en el Sequential File, se da en la reorganización de archivos cuando la región auxiliar alcanza su máxmimo tamaño. Si realizamos un análisis cuando insertamos un solo registro, la técnica de Extendible Hash tendría un mejor rendimiento que el Sequential File, esto debido a que en el Sequential File, siempre se necesita de una búsqueda binaria para ubicar la posición, además de que, si se inserta en la zona auxiliar y se llena, se requiere de una reorganización total. Mientras que, en el Extendible Hashing, al generarse la llave con la función hash, se guarda en su bucket correspondiente o, en el peor caso, se crea uno nuevo. Por otro lado, la cantidad de accesos a memoria secundaria es significativamente mayor en el Sequential por la búsqueda binaria en el archivo de datos y por la búsqueda lineal en la zona auxiliar, mientras que la otra técnica se dirige a los buckets directamente.

Con respecto a la búsqueda de un registro, la técnica Sequential File tiene un mayor tiempo de ejecución por las búsquedas binaria y lineal que realiza. Además de esto, los accesos a memoria son mucho más bajos (1 en todos los casos) en el Extendible Hashing, ya que la altura máxima permite distribuir eficientemente los registros en los buckets.

Por último, encontramos que las búsquedas por rango, son más eficientes dentro del Sequential File por su misma organización al momento de escribirse en los archivos, ya que al estar ordenado el acceso es directo. Por el contrario, en la otra técnica, se tienen que hacer una búsqueda en todos los buckets ya que no existe una noción de orden.

# **Pruebas**

Las pruebas se realizan en el siguiente video (darle click a la imagen).

[![Pruebas del sistema de almacenamiento](/imagenes/icono.jpeg)](https://www.youtube.com/watch?v=cUdKwrsEEWU)
