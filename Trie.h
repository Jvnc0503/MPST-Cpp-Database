#ifndef TRIE_H
#define TRIE_H

#include "Node.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <future>
#include <ranges>
using std::vector, std::istringstream, std::string, std::tolower, std::locale,
std::future, std::async, std::ranges::transform, std::ranges::remove_if, std::ispunct;

class Trie {
    Node* root;

    static vector<string> tokenize(const string& text) {
        vector<string> tokens;
        istringstream stream(text);
        string word;
        while(stream >> word) {
            word.erase(remove_if(word, [](const unsigned char c) {
                return ispunct(c);
            }).begin(), word.end());

            transform(word, word.begin(), [](const unsigned char c) {
                return std::tolower(c);
            });

            tokens.emplace_back(std::move(word));
        }
        return tokens;
    }

public:
    Trie(): root (new Node()) {}
    ~Trie() {
        delete root;
    }

    void insert(const string& id, const string& text) const {
        Node* current = root;
        for (const string& word: tokenize(text)) {
            for (char c: word) {
                if (!current->children.contains(c)) {
                    current->children[c] = new Node();
                }
                current = current->children[c];
                current->movieIds.insert(id);
            }
        }
    }

    [[nodiscard]] unordered_set<string> searchByWord(const string& word) const {
        Node* current = root;
        for (const char& c: word) {
            if (!current->children.contains(c)) {
                return {};
            }
            current = current->children[c];
        }
        return current->movieIds;
    }

    unordered_set<string> searchByText(const string& text) {
        vector<future<unordered_set<string>>> futures;

        for (const string& word: tokenize(text)) {
            futures.emplace_back(async(&Trie::searchByWord, this, word));
        }

        unordered_set<string> result;
        for (auto& future: futures) {
            result.insert(future.get().begin(), future.get().end());
        }

        return result;
    }
};

#endif