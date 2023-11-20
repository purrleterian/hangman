#include "main.h"

#include "includes.h"

// Making Hangman
// Steps:
// - Make a function that allocates memory for an array of nouns (2D array of
// Chars)
// - Store that array in heap
// - Randomly select a word from that array
// - Create a loop that checks if the user has won the game. If they do, break
// out of the loop
// - While in the loop:
//     - Print underscores equal to the length of the word
//     - Prompt the user for a letter
//     - Check if that letter is part of the array of chars of the chosen word
//     - If the letter is present in the word:
//         - Replace the corresponding underscores with the instances of that
//         letter
//         - Resume the loop
//     - If the letter is NOT present in the word:
//         - Subtract from the limbs(?) count
//
//     - If all letters are found:
//         - Won = True
//         - Break out of the loop
//
//     - If the limbs variable reaches zero:
//         - Break out of the loop
int limbs = TOTAL_LIMBS;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    rand();

    char filename[] = "./data/nounlist.txt";
    FILE *fP = fopen(filename, "r");
    if (fP == NULL) {
        printf("Failed to open text file [%s]\n", filename);
        exit(1);
    }

    // words is a pointer to pointers
    char **words;
    long fileLines = getFileSize(fP);

    // Alocate a string of character pointers the size of however many lines of
    // words in the file
    words = malloc(fileLines * sizeof(char *));
    size_t tempSize = 32;
    for (int i = 0; i < fileLines; i++) {
        // For every one of the pointers, allocate a certain size for the word
        words[i] = malloc(tempSize * sizeof(char));
    }

    if (!words) {
        printf("Error allocating memory");
        exit(1);
    }

    populateWordArray(words, fP);
    // displayWords(words, fileLines);
    while (1) {
        displayRandomWord(words, fileLines);
        getchar();
    }

    free(words);
    fclose(fP);
    return 0;
}

void displayRandomWord(char **words, long fileLines) {
    char *word = words[rand() % fileLines];
    int wordSize = strlen(word);
    printf("%s (%d)", word, wordSize);
}

void displayWords(char **words, long fileLines) {
    for (int i = 0; i < fileLines; i++) {
        printf("[%d] %s\n", i + 1, words[i]);
    }
}

void populateWordArray(char **words, FILE *fP) {
    long i = 0;
    char buffer[32];

    // fgets returns null on the last line, so 'i' will end up the same as
    // fileLines
    while (fgets(buffer, sizeof(buffer), fP)) {
        // Create a new pointer with the precise size

        // Remove the last character of each word (\n) to clean up the data
        int wordSize = strlen(buffer);
        buffer[wordSize - 1] = '\0';

        strcpy(words[i], buffer);
        i++;
    }
    rewind(fP);
}

long getFileSize(FILE *fP) {
    int c;
    unsigned long lines = 0;
    while ((c = getc(fP)) != EOF) {
        if (c == '\n') {
            lines++;
        }
    }

    rewind(fP);
    return lines;
}
