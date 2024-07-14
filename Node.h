#ifndef NODE_H
#define NODE_H

#include <unordered_map>
#include <unordered_set>
#include <string>
using std::unordered_map, std::unordered_set, std::string;

struct Node {
    unordered_map<char, Node*> children;
    unordered_set<int> movieIds;

    Node() = default;
    ~Node() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

#endif