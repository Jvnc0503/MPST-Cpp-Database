#ifndef NODE_H
#define NODE_H

#include <unordered_map>
#include <vector>
#include <string>

using std::unordered_map, std::vector, std::string;

// Estructura para representar un nodo en una estructura de datos Trie
struct Node {
	unordered_map<char, Node *> children; // Mapa de hijos: clave es el carácter, valor es el puntero al nodo hijo
	vector<int> movieIds; // Vector de ID de películas asociadas con este nod

	// Destructor que se encarga de liberar la memoria de los nodos hijos
	~Node() {
		for (auto &pair: children) { // Itera sobre cada par clave-valor en el mapa de hijos
			delete pair.second; // Elimina el nodo hijo apuntado por el puntero
		}
	}
};

#endif
