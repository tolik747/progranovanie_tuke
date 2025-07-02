#include "backpack.h"
#include <stdlib.h>
#include<ctype.h>
#include<string.h>

struct backpack* create_backpack(const int capacity)
{
	struct backpack* ku = (struct backpack*)calloc((size_t)capacity, sizeof(struct backpack));
	ku->capacity = capacity;
	
	return ku;
}
struct backpack* destroy_backpack(struct backpack* backpack)
{
	for (int i = 0; i < backpack->size; i++)
	{
		free(backpack[i].items);
	}
	free(backpack);
	return NULL;
}
//
bool add_item_to_backpack(struct backpack* backpack, struct item* item)
{
	if (item == NULL || backpack == NULL || backpack->size >= backpack->capacity) {
        return false;
    }

    struct container* b_item = create_container(NULL, ITEM, item);

    if (b_item == NULL) {
        return false;
    }

    if (backpack->items == NULL) {
        backpack->items = b_item;
    } else {
        struct container* current = backpack->items;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = b_item;
    }

    backpack->size++;

    return true;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item)
{
	 if (backpack == NULL || item == NULL || backpack->items == NULL) {
        return;
    }
    struct container* current = backpack->items;
    struct container* prev = NULL;
    while (current != NULL) {
        if (current->item == item) {
            if (prev == NULL) {
                backpack->items = current->next;
            } else {
                prev->next = current->next;
            }
            free(current); 
            backpack->size--; 
            return;
        }
        prev = current;
        current = current->next;
    }
}

void to_lower(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower(str[i]);
    }
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name)
{
	 if (backpack == NULL||name==NULL) {
        return NULL;
    }

    if (backpack->items == NULL) {
        return NULL;
    }

    char lowercase_name[strlen(name) + 1];
    strcpy(lowercase_name, name);
    to_lower(lowercase_name);

    struct container* current = backpack->items;
    while (current != NULL) {
        struct item* item = current->item;
        char lowercase_item_name[strlen(item->name) + 1];
        strcpy(lowercase_item_name, item->name);
        to_lower(lowercase_item_name);
        if (strcmp(lowercase_item_name, lowercase_name) == 0) {
            return item;
        }
        current = current->next;
    }

    return NULL;
}