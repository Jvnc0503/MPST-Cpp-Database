#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <unordered_set>
using std::string, std::unordered_set;

class Movie {
    int id;
    string title;
    string plot;
    unordered_set<string> tags;
public:
    Movie(): id(0) {};
    Movie(const int id, string title, string plot, unordered_set<string> tags): id(id), title(std::move(title)), plot (std::move(plot)), tags(std::move(tags)) {}
    ~Movie() = default;

    const int& getId() const {
        return this->id;
    }

    const string& getTitle() const {
        return this->title;
    }

    const string& getPlot() const {
        return this->plot;
    }

    const unordered_set<string>& getTags() const {
        return this->tags;
    }
};

#endif