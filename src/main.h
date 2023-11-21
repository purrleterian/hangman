#include "includes.h"
#define TOTAL_LIMBS 6

typedef struct {
    int hasWon;
    int wordSize;
    int limbs;
    int lettersFound;

    int attemptsN;
    char *attempted;
    char word[];
} Game;

long getFileSize(FILE *fP);
void populateWordArray(char **words, FILE *fP);
char *getRandomWord(char **words, long fileLines);
void initGame(Game *g, char **words, long fileLines);
void printLines(const Game *g);
void submitAttempt(Game *g, char attempt);
void displayAttempted(const Game *g);
