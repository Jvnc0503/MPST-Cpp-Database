#ifndef NODE_H
#define NODE_H

#include <unordered_map>
#include <unordered_set>
#include <string>
using std::unordered_map, std::unordered_set, std::string;

struct Node {
    char letter;
    unordered_map<char, Node*> children;
    unordered_set<string> movieIds;

    explicit Node(const char letter): letter(letter) {}
    ~Node() {
        for (auto& child : children) {
            delete child.second;
        }
    }
};

#endif