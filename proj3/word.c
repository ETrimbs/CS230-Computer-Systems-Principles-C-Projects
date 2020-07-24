#include "word.h"

_Bool isLetter(char c){
  return (c >= 65 && c <= 90 ) || (c >= 97 && c <= 122);
}

word* constructWord(char* str, int len){
  word* out = (word*) malloc(sizeof(word));
  char* copy = (char*) malloc(sizeof(char) * MaxWordLength + 1);
  if(out == NULL || copy == NULL){
    printf("Error allocating memory at constructWord.");
    exit(4);
  }
  copy = strcpy(copy, str);
  out->str = copy;
  out->length = len;
  out->count = 1;
  return out;
}


void freeWords(word* words[MaxWords]){
  for(int i = 0; i < MaxWords && words[i] != NULL; ++i){
    free(words[i]);
    words[i] = NULL;
  }  
}

void printWords(word* words[MaxWords]){
  int j, temp;
  int chars = 0;
  char* outbuf = malloc(sizeof(char) * 20000);
  if(outbuf == NULL){
    printf("Error allocating memory at printWords.");
    exit(11);
  }
  for(int i = 0; i < MaxWords && words[i] != NULL; ++i){
    word* word = words[i];

    if(words[i]->length < 12){
      j = 0;
      while(j < 11){
        if(!isLetter(word->str[j])){
          word->str[j] = ' ';
        }
        ++j;
      }
      word->str[11] = '\0';
    }

    if(word->count < 10){
      if((temp = sprintf(outbuf+chars, "\n%s:  %i", word->str, word->count)) < 0){
        printf("Error using sprintf in printWords.");
        exit(6);
      }        
      chars += temp;
    }
    else if(word->count > 9){
      if((temp = sprintf(outbuf+chars, "\n%s: %i", word->str, word->count)) < 0){
        printf("Error using sprintf in printWords.");
        exit(7);
      }        
      chars += temp;
    } else{
      if((temp = sprintf(outbuf+chars, "\n%s:%i", word->str, word->count)) < 0){
        printf("Error using sprintf in printWords.");
        exit(8);
      }        
      chars += temp;
    }
  }  
  if(write(STDOUT_FILENO, outbuf, sizeof(char) * chars) == -1){
    printf("Error: write fails in printWords.");
    exit(8);
  }
  free(outbuf);
}

//returns 1 if a new word is added, 0 otherwise
int addWord(char wordCon[MaxWordLength], int letters, word* words[MaxWords], int numWords){
  int j = 0;
  //check if it has been encountered before
  while(j < numWords){
   // printf("\nComparing %s to %s", wordCon, words[j]->str);        
    
    if(words[j] != NULL && strcmp(wordCon, words[j]->str) == 0){ //if word has been encountered before, add to count
    //  printf("\nencounters match, %s, %s", wordCon, words[j]->str);
      words[j]->count += 1;
      break;
    }
    ++j;
  }
  if(words[j] == NULL){ //if word has not been encountered before, add it to list
    //  printf("\nAdding word: %s at %i", wordCon, j);
    words[j] = constructWord(wordCon, letters);
    return 1;
  }
  return 0;
}