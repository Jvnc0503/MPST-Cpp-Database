#ifndef MOVIEBUILDER_H
#define MOVIEBUILDER_H

#include <string>
#include <unordered_set>
#include <sstream>
#include "Movie.h"

using std::string, std::unordered_set, std::istringstream, std::getline, std::stoi;

class MovieBuilder {
	int id;
	string title;
	string plot;
	unordered_set<string> tags;
public:
	MovieBuilder() : id(0) {}

	MovieBuilder &setId(const string &i) {
		this->id = stoi(i.substr(2)); // Convierte el ID de string a int y lo asigna
		return *this; // Permite encadenamiento de métodos
	}

	MovieBuilder &setTitle(const string &t) {
		this->title = t;
		return *this; // Permite encadenamiento de métodos
	}

	MovieBuilder &setPlot(const string &p) {
		string processedPlot = p;
		// Elimina comillas al principio y al final, si las hay
		if (!p.empty() && p.front() == '"' && p.back() == '"') {
			processedPlot = p.substr(1, p.size() - 2);
		}
		this->plot = processedPlot;
		return *this; // Permite encadenamiento de métodos
	}

	MovieBuilder &setTags(const string &ts) {
		istringstream tagStream(ts);
		string tag;
		while (getline(tagStream, tag, ',')) {
			// Elimina espacios al principio y al final de cada etiqueta
			tag.erase(0, tag.find_first_not_of(' '));
			tag.erase(tag.find_last_not_of(' ') + 1);
			this->tags.insert(std::move(tag)); // Inserta la etiqueta en el conjunto
		}
		return *this; // Permite encadenamiento de métodos
	}

	// Construye y devuelve una instancia de Movie
	Movie build() {
		return {id, std::move(title), std::move(plot), std::move(tags)};
	}

	// Reinicia el constructor para poder empezar de nuevo
	void reset() {
		this->id = 0;
		this->title.clear();
		this->plot.clear();
		this->tags.clear();
	}

	// Métodos getters para cada atributo
	const int &getId() const {
		return this->id;
	}

	const string &getTitle() const {
		return this->title;
	}

	const string &getPlot() const {
		return this->plot;
	}

	const unordered_set<string> &getTags() const {
		return this->tags;
	}
};

#endif
