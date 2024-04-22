#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define NUM_LETTERS 26 // Maximum number of letters supported

char letters[NUM_LETTERS];
int values[NUM_LETTERS];

int num_unique_letters = 0;

bool is_valid_assignment() {
    int unique[10] = {0};

    for (int i = 0; i < num_unique_letters; i++) {
        int value = values[i];

        if (unique[value] == 1) {
            return false; // Non-unique assignment
        }
        unique[value] = 1;
    }

    return true;
}

bool is_solution(char* word1, char* word2, char* result) {
    int val1 = 0, val2 = 0, res = 0;

    // Calculate the values for word1
    for (int i = 0; word1[i]; i++) {
        val1 = val1 * 10 + values[letters[word1[i] - 'A']];
    }

    // Calculate the values for word2
    for (int i = 0; word2[i]; i++) {
        val2 = val2 * 10 + values[letters[word2[i] - 'A']];
    }

    // Calculate the value for the result
    for (int i = 0; result[i]; i++) {
        res = res * 10 + values[letters[result[i] - 'A']];
    }

    return (val1 + val2 == res);
}

bool solve(int letter_index) {
    if (letter_index == num_unique_letters) {
        return is_solution("SEND", "MORE", "MONEY");
    }

    for (int value = 0; value <= 9; value++) {
        values[letter_index] = value;

        if (is_valid_assignment() && solve(letter_index + 1)) {
            return true;
        }

        values[letter_index] = -1; // Backtrack
    }

    return false;
}

int main() {
    char equation[100];
    printf("Enter the cryptoarithmetic equation: ");
    fgets(equation, sizeof(equation), stdin);

    // Initialize values to -1 (unassigned)
    for (int i = 0; i < NUM_LETTERS; i++) {
        letters[i] = -1;
        values[i] = -1;
    }

    // Extract unique letters
    for (int i = 0; equation[i]; i++) {
        if (isalpha(equation[i]) && letters[toupper(equation[i]) - 'A'] == -1) {
            letters[toupper(equation[i]) - 'A'] = num_unique_letters++;
        }
    }

    if (solve(0)) {
        printf("Solution found:\n");
        for (int i = 0; i < num_unique_letters; i++) {
            printf("%c = %d\n", 'A' + i, values[i]);
        }
    } else {
        printf("No solution found.\n");
    }

    return 0;
}
