#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20

// Structure to represent a dictionary word
struct DictionaryWord {
    char word[MAX_WORD_LENGTH];
};

// Function to load words into the dictionary
void loadDictionary(struct DictionaryWord *dictionary, int *wordCount) {
    // In a real application, you would load words from a file or a database
    // For simplicity, we'll hardcode some words here.
    strcpy(dictionary[0].word, "hello");
    strcpy(dictionary[1].word, "world");
    strcpy(dictionary[2].word, "programming");
    
    *wordCount = 3;
}

// Function to check if a word is in the dictionary
int isWordInDictionary(const char *word, struct DictionaryWord *dictionary, int wordCount) {
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(word, dictionary[i].word) == 0) {
            return 1; // Word is in the dictionary
        }
    }
    return 0; // Word is not in the dictionary
}

// Function to suggest corrections for a given word
void suggestCorrections(const char *input, struct DictionaryWord *dictionary, int wordCount) {
    printf("Did you mean:\n");

    for (int i = 0; i < wordCount; i++) {
        if (strncmp(input, dictionary[i].word, strlen(input)) == 0) {
            printf("- %s\n", dictionary[i].word);
        }
    }
}

int main() {
    struct DictionaryWord dictionary[MAX_WORDS];
    int wordCount = 0;

    loadDictionary(dictionary, &wordCount);

    char userInput[MAX_WORD_LENGTH];
    printf("Enter a word: ");
    scanf("%s", userInput);

    if (isWordInDictionary(userInput, dictionary, wordCount)) {
        printf("Your input is correct!\n");
    } else {
        printf("Your input is incorrect!\n");
        suggestCorrections(userInput, dictionary, wordCount);
    }

    return 0;
}
