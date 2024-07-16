#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H

#include <unordered_map>
#include <string>
#include "Movie.h"
#include "MovieBuilder.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "Trie.h"

using std::unordered_map, std::string, std::vector, std::ifstream, std::istringstream, std::stringstream, std::pair;

class MovieDatabase {
	unordered_map<int, Movie> movies;
	unordered_map<string, unordered_set<int>> tagMap; // Mapea etiquetas a IDs de películas
	Trie trie;

	// Constructor privado para el patrón Singleton
	MovieDatabase() = default;

	// Destructor por defecto
	~MovieDatabase() = default;

	// Parsea una línea del CSV y devuelve sus celdas como vector de strings
	static vector<string> parseRow(const string &line) {
		vector<string> row;
		stringstream ss(line);
		bool insideQuote = false;
		string cell;

		for (const auto &c: line) {
			if (c == '"') {
				insideQuote = !insideQuote;
			} else if (c == ',' && !insideQuote) {
				row.emplace_back(std::move(cell));
				cell.clear();
			} else {
				cell += c;
			}
		}
		row.emplace_back(std::move(cell));

		return row;
	}

public:
	// Obtiene la instancia única de la base de datos
	static MovieDatabase &getInstance() {
		static MovieDatabase instance;
		return instance;
	}

	// Carga películas desde un archivo CSV
	void loadCSV(const string &path) {
		MovieBuilder builder;
		ifstream csv(path);
		string line;

		// Omitir la cabecera
		getline(csv, line);
		line.clear();

		while (getline(csv, line)) {
			vector<string> cells = parseRow(line);

			builder.setId(cells[0])
					.setTitle(cells[1])
					.setPlot(cells[2])
					.setTags(cells[3]);

			trie.insert(builder.getId(), builder.getTitle());
			trie.insert(builder.getId(), builder.getPlot());

			for (const auto &tag: builder.getTags()) {
				tagMap[tag].insert(builder.getId());
			}

			movies.emplace(builder.getId(), std::move(builder.build()));
			builder.reset();
		}
		csv.close();
	}

	// Busca películas por texto
	vector<Movie> searchByText(const string &text) {
		const vector<int> ids = trie.search(text);
		vector<Movie> result;
		for (const int &id: ids) {
			result.emplace_back(movies[id]);
		}
		return result;
	}

	// Busca películas por etiqueta
	vector<Movie> searchByTag(const string &tag) {
		vector<Movie> result;
		if (tagMap.contains(tag)) {
			for (const int &id: tagMap[tag]) {
				result.emplace_back(movies[id]);
			}
		}
		return result;
	}

	// Busca películas por un conjunto de ID
	vector<Movie> searchByIds(const unordered_set<int> &ids) {
		vector<Movie> result;
		for (const int &id: ids) {
			result.emplace_back(movies[id]);
		}
		return result;
	}

	// Obtiene recomendaciones de películas basadas en preferencias de etiquetas
	vector<Movie> getRecommendations(const unordered_map<string, double> &tagPreferences) {
		unordered_map<int, double> movieWeights; // Almacena la ponderación acumulada de cada película

		// Itera sobre cada preferencia de etiqueta proporcionada
		for (const auto &[tag, preference]: tagPreferences) {
			// Si la etiqueta existe en el mapa de etiquetas, procesa cada película asociada
			if (tagMap.contains(tag)) {
				for (const int &id: tagMap[tag]) {
					// Aumenta la ponderación de la película basada en la preferencia del usuario
					// y la cantidad de etiquetas de la película, para normalizar la influencia de cada etiqueta
					movieWeights[id] += preference / movies[id].getTags().size();
				}
			}
		}

		// Convierte el mapa de ponderaciones en un vector para ordenarlo
		vector<pair<int, double>> sortedWeights(movieWeights.begin(), movieWeights.end());

		// Ordena el vector de ponderaciones de mayor a menor
		sort(sortedWeights.begin(), sortedWeights.end(), [](const pair<int, double> &a, const pair<int, double> &b) {
			return a.second > b.second;
		});

		vector<Movie> result; // Almacena el resultado final de las recomendaciones

		// Recorre el vector de ponderaciones ordenado y agrega las películas correspondientes al resultado
		for (const auto &[id, weight]: sortedWeights) {
			result.emplace_back(movies[id]); // Agrega la película por ID al vector de resultados
		}

		return result; // Devuelve el vector de películas recomendadas
	}
};

#endif
