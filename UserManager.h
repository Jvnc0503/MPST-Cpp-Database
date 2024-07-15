#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <unordered_set>
#include <unordered_map>
#include <string>
#include "Movie.h"
using std::unordered_set, std::unordered_map, std::string;

class UserManager {
    static UserManager* instance;
    unordered_set<int> watchLater;
    unordered_set<int> likes;
    unordered_map<string, int> tagPreferences;

    UserManager() = default;
public:
    static UserManager* getInstance() {
        if (!instance) {
            instance = new UserManager();
        }
        return instance;
    }

    void addToWatchLater(const Movie& movie) {
        watchLater.emplace(movie.getId());
    }

    void addToLikes(const Movie& movie) {
        likes.emplace(movie.getId());
        for (const auto& tag : movie.getTags()) {
            tagPreferences[tag]++;
        }
    }

    const unordered_set<int>& getWatchLater() const {
        return watchLater;
    }

    const unordered_set<int>& getLikes() const {
        return likes;
    }

    const unordered_map<string, int>& getTagPreferences() const {
        return tagPreferences;
    }
};

UserManager* UserManager::instance = nullptr;

#endif