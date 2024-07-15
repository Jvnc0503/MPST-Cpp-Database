#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "Node.h"
using std::unordered_map, std::vector, std::string, std::tolower, std::locale, std::isalnum, std::erase_if;

class Trie {
    Node* root;

    void insert(Node* node, const string& word, const int movieId, const size_t index) {
        if (index == word.length()) {
            node->movieIds.push_back(movieId);
            return;
        }

        const char c = tolower(word[index], locale());
        if (!node->children[c]) {
            node->children[c] = new Node();
        }
        insert(node->children[c], word, movieId, index + 1);
    }

    void search(Node* node, const string& word, vector<int>& results, const size_t index) const {
        if (index == word.length()) {
            results.insert(results.end(), node->movieIds.begin(), node->movieIds.end());
            return;
        }

        const char c = tolower(word[index], locale());
        if (node->children.contains(c)) {
            search(node->children[c], word, results, index + 1);
        }
    }

public:
    Trie() : root(new Node()) {}

    ~Trie() {
        delete root;
    }

    void insert(const int movieId, const string& text) {
        istringstream iss(text);
        string word;
        while (iss >> word) {
            erase_if(word, [](char c) { return !isalnum(c); });
            std::ranges::transform(word, word.begin(),
                                   [](unsigned char c){ return tolower(c); });
            if (!word.empty()) {
                insert(root, word, movieId, 0);
            }
        }
    }

    vector<int> search(const std::string& text) const {
        vector<int> results;
        istringstream iss(text);
        string word;
        while (iss >> word) {
            std::erase_if(word, [](char c) { return !isalnum(c); });
            std::ranges::transform(word, word.begin(),
                                   [](unsigned char c){ return tolower(c); });
            if (!word.empty()) {
                search(root, word, results, 0);
            }
        }
        std::ranges::sort(results);
        results.erase(std::ranges::unique(results).begin(), results.end());
        return results;
    }
};

#endif