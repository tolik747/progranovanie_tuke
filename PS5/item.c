#include "item.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>


char* strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* copy = malloc(len);
    if (copy != NULL) {
        memcpy(copy, str, len);
    }
    return copy;
}


struct item* create_item(char* name, char* description, unsigned int properties){
	if (name == NULL || description == NULL || name[0] == '\0' || description[0] == '\0') {
        return NULL;
    }
    if (name && description)
	{
		struct item* itemm = (struct item*)calloc(1, sizeof(struct item));
		if(itemm==NULL){
			return NULL;
		}
		itemm->name = strdup(name);
		if (itemm->name == NULL) {
			free(itemm);
			return NULL; 
		}
		itemm->description = strdup(description);
	    if (itemm->description == NULL) {
			free(itemm->name); 
			free(itemm);
			return NULL; 
    	}
		itemm->properties = properties;
		return itemm;
	}
	return NULL;
}
struct item* destroy_item(struct item* item){
	if(item==NULL){
		return NULL;
	}
    if(item!=NULL){
        if(item){
			free(item->name);
			free(item->description);
            free(item);
        }
    }
    return NULL;
}