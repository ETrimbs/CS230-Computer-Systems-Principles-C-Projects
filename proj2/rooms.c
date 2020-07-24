#include "rooms.h"
#include <stdio.h>
#include <stdlib.h>
#include "items.h"

struct Room * room(char* description, char* requirement){
  struct Room* out = (struct Room*) malloc(sizeof(struct Room));

  out->description = description;
  out->requirement = requirement;
  out->items = item(NULL, NULL, NULL);
  out->north = NULL;
  out->south = NULL;
  out->east = NULL;
  out->west = NULL;
  out->up = NULL;
  out->down = NULL;

  return out;
}

void freeRooms(struct Room* rooms[8]){
  for(int i = 0; i < 8; ++i){
    freeItems(rooms[i]->items);
    free(rooms[i]);
    rooms[i] = NULL;
  }
}

void roomToString(struct Room * room){
  printf("%s\n ...and the room layout is:\n", room->description);

  if(room->north != NULL){
    printf("\n------| |------"); //15 chars
  }else{
    printf("\n---------------");
  }

  for(int i = 0; i < 5; ++i){
    if(room->up != NULL && i == 0){
      printf("\n|  ^          |");
    }
    else if(room->down != NULL && i == 4){
      printf("\n|          v  |");
    }
    else if(room->west != NULL && room->east != NULL && i > 0 && i < 4){
      if(i == 1 || i == 3){
        printf("\n-             -");
      }else if(i==2){
        printf("\n               ");
      }
    }
    else if(room->west != NULL && i > 0 && i < 4){
      if(i == 1 || i == 3){
        printf("\n-             |");
      }else if(i==2){
        printf("\n              |");
      }
    }
    else if(room->east != NULL && i > 0 && i < 4){
      if(i == 1 || i == 3){
        printf("\n|             -");
      }else if(i==2){
        printf("\n|              ");
      }
    }
    else{
      printf("\n|             |");
    }
  }

  if(room->south != NULL){
    printf("\n------| |------");
  }else{
    printf("\n---------------");
  }
}