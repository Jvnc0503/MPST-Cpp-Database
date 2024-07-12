#ifndef TRIE_H
#define TRIE_H

#include "Node.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <future>
#include <ranges>
using std::vector, std::istringstream, std::string, std::tolower, std::locale, std::future, std::async;

class Trie {
    Node* root = nullptr;

    vector<string> tokenize(const string& text) {
        vector<string> tokens;
        istringstream stream(text);
        string word;
        while(stream >> word) {
            word.erase(std::ranges::remove_if(word, [](const unsigned char c) {
                return std::ispunct(c);
            }).begin(), word.end());

            std::ranges::transform(word, word.begin(), [](const unsigned char c) {
                return std::tolower(c);
            });

            tokens.emplace_back(std::move(word));
        }
        return std::move(tokens);
    }

    void deleteNodes(const Node* node) {
        for(auto& child: node->children) {
            deleteNodes(child.second);
        }
        delete node;
    }

public:
    Trie(): root(new Node('\0')) {}

    void insert(const string& id, const string& text) {
        vector<string> words = tokenize(text);

        for (const string& word: words) {
            Node* current = root;
            for (char c: word) {
                if (!current->children.contains(c)) {
                    current->children[c] = new Node(c);
                }
                current = current->children[c];
                current->movieIds.insert(id);
            }
        }
    }

    unordered_set<string> search(const string& word) {
        Node* current = root;
        for (const char& c: word) {
            if (!current->children.contains(c)) {
                return {};
            }
            current = current->children[c];
        }
        return current->movieIds;
    }

    unordered_set<string> concurrentSearch(const string& text) {
        vector<string> words = tokenize(text);
        vector<future<unordered_set<string>>> futures;

        for (const string& word: words) {
            futures.emplace_back(async(&search, this, word));
        }

        unordered_set<string> result;
        for (auto& future: futures) {
            unordered_set<string> wordResult = future.get();
            result.insert(wordResult.begin(), wordResult.end());
        }

        return result;
    }

    ~Trie() {
        deleteNodes(root);
    }
};

#endif