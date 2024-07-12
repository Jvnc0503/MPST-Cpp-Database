#ifndef MOVIEBUILDER_H
#define MOVIEBUILDER_H

#include <string>
#include <unordered_set>
#include <sstream>
#include "Movie.h"
using std::string, std::unordered_set, std::istringstream, std::getline;

class MovieBuilder {
    string title;
    string plot;
    unordered_set<string> tags;
public:
    MovieBuilder& setTitle(string t) {
        this->title = std::move(t);
        return *this;
    }

    MovieBuilder& setPlot(string p) {
        if (!p.empty() && p.front() == '"' && p.back() == '"') {
            p = p.substr(1, p.size() - 2);
        }
        this->plot = std::move(p);
        return *this;
    }

    MovieBuilder& setTags(string t) {
        istringstream tagStream(std::move(t));
        string tag;
        while(getline(tagStream, tag, ',')) {
            this->tags.insert(std::move(t));
        }
        return *this;
    }

    Movie build() {
        return {std::move(title), std::move(plot), std::move(tags)};
    }
};

#endif