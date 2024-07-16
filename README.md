Proyecto Programacion III: Plataforma de Streaming

Contenido del Proyecto (Archivos):
- "main.cpp"
- "Movie.h"
- "MovieBuilder.h"
- "MovieDatabase.h"
- "Node.h"
- "Trie.h"
- "UserManager.h"


## main.cpp
* Importaciones de Librerías:
	- iostream

* Modulos importados:
	- Movie.h
	- MovieDatabase.h
	- UserManager.h

* No se importo el namespace "Standard" en su totalidad dado a motivos de optimizacion. Por lo que se usaron los siguientes componentes:
	- cout
	- cin
	- max

* Funciones: 
	- void "displayMovieDetails":
		Descripción: La función muestra los detalles de la película seleccionada, imprime los títulos, la sinopsis, y las etiquetas de la película.

	- void "handleMovieSelection":
		Descripción:  La función maneja la selección de una película permitiendo al usuario agregarla a "me gusta" o a "ver más tarde".
		      El bucle se repite hasta que el usuario elige volver al menú anterior.

	
	- void "displayMovies":
		Descripción: La función muestra una lista de películas en grupos de cinco. Permite al usuario seleccionar una película,
		     navegar a la página anterior o siguiente de la lista, o salir de la visualización.
	
	- int "main":
		Descripción: La función principal del programa. Carga la base de datos de películas desde un archivo CSV y presenta un menú interactivo
		     al usuario para buscar y gestionar películas.
		

## Movie.h:
* Importaciones de Librerías:
	- string
	- unordered_set

* No se importo el namespace "Standard" en su totalidad dado a motivos de optimizacion. Por lo que se usaron los siguientes componentes:
	- string
	- unordered_set

* Funciones:
	- int id: Identificador único de la película.

	- string title: Título de la película.

 	- string plot: Sinopsis de la película.
    
  	- unordered_set<string> tags: Conjunto de etiquetas asociadas a la película. 


## MovieBuilder.h:
* Importaciones de Librerías:
	- string
	- unordered_set
	- sstream

* No se importo el namespace "Standard" en su totalidad dado a motivos de optimizacion. Por lo que se usaron los siguientes componentes:
	- string
	- unordered_set
	- istringstream
	- getline
	- stoi

* Funciones:
	- int id: Identificador único de la película en construcción.

	- string title: Título de la película en construcción.

	- string plot: Sinopsis de la película en construcción.

	- unordered_set<string> tags: Conjunto de etiquetas asociadas a la película en construcción.

* Setters:
	- setId: Establece el identificador de la película a partir de un string.

 	- setTitle: Establece el título de la película.

	- setPlot: Establece la sinopsis de la película, eliminando las comillas iniciales y finales si están presentes.

	- setTags: Establece las etiquetas de la película a partir de un string separado por comas.

* Métodos relevantes:
	- build: Construye y retorna un objeto "Movie" con los valores actuales del "MovieBuilder".

	- reset: Reinicia todos los valores del "MovieBuilder" a sus valores por defecto.

	
## MovieDatabase.h:
	- 


## Node.h:
	- 


## Trie.h:
	- 


## UserManager.h:
	- 


Archivo "comma-separated value" (.csv):
El archivo ".csv" inicial fue corregido para una mejor administración de la información, tal como fue indicado en clase.

- https://docs.google.com/spreadsheets/d/1Eyxz5K7UtoBq1ywYVzFCO1lF-NjtSZNPEPTTcI6w_d8/edit?gid=408967157#gid=408967157

Referencias:
- https://en.cppreference.com/w/
- https://stackoverflow.com/
- 
