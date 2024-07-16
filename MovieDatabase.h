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
	unordered_map<string, unordered_set<int>> tagMap;
	Trie trie;

	MovieDatabase() = default;

	~MovieDatabase() = default;

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
	static MovieDatabase &getInstance() {
		static MovieDatabase instance;
		return instance;
	}

	void loadCSV(const string &path) {
		MovieBuilder builder;
		ifstream csv(path);
		string line;

		// Skip the header
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

	vector<Movie> searchByText(const string &text) {
		const vector<int> ids = trie.search(text);
		vector<Movie> result;
		for (const int &id: ids) {
			result.emplace_back(movies[id]);
		}
		return result;
	}

	vector<Movie> searchByTag(const string &tag) {
		vector<Movie> result;
		if (tagMap.contains(tag)) {
			for (const int &id: tagMap[tag]) {
				result.emplace_back(movies[id]);
			}
		}
		return result;
	}

	vector<Movie> searchByIds(const unordered_set<int> &ids) {
		vector<Movie> result;
		for (const int &id: ids) {
			result.emplace_back(movies[id]);
		}
		return result;
	}

	vector<Movie> getRecommendations(const unordered_map<string, double> &tagPreferences) {
		unordered_map<int, double> movieWeights;

		for (const auto &[tag, preference]: tagPreferences) {
			for (const int &id: tagMap[tag]) {
				movieWeights[id] += preference / movies[id].getTags().size();
			}
		}

		vector<pair<int, double>> sortedWeights(movieWeights.begin(), movieWeights.end());
		sort(sortedWeights, [](const pair<int, double> &a, const pair<int, double> &b) {
			return a.second > b.second;
		});

		vector<Movie> result;
		for (const auto &[id, weight]: sortedWeights) {
			result.emplace_back(movies[id]);
		}
		return result;
	}
};

#endif
