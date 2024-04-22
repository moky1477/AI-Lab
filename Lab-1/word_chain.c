#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

const char* dictionary[] = {"apple", "elephant", "tiger", "rabbit", "giraffe", "eagle"};
const int dictionarySize = sizeof(dictionary) / sizeof(dictionary[0]);

bool isValidWord(const char* word, const char* prevWord, const char** usedWords, int usedWordsCount) {
    if (strlen(word) == 0 || word[0] != prevWord[strlen(prevWord) - 1]) {
        return false;
    }
    
    int i; // Move the variable declaration outside the loop
    for (i = 0; i < usedWordsCount; i++) {
        if (strcmp(word, usedWords[i]) == 0) {
            return false;
        }
    }
    
    return true;
}

const char* makeAIMove(const char* prevWord, const char** usedWords, int usedWordsCount) {
    int validWords[dictionarySize];
    int validWordsCount = 0;
    int i; // Move the variable declaration outside the loop
    
    for (i = 0; i < dictionarySize; i++) {
        if (isValidWord(dictionary[i], prevWord, usedWords, usedWordsCount)) {
            validWords[validWordsCount++] = i;
        }
    }
    
    if (validWordsCount == 0) {
        return "No valid word found";
    }
    
    srand(time(NULL));
    int randomIndex = rand() % validWordsCount;
    return dictionary[validWords[randomIndex]];
}

int main() {
    const char* prevWord = NULL;
    int currentPlayer = 0;
    const char* usedWords[dictionarySize];
    int usedWordsCount = 0;

    while (true) {
        printf("Player %d, enter a word: ", currentPlayer + 1);
        char inputWord[100];
        scanf("%s", inputWord);

        if (!isValidWord(inputWord, prevWord, usedWords, usedWordsCount)) {
            printf("Invalid word! Game over.\n");
            break;
        }

        printf("Valid word: %s\n", inputWord);
        usedWords[usedWordsCount++] = inputWord;
        prevWord = inputWord;
        currentPlayer = (currentPlayer + 1) % 2;

        const char* aiWord = makeAIMove(prevWord, usedWords, usedWordsCount);
        if (!isValidWord(aiWord, prevWord, usedWords, usedWordsCount)) {
            printf("AI cannot continue the word chain! Player %d wins!\n", currentPlayer + 1);
            break;
        }

        printf("AI chooses: %s\n", aiWord);
        usedWords[usedWordsCount++] = aiWord;
        prevWord = aiWord;
        
        if (usedWordsCount == dictionarySize) {
            printf("Game ends in a draw!\n");
            break;
        }
    }

    return 0;
}
