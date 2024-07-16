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
		this->id = stoi(i.substr(2));
		return *this;
	}

	MovieBuilder &setTitle(const string &t) {
		this->title = t;
		return *this;
	}

	MovieBuilder &setPlot(const string &p) {
		string processedPlot = p;
		if (!p.empty() && p.front() == '"' && p.back() == '"') {
			processedPlot = p.substr(1, p.size() - 2);
		}
		this->plot = processedPlot;
		return *this;
	}

	MovieBuilder &setTags(const string &ts) {
		istringstream tagStream(ts);
		string tag;
		while (getline(tagStream, tag, ',')) {
			tag.erase(0, tag.find_first_not_of(' '));
			tag.erase(tag.find_last_not_of(' ') + 1);
			this->tags.insert(std::move(tag));
		}
		return *this;
	}

	Movie build() {
		return {id, std::move(title), std::move(plot), std::move(tags)};
	}

	void reset() {
		this->id = 0;
		this->title.clear();
		this->plot.clear();
		this->tags.clear();
	}

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
