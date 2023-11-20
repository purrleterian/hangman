#include "includes.h"
#define TOTAL_LIMBS 6

typedef struct {
    int hasWon;
    int wordSize;
    char word[];
} Game;

long getFileSize(FILE *fP);
void populateWordArray(char **words, FILE *fP);
void displayWords(char **words, long fileLines);
void displayRandomWord(char **words, long fileLines);
void *getRandomWord(char **words, long fileLines);
void initGame(Game *g, char **words, long fileLines);
void printLines(const Game *g);