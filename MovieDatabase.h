#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H

#include <unordered_map>
#include <string>
#include "Movie.h"
#include "MovieBuilder.h"
#include <vector>
#include <fstream>
#include <sstream>
using std::unordered_map, std::string, std::vector, std::ifstream, std::istringstream, std::stringstream;

class MovieDatabase {
    unordered_map<string, Movie> movies;
    MovieDatabase() = default;
public:
    static MovieDatabase& getInstance() {
        static MovieDatabase instance;
        return instance;
    }

    vector<string> parseRow(const string& line) {
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

        return std::move(row);
    }

    void loadCSV(const string& path) {
        MovieBuilder builder;
        string id, title, plot, tags;
        ifstream csv(path);
        string line;

        getline(csv, line);
        vector<string> headers = parseRow(line);

        while(getline(csv, line)) {
            vector<string> cells = parseRow(line);

            id = cells[0];
            title = cells[1];
            plot = cells[2];
            tags = cells[3];

            builder.setTitle(std::move(title))
                .setPlot(std::move(plot))
                .setTags(std::move(tags));

            movies.emplace(std::move(id), builder.build());
        }
    }
};

#endif