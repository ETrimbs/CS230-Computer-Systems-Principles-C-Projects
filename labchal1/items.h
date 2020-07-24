struct Item {
	char* name;
	char* description;
	struct Item* next;
};

//construct an item node using malloc
struct Item* item(char* name, char* description, struct Item* next);

//getter for name
char* item_name(struct Item* item);

//getter for description
char* item_description(struct Item* item);

//getter for next item
struct Item* item_next(struct Item* item);

//remove and return a pointer to an item in a linked item list
struct Item* item_take(char* name, struct Item* i);

//free memory of items in linked item list
void freeItems(struct Item* item);

//print all items in this linked item list
void printItems(struct Item* head);

//add an item to the end of this item list
void addItem(struct Item* head, struct Item* item);