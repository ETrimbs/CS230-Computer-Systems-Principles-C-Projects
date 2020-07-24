struct Room {
  char* description;
  char* requirement;
  struct Item* items;
  struct Room* north; 
  struct Room* south;
  struct Room* east; 
  struct Room* west;
  struct Room* up; 
  struct Room* down;
};

/*
  construct a room using malloc
  rooms are initialized with a null Item (item(NULL, NULL, NULL);)
*/
struct Room * room(char* description, char* requirement);

//For each room, free its items, the room itself, and nullify the pointer.
void freeRooms(struct Room* rooms[8]);

/*
  print a visual representation of a room. The visual representation uses if statements to print
  doors and stairs corresponding to if a room has (a) neighboring room(s).
  room -> non-null room
*/
void roomToString(struct Room * room);
