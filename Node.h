#ifndef NODE_H
#define NODE_H

#include <unordered_map>
#include <vector>
#include <string>
using std::unordered_map, std::vector, std::string;

struct Node {
    unordered_map<char, Node*> children;
    vector<int> movieIds;
    ~Node() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

#endif