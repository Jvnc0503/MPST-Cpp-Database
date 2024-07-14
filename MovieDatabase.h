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
using std::unordered_map, std::string, std::vector, std::ifstream, std::istringstream, std::stringstream;

class MovieDatabase {
    unordered_map<string, Movie> movies;
    unordered_map<string, unordered_set<string>> tagMap;
    Trie trie;
    MovieDatabase() = default;

    static vector<string> parseRow(const string& line) {
        vector<string> row;
        stringstream ss(line);
        bool insideQuote = false;
        string cell;

        for(const auto& c : line) {
            if (c == '"') {
                insideQuote = !insideQuote;
            }
            else if (c == ',' && !insideQuote) {
                row.emplace_back(std::move(cell));
                cell.clear();
            }
            else {
                cell += c;
            }
        }
        row.emplace_back(std::move(cell));

        return row;
    }
public:
    static MovieDatabase& getInstance() {
        static MovieDatabase instance;
        return instance;
    }

    void loadCSV(const string& path) {
        MovieBuilder builder;
        ifstream csv(path);
        string line;

        // Skip the header
        getline(csv, line);
        line.clear();

        while(getline(csv, line)) {
            vector<string> cells = parseRow(line);

            builder.setTitle(cells[1])
                .setPlot(cells[2])
                .setTags(cells[3]);

            trie.insert(cells[0], builder.getTitle());
            trie.insert(cells[0], builder.getPlot());

            for (const auto& tag : builder.getTags()) {
                tagMap[tag].insert(cells[0]);
            }

            movies.emplace(cells[0], builder.build());
            builder.reset();
        }
        csv.close();
    }

    vector<Movie> searchByText(const string& text) {
        const unordered_set<string> ids = trie.searchByText(text);
        vector<Movie> result;
        for (const auto& id : ids) {
            result.emplace_back(movies[id]);
        }
        return result;
    }

    vector<Movie> searchByTag(const string& tag) {
        vector<Movie> result;
        for (const auto& id : tagMap[tag]) {
            result.emplace_back(movies[id]);
        }
        return result;
    }
};

#endif