#include "includes.h"
#define TOTAL_LIMBS 6

long getFileSize(FILE *fP);
void populateWordArray(char **words, FILE *fP);
void displayWords(char **words, long fileLines);
void displayRandomWord(char **words, long fileLines);
