#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <future>
#include "Node.h"

using std::unordered_map, std::vector, std::string, std::tolower, std::isalnum, std::erase_if, std::future,
		std::launch, std::async, std::ranges::transform, std::ranges::sort, std::ranges::unique;

class Trie {
	Node *root;

	// Inserta recursivamente una palabra en el trie, asociándola con un ID de película.
	static void insertAux(Node *node, const string &word, const int movieId, const size_t index) {
		if (index == word.length()) {
			node->movieIds.push_back(movieId); // Asocia el ID al nodo final de la palabra.
			return;
		}
		const char c = word[index];
		if (!node->children[c]) {
			node->children[c] = new Node(); // Crea un nuevo nodo si no existe para el carácter actual.
		}
		insertAux(node->children[c], word, movieId, index + 1); // Continúa con el siguiente carácter.
	}

	// Busca recursivamente las películas asociadas a una palabra, agregando sus ID a 'results'.
	static void searchAux(Node *node, const string &word, vector<int> &results, const size_t index) {
		if (index == word.length()) {
			results.insert(results.end(), node->movieIds.begin(),
						   node->movieIds.end()); // Agrega los ID al finalizar la palabra.
			return;
		}
		const char c = word[index];
		if (node->children.contains(c)) {
			searchAux(node->children[c], word, results, index + 1); // Continúa con el siguiente carácter si existe.
		}
	}

public:
	Trie() : root(new Node()) {}

	~Trie() {
		delete root;
	}

	// Inserta un texto asociado a un ID de película, procesando cada palabra del texto.
	void insert(const int movieId, const string &text) const {
		istringstream iss(text);
		string word;
		while (iss >> word) {
			erase_if(word, [](const char c) { return !isalnum(c); });
			transform(word, word.begin(), [](const unsigned char c) { return tolower(c); });
			if (!word.empty()) {
				insertAux(root, word, movieId, 0);
			}
		}
	}

	// Busca un texto, devolviendo los ID de películas asociadas a las palabras del texto.
	[[nodiscard]] vector<int> search(const string &text) const {
		vector<int> results;
		vector<string> words;
		istringstream iss(text);
		string word;

		while (iss >> word) {
			erase_if(word, [](const char c) { return !isalnum(c); });
			transform(word, word.begin(), [](const unsigned char c) { return tolower(c); });
			if (!word.empty()) {
				words.emplace_back(word);
			}
		}

		vector<future<vector<int>>> futures;
		for (const auto &w: words) {
			futures.push_back(async(launch::async, [this, &w]() {
				vector<int> wordResults;
				searchAux(root, w, wordResults, 0);
				return wordResults;
			}));
		}

		for (auto &f: futures) {
			const auto &res = f.get();
			results.insert(results.end(), res.begin(), res.end());
		}

		sort(results);
		results.erase(unique(results).begin(), results.end());
		return results;
	}
};

#endif
