#include<stdio.h>
#include"container.h"
#include<stdlib.h>
#include <string.h>
#include<ctype.h>


struct container* create_container(struct container* first, enum container_type type, void* entry) {
    if (entry == NULL) {
        return NULL;
    }
    struct container* contain = (struct container*)calloc(1,sizeof(struct container)); 
    if (contain == NULL) {
        return NULL;
    }
    contain->type = type;
    
    switch (type) {
        case ROOM:
            contain->room = (struct room*)entry;
            break;
        case ITEM:
            contain->item = (struct item*)entry;
            break;
        case COMMAND:
            contain->command = (struct command*)entry;
            break;
        case TEXT:
            contain->text = (char*)entry;
            break;
        default:
            free(contain);
            return NULL;
    }
       
    contain->next=NULL;

    if(first==NULL){
        return contain;
    }
    if(first->type!=type){
        free(contain);
        return NULL;
    }
    struct container* con = first;
    while (con->next != NULL) {
        con = con->next;
    }
    con->next = contain;
    return contain;

}
//
struct container* destroy_containers(struct container* first)
{
if(first == NULL){
        return NULL;
    }
    struct container* current = first;
    struct container* next;

    while (current != NULL)
    {
        next = current->next;

        switch (current->type)
        {
            case ROOM:
                destroy_room(current->room);
                break;
            case ITEM:
                destroy_item(current->item);
                break;
            case COMMAND:
                destroy_command(current->command);
                break;
            case TEXT:
                free(current->text);
                break;
            default:
                break;
        }
        
        free(current); 
        current = next;
    }

    return NULL;
}
//
int sravnenie(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    while (*s1 != '\0' && *s2 != '\0') {
        if (tolower(*s1) != tolower(*s2)) {
            return 0;
        }
        s1++;
        s2++;
    }

    return (*s1 == '\0' && *s2 == '\0');
}
void* get_from_container_by_name(struct container *first, const char *name){

    if (name == NULL || first == NULL) {
        return NULL;
    }

    struct container *temp = first;

    while (temp != NULL) {
        if (temp->type == ROOM) {
            if (sravnenie(temp->room->name, name)) {
                return temp->room;
            }
        } else if (temp->type == ITEM) {
            if (sravnenie(temp->item->name, name)) {
                return temp->item;
            }
        } else if (temp->type == COMMAND) {
            if (sravnenie(temp->command->name, name)) {
                return temp->command;
            }
        } else if (temp->type == TEXT) {
            if (sravnenie(temp->text, name)) {
                return temp->text;
            }
        }
        temp = temp->next;
    }

    return NULL;
}
//
struct container* remove_container(struct container *first, void *entry){
    if (first == NULL) {
        return NULL;
    }

    struct container *prev = NULL;

    switch(first->room == entry || first->item == entry || first->text == entry || first->command == entry){
        case true:
            {
                struct container *temp = first;
                first = first->next;
                free(temp);
                return first; 
            }
        default:
            break;
    }

    for(struct container *current = first; current != NULL; current = current->next) {
        switch(current->room == entry || current->item == entry || current->text == entry || current->command == entry){
            case true:
                prev->next = current->next;
                free(current);
                return first; 
            default:
                break;
        }
        prev = current;
    }

    return first;
}
