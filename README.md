# Dsa-Text-autocorrection
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode* createNode() {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    newNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insertWord(TrieNode* root, const char* word) {
    TrieNode* node = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (node->children[index] == NULL) {
            node->children[index] = createNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

void findSuggestions(TrieNode* root, const char* word, char* path, int depth, int maxDistance) {
    if (root->isEndOfWord && depth <= maxDistance) {
        printf("%s\n", path);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            char c = 'a' + i;
            int newDepth = (word[depth] == c) ? depth : depth + 1;

            if (newDepth <= maxDistance) {
                path[depth] = c;
                findSuggestions(root->children[i], word, path, depth + 1, maxDistance);
                path[depth] = '\0';
            }
        }
    }
}

int main() {
    TrieNode* root = createNode();
    char* dictionary[] = {"apple", "banana", "cherry", "date", "grape", "lemon", "lime", "orange"};
    int numWords = sizeof(dictionary) / sizeof(dictionary[0]);

    // Insert words into the trie
    for (int i = 0; i < numWords; i++) {
        insertWord(root, dictionary[i]);
    }

    char* inputWord = "aple";
    int maxDistance = 2; // Maximum Levenshtein distance for suggestions
    char path[100];

    // Find suggestions for autocorrection
    findSuggestions(root, inputWord, path, 0, maxDistance);

    if (path[0] == '\0') {
        printf("No suggestions found for '%s'.\n", inputWord);
    }

    return 0;
}
