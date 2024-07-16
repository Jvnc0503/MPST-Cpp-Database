Proyecto Programacion III: Plataforma de Streaming

Contenido del Proyecto (Archivos):
- "main.cpp"
- "Movie.h"
- "MovieBuilder.h"
- "MovieDatabase.h"
- "Node.h"
- "Trie.h"
- "UserManager.h"


* "Main.cpp":
- Se realizo la importacion de la siguiente(s) librerias:
	- iostream

- Modulos importados:
	- "Movie.h"
	- "MovieDatabase.h"
	- "UserManager.h"

- No se importo la biblioteca "Standard" en su totalidad dado a motivos de optimizacion. Por lo que se usaron los siguientes componentes:
	- "cout"
	- "cin"
	- "max"

- Funciones: 
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
		

* "Movie.h":
	- 


* "MovieBuilder.h":


* "MovieDatabase.h":


* "Node.h":


* "Trie.h":


* "UserManager.h":



Archivo "comma-separated value" (.csv):
El archivo ".csv" inicial fue corregido para una mejor administración de la información, tal como fue indicado en clase.

- https://docs.google.com/spreadsheets/d/1Eyxz5K7UtoBq1ywYVzFCO1lF-NjtSZNPEPTTcI6w_d8/edit?gid=408967157#gid=408967157

Referencias:
- https://en.cppreference.com/w/
- https://stackoverflow.com/
- 
