#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "items.h"
#include "rooms.h"

struct Avatar{
  struct Room* location; 
  struct Item* inventory;
};

struct Avatar* player; //game avatar is referenced often
struct Room* rooms[8]; //keep track of room pointers for comparisons and memory control

//construct an avatar using malloc
struct Avatar* avatar(struct Room* location, struct Item* inventory){
  struct Avatar* out = (struct Avatar*) malloc(sizeof(struct Avatar));
  out->location = location;
  out->inventory = inventory;
}

//create game rooms, connect them, create game items, add them to rooms, create avatar and initial state of game
void initializeGame(){
  
  struct Room * room1 = room("Starting Room", NULL);
  struct Room * room2 = room("Abandoned Barracks", NULL);
  struct Room * room3 = room("Creepy Bedroom", NULL);
  struct Room * room4 = room("An old jail-cell full of rotting bones.", NULL);
  struct Room * room5 = room("An old chapel. There's blood on the altar.", "There is a skeleton, defeat it!");
  struct Room * room6 = room("Hallway", "You are blocked by a zombie!");
  struct Room * room7 = room("Empty Room", "This door is barred shut.");
  struct Room * room8 = room("You've escaped!", "The door is locked!");

  player = avatar(room1, item(NULL, NULL, NULL)); //set player's starting position to starter room and no items

  rooms[0] = room1;
  rooms[1] = room2;
  rooms[2] = room3;
  rooms[3] = room4;
  rooms[4] = room5;
  rooms[5] = room6;
  rooms[6] = room7;
  rooms[7] = room8;

  addItem(room2->items, item("sword", "This is a pretty dope sword.", NULL));
  addItem(room6->items, item("key", "This key would open a door.", NULL));
  addItem(room5->items, item("crowbar", "It'll break shit!", NULL));

  //set room connection pairs;
  room1->north = room2;
  room2->south = room1;

  room2->up = room8;
  room8->down = room2;

  room2->north = room3;
  room3->south = room2;

  room3->north = room4;
  room4->south = room3;

  room4->west = room5;
  room5->east = room4;

  room5->south = room6;
  room6->north = room5;

  room6->south = room7;
  room7->north = room6;

  room7->east = room2;
  room2->west = room7;
}

// free all memory from malloc calls, set some pointers to null
void deinitializeGame(){
  freeItems(player->inventory);
  freeRooms(rooms);
  free(player);
  player = NULL;
}

//show a visual representation of room along with any items in the room and remind the user of his/her inventory
void look(){
  printf("\nYou look around the room...");
  printf("\nThere is an inscription: ");

  struct Room* map = player->location;

  roomToString(map);

  if(map->items->next != NULL && map->items->next->next != NULL){
    printf("\nYou see some items on the floor: ");
    printItems(map->items);
  }
  else if(map->items->next != NULL){
    printf("\nYou see an item on the floor: ");
    printItems(map->items);
  }

  if(player->inventory->next != NULL){
    printf("\nYou have in your inventory: ");
    printItems(player->inventory);
  } else{
    printf("\nYour inventory is empty.");
  }
}

//checks if player is in the final room, marked by "You've escaped!"
_Bool gameIsOver(){
  if(strcmp(player->location->description, "You've escaped!") == 0){
    return 1;
  }
  return 0;
}

