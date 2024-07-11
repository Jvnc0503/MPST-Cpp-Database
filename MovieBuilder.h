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
    MovieBuilder& setTitle(string title) {
        this->title = std::move(title);
        return *this;
    }

    MovieBuilder& setPlot(string plot) {
        if (!plot.empty() && plot.front() == '"' && plot.back() == '"') {
            plot = plot.substr(1, plot.size() - 2);
        }
        this->plot = std::move(plot);
        return *this;
    }

    MovieBuilder& setTags(string tags) {
        istringstream tagStream(std::move(tags));
        string tag;
        while(getline(tagStream, tag, ',')) {
            this->tags.insert(std::move(tags));
        }
        return *this;
    }

    Movie build() {
        return {std::move(title), std::move(plot), std::move(tags)};
    }
};

#endif