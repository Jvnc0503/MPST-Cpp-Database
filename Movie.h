#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <unordered_set>
using std::string, std::unordered_set;

class Movie {
    string title;
    string plot;
    unordered_set<string> tags;
public:
    Movie(string title, string plot, unordered_set<string> tags): title(std::move(title)), plot (std::move(plot)), tags(std::move(tags)) {}

    string getTitle() const {
        return this->title;
    }

    string getPlot() const {
        return this->plot;
    }

    unordered_set<string> getTags() const {
        return this->tags;
    }
};

#endif