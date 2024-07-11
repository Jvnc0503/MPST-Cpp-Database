#ifndef TRIE_H
#define TRIE_H

#include "Node.h"
#include <vector>
#include <sstream>
using std::vector, std::istringstream, std::string, std::tolower;

class Trie {
    Node* root = nullptr;

    static vector<string> tokenize(const string& text) {
        vector<string> tokens;
        istringstream stream(text);
        string word;
        while(stream >> word) {
            tokens.emplace_back(std::move(word));
        }
        return std::move(tokens);
    }

    static void deleteNodes(const Node* node) {
        for(auto& child: node->children) {
            deleteNodes(child.second);
        }
        delete node;
    }

public:
    Trie(): root(new Node('\0')) {}

    void insert(const string& id, const string& text) const {
        vector<string> tokens = tokenize(text);

        for (const string& word: tokens) {
            Node* current = root;
            for (char c: word) {
                c = tolower(c, std::locale());
                if (!current->children.contains(c)) {
                    current->children[c] = new Node(c);
                }
                current = current->children[c];
                current->movieIds.emplace(id);
            }
        }
    }

    unordered_set<string>& searchByWord(const string& word) const {
        Node* current = root;
        for (char c: word) {
            c = tolower(c, std::locale());
            if (!current->children.contains(c)) {
                return {};
            }
            current = current->children[c];
        }
        return current->movieIds;
    }

    ~Trie() {
        deleteNodes(root);
    }
};

#endif