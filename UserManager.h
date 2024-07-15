#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <unordered_set>
#include <unordered_map>
#include <string>
#include "Movie.h"
using std::unordered_set, std::unordered_map, std::string, std::cout;

class UserManager {
    unordered_set<int> watchLater;
    unordered_set<int> likes;
    unordered_map<string, double> tagPreferences;

    UserManager() = default;
    ~UserManager() = default;
public:
    static UserManager& getInstance() {
        static UserManager instance;
        return instance;
    }

    void addToWatchLater(const Movie& movie) {
        watchLater.emplace(movie.getId());
        std::cout << "Added " << movie.getTitle() << " to watch later\n";
    }

    void addToLikes(const Movie& movie) {
        likes.emplace(movie.getId());
        for (const auto& tag : movie.getTags()) {
            tagPreferences[tag]++;
        }
        std::cout << "Added " << movie.getTitle() << " to likes\n";
    }

    const unordered_set<int>& getWatchLater() const {
        return watchLater;
    }

    const unordered_set<int>& getLikes() const {
        return likes;
    }

    const unordered_map<string, double>& getTagPreferences() const {
        return tagPreferences;
    }
};

#endif