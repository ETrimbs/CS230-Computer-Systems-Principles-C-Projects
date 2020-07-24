#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>   // open, read

#define MaxWordLength 100
#define MaxWords      1000
#define STDOUT_FILENO 1

//word struct
typedef struct WordFrequency{
  char* str;
  int length;
  int count;
} word;

//returns if c is a letter
_Bool isLetter(char c);

//constructor for words, uses malloc
word* constructWord(char* str, int len);

void freeWords(word* words[MaxWords]);
  
void printWords(word* words[MaxWords]);

int addWord(char wordCon[MaxWordLength], int letters, word* words[MaxWords], int numWords);