//the game loop and end logic
void play(){
  initializeGame(); 
  char i1[15];
  char i2[15];
  struct Room* map;
  printf("\nYou wake up on in a cold, creepy cement basement with no memory. You need to get out and find help now!");

  while(!gameIsOver()){
    printf("\nChoose your action. Type 'help me' for instruction.\n");
    i1[0] = '\0'; //reset input strings
    i2[0] = '\0';
    scanf(" %s %s", &i1, &i2);
    map = player->location; //ease of code reading

    if(strcmp(i1, "help") == 0){
      printf("\nType 'look around' to look around the room. \nType 'go DIRECTION' to attempt to go to another room. \nPossible directions are 'up', 'down', 'north', 'south', 'east', or 'west'. \nType 'take ITEM' to pick up an item. \nType 'use ITEM' to use an item. \nType 'drop ITEM' to drop an item.");
    } 
    else if(strcmp(i1, "look") == 0){
      look();
    }
    else if(strcmp(i1, "go") == 0){
      if(strcmp(i2, "north") == 0){
        if(map->north != NULL){
          if(map->north->requirement == NULL){
            map = map->north;
            printf("\nYou move north...");
          } else{
            printf("\nYou can't: %s", map->north->requirement);
          }
        } else {
          printf("\nYou can't move in that direction.");
        }
      } 
      else if(strcmp(i2, "up") == 0){
        if(map->up != NULL){
          if(map->up->requirement == NULL){
            map = map->up;
            printf("\nYou move up...");
          } else{
            printf("\nYou can't: %s", map->up->requirement);
          }
        } else {
          printf("\nYou can't move in that direction.");
        }
      } 
      else if(strcmp(i2, "down") == 0){
        if(map->down != NULL){
          if(map->down->requirement == NULL){
            map = map->down;
            printf("\nYou move down...");
          } else{
            printf("\nYou can't: %s", map->down->requirement);
          }
        } else {
          printf("\nYou can't move in that direction.");
        }
      } 
      else if(strcmp(i2, "south") == 0){
        if(map->south != NULL){
          if(map->south->requirement == NULL){
            map = map->south;
            printf("\nYou move south...");
          } else{
            printf("\nYou can't: %s", map->south->requirement);
          }
        } else {
          printf("\nYou can't move in that direction.");
        }
      } 
      else if(strcmp(i2, "east") == 0){
        if(map->east != NULL){
          if(map->east->requirement == NULL){
            map = map->east;
            printf("\nYou move east...");
          } else{
            printf("\nYou can't: %s", map->east->requirement);
          }
        } else {
          printf("\nYou can't move in that direction.");
        }
      } 
      else if(strcmp(i2, "west") == 0){
        if(map->west != NULL){
          if(map->west->requirement == NULL ){
            map = map->west;
            printf("\nYou move west...");
          } else{
            printf("\nYou can't: %s", map->west->requirement);
          }
        } else {
          printf("\nYou can't move in that direction.");
        }
      }
    } 
    else if(strcmp(i1, "take") == 0){
      struct Item* take = item_take(i2, map->items);
      if(take == NULL){
        printf("\nNo items match '%s'.", i2);
      } else{
        printf("\nYou have obtained %s: %s.", take->name, take->description);
        addItem(player->inventory, take);
      }
    } 
    else if(strcmp(i1, "use") == 0){
      //logic: check which item is used. check if item is being used in the proper room and if it has not already been used. 
      //If item used effectively, set room ahead's requirement to NULL.
      if(strcmp(i2, "key") == 0){
        if(rooms[7]->requirement != NULL && strcmp(player->location->description, rooms[1]->description) == 0){
          printf("\nYou successfully unlock the exit.");
          rooms[7]->requirement = NULL;
        } else{
          printf("\nThe item does nothing.");
        }
      } 
      else if(strcmp(i2, "sword") == 0){
        if(rooms[4]->requirement != NULL && strcmp(map->description, rooms[3]->description) == 0){
          printf("\nYou successfully kill the skeleton.");
          rooms[4]->requirement = NULL;
        }
        else if(rooms[5]->requirement != NULL && strcmp(map->description, rooms[4]->description) == 0){
          printf("\nYou defeat the zombie.");
          rooms[5]->requirement = NULL;
        } else{
          printf("\nThe item does nothing.");
        }
      }
      else if(strcmp(i2, "crowbar") == 0){
        if(rooms[6]->requirement != NULL && strcmp(map->description, rooms[5]->description) == 0){
          printf("\nYou defeat the door, once and for all.");
          rooms[6]->requirement = NULL;
        } else{
          printf("\nThe item does nothing.");
        }
      } 
      else{
        printf("\nYou don't have a %s.", i2);
      }
    } 
    else if(strcmp(i1, "drop") == 0){ //logic: remove item from inventory, add item to room's items
      struct Item* drop = item_take(i2, player->inventory);
      if(drop == NULL){
        printf("\nYou don't have a %s in your inventory.", i2);
      } else{
        printf("\nYou drop %s.", drop->name);
        addItem(map->items, drop);
      }
    }
    player->location = map; //update player->location
  }

  look();
  printf("\nCongratulations, you have escaped the creepy basement. You immediately call an Uber and get medical attention.\nYou win!");

  deinitializeGame();  
}

//for debugging, print the entire map.
void printMap(){
  struct Room* map = player->location;
  roomToString(map);
  map = map->north;
  roomToString(map);
  map = map->north;
  roomToString(map);
  map = map->north;
  roomToString(map);
  map = map->west;
  roomToString(map);
  map = map->south;
  roomToString(map);
  map = map->south;
  roomToString(map);
  map = map->east;
  roomToString(map);
  map = map->up;
  roomToString(map);
}

int main(){
  // printMap();
  // puts("");
  play();
}