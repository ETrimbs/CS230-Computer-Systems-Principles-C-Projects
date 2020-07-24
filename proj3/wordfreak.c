#include "wordfreak.h"

void countWordsFD(int fd){
  word* words[MaxWords]; //store words
  char wordCon[MaxWordLength] = "\0"; //construct a word. +1 for terminal null char
  char buf[1000] = "\0"; //read buffer
  int numWords = 0; //number of unique words
  int letters = 0; //length of word being built
  int r = 1; //stores read() return val
  
  //read file into array
  while(r != 0){
    if((r = read(fd, buf, BufSize)) > 0){
      buf[1] = '\0';
      if(isLetter(buf[0])){ // check if we
        strcat(&wordCon[0], &buf[0]);
        ++letters;
        wordCon[letters-1] = buf[0]; //increment terminal char
        wordCon[letters] = '\0'; //increment terminal char
      }
      else{
        if(wordCon[0] != '\0'){ //A word has been read in
          numWords += addWord(wordCon, letters, words, numWords);
          //prepare to read in a new word
          wordCon[0] = '\0';
          letters = 0;
        }
      }
    }
    else if(r == -1){ //read error
      printf("Error on read at countWordsFD.");
      exit(2);
    }
  }

  printWords(words);
  printf("\n");
  freeWords(words); //free blocks from malloc
}

void countWordsPointer(char* filePointer){
  int fd = open(filePointer, O_RDONLY); //fd = file descriptor
  if(fd == -1){
    printf("Error on open at countWordsPointer.");
    exit(1);
  }
  countWordsFD(fd);
  if(close(fd) == -1){
    printf("Error on close at countWordsPointer.");
    exit(3);
  }
}


void wordFreak(int arg, char** argv){
   char* ge; //store getenv call

  if(arg > 1){ //read from argv
    printf("\nRead argv:\n");

    for(int i = 1; i < arg; ++i){
      countWordsPointer(argv[i]);
    }
  }
  else if((ge = getenv(Env)) != NULL){ //read env if it is not null
    printf("\nRead env:\n");
    countWordsPointer(ge);
  }
  else{  
    printf("\nread stdin:\n");
    countWordsFD(STDIN_FILENO); //STDIN_FILENO is an open file descriptor
  }
}