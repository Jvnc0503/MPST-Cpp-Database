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

    static void insertAux(Node* node, const string& word, const int movieId, const size_t index) {
        if (index == word.length()) {
            node->movieIds.push_back(movieId);
            return;
        }

        const char c = word[index];
        if (!node->children[c]) {
            node->children[c] = new Node();
        }
        insertAux(node->children[c], word, movieId, index + 1);
    }

    static void searchAux(Node* node, const string& word, vector<int>& results, const size_t index) {
        if (index == word.length()) {
            results.insert(results.end(), node->movieIds.begin(), node->movieIds.end());
            return;
        }

        const char c = word[index];
        if (node->children.contains(c)) {
            searchAux(node->children[c], word, results, index + 1);
        }
    }

public:
    Trie() : root(new Node()) {}

    ~Trie() {
        delete root;
    }

    void insert(const int movieId, const string& text) const {
        istringstream iss(text);
        string word;
        while (iss >> word) {
            erase_if(word, [](const char c) { return !isalnum(c); });
            std::ranges::transform(word, word.begin(),
                                   [](const unsigned char c){ return tolower(c); });
            if (!word.empty()) {
                insertAux(root, word, movieId, 0);
            }
        }
    }

    vector<int> search(const std::string& text) const {
        vector<int> results;
        istringstream iss(text);
        string word;
        while (iss >> word) {
            erase_if(word, [](const char c) { return !isalnum(c); });
            std::ranges::transform(word, word.begin(),
                                   [](const unsigned char c){ return tolower(c); });
            if (!word.empty()) {
                searchAux(root, word, results, 0);
            }
        }
        std::ranges::sort(results);
        results.erase(std::ranges::unique(results).begin(), results.end());
        return results;
    }
};

#endif