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
    Game currentGame;
    initGame(&currentGame, words, fileLines);

    char attempt = 0;
    system("cls");
    while (currentGame.limbs > 0) {
        // printf("%s (%d)\n", currentGame.word, currentGame.wordSize);
        displayAttempted(&currentGame);
        printf("Limbs remaining: %d\n", currentGame.limbs);
        printLines(&currentGame);
     
        
        scanf(" %c", &attempt);
        clearInputStream();
        submitAttempt(&currentGame, attempt);
        system("cls"); 
    }

    free(words);
    fclose(fP);
    return 0;
}

void clearInputStream() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        continue;
    }
}

void displayAttempted(const Game *g) {
    printf("Attempted Letters: ");
    for (int i = 0; i < g->attemptsN; i++) {
        printf("%c ", g->attempted[i]);
    }
    printf("\n");
}

void submitAttempt(Game *g, char attempt) {
    int alreadyAttempted = 0;
    if (attempt != '\n') {
        for (int i = 0; i < g->attemptsN; i++) {
            if (attempt == g->attempted[i]) {
                alreadyAttempted = 1;
            }
        }

        if (!alreadyAttempted) {
            // If the attempt is correct
            int correctAttempt = 0;
            for (int i = 0; i < g->wordSize; i++) {
                if (g->word[i] == attempt) {
                    correctAttempt = 1;
                }
            }

            g->attemptsN++;

            g->attempted = realloc(g->attempted, g->attemptsN * sizeof(char) + 1);
            g->attempted[g->attemptsN-1] = attempt;
            if (correctAttempt == 0) {
                g->limbs--;
            }
        }
    }
    
}

void printLines(const Game *g) {
    int letterFound;
    for (int i = 0; i < g->wordSize; i++) {
        letterFound = 0;
        for (int j = 0; j < g->attemptsN; j++) {
            if (g->attempted[j] == g->word[i]) {
                letterFound = 1;
            }
        }
        if (letterFound == 0) {
            printf("_");
        } else {
            printf("%c", g->word[i]);
        }


    }
    printf("\n\n");
}

void initGame(Game *g, char **words, long fileLines) {
    strcpy(g->word, getRandomWord(words, fileLines));
    g->hasWon = 0;
    g->wordSize = strlen(g->word);
    g->limbs = TOTAL_LIMBS;
    g->attemptsN = 0;
    g->attempted = (char *)malloc(sizeof(char));
}

void *getRandomWord(char **words, long fileLines) {
    return words[rand() % fileLines];
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
