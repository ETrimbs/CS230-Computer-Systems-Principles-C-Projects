#include "items.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct Item* item(char* name, char* description, struct Item* next) {
	struct Item* i = (struct Item *) malloc(sizeof(struct Item));
	i->name = name;
	i->description = description;
	i->next = next;
	return i;
}

char* item_name(struct Item* item) {
	return item->name;
}

char* item_description(struct Item* item) {
	return item->description;
}

struct Item* item_next(struct Item* item) {
	return item->next;
}

struct Item* item_take(char* name, struct Item* head) {
	struct Item* curr = head;

	while (item_next(curr) != NULL) {
		if (strcmp(item_name(item_next(curr)), name) == 0) {
      struct Item* out = item_next(curr);
			curr->next = item_next(item_next(curr));
      out->next = NULL;
			return out;
		}
    curr = item_next(curr);
	}
	return NULL;
}

void freeItems(struct Item* curr){
  if(curr == NULL){
    return;
  }
  struct Item* next = curr->next;
  free(curr);
  freeItems(next);
}

void printItems(struct Item* head){
  if(head->next != NULL){
    printf("\n%s: %s", head->next->name, head->next->description);
    printItems(head->next);
  }
}

void addItem(struct Item* head, struct Item* item){
  struct Item* curr = head;
  while(curr->next != NULL){
    curr = curr->next;
  }
  curr->next = item;
}