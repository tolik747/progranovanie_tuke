#include "room.h"
#include <stdlib.h>
#include <stdio.h>
#include"container.h"
#include<ctype.h>
#include<string.h>

struct room* create_room(char *name, char *description){
    // if(name==NULL||description==NULL){
    //     return NULL;
    // }
    // struct room* pop=(struct room*)calloc(1,sizeof(struct room));
    // if(pop==NULL){
    //     return NULL;
    // }
    // pop->description=description;
    // pop->name=name;
    // return pop;
    // if(name[0]=='\0'||description[0]=='\0'){
    //     return NULL;
    // }
    if (name == NULL || description == NULL || name[0] == '\0' || description[0] == '\0') {
        return NULL; // Перевіряємо, чи передано обов'язкові параметри
    }

    // Виділення пам'яті для структури кімнати
    struct room* new_room = (struct room*)malloc(sizeof(struct room));
    if (new_room == NULL) {
        return NULL; // Перевіряємо, чи вдалося виділити пам'ять
    }

    // Виділення пам'яті та копіювання назви кімнати
    new_room->name = (char*)malloc(strlen(name) + 1);
    if (new_room->name == NULL) {
        free(new_room); // Звільняємо пам'ять, якщо відбулася помилка
        return NULL;
    }
    strcpy(new_room->name, name);

    // Виділення пам'яті та копіювання опису кімнати
    new_room->description = (char*)malloc(strlen(description) + 1);
    if (new_room->description == NULL) {
        free(new_room->name); // Звільняємо пам'ять, якщо відбулася помилка
        free(new_room);
        return NULL;
    }
    strcpy(new_room->description, description);

    // Ініціалізація вказівників на сусідні кімнати та список предметів
    new_room->north = NULL;
    new_room->south = NULL;
    new_room->east = NULL;
    new_room->west = NULL;
    new_room->items = NULL;

    return new_room;
}
void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){

    if(room==NULL){
        return ;
    }
    if(room){
        room->north=north;
        room->west=west;
        room->south=south;
        room->east=east;
    }
}
void show_room(const struct room* room){
    if(room!=NULL){
        if(room){
           printf("%s\n",room->description);
           printf("Mozne vychody z miesnosti:\n");
           if(room->east!=NULL){
            printf("  east\n");
           }
           if(room->west!=NULL){
            printf("  west\n");
           }
           if(room->north!=NULL){
            printf("  north\n");
           }
           if(room->south!=NULL){
            printf("  south\n");
           }
        }
        printf("Vidíš:\n");
        printf("%s\n",room->name);
    }
}
struct room* destroy_room(struct room* room){
    if(room==NULL){
        return NULL;
    }
    
    free(room->name); 
    free(room->description); 
    free(room); 
    return NULL;
}
void add_item_to_room(struct room* room, struct item* item){
    if (room == NULL || item == NULL) {
        return;
    }
    
    struct container* new_node;
    new_node=create_container(room->items,ITEM,item);
    if(room->items==NULL){
        room->items=new_node;
    }
    // new_node->type = ITEM;
    // new_node->item = item;
    // new_node->next = NULL;

    // if (room->items == NULL) {
    //     room->items = new_node;
    // } else {
    //     struct container* current = room->items;
    //     while (current->next != NULL) {
    //         current = current->next;
    //     }
    //     current->next = new_node;
    // }
}
struct item* get_item_from_room(const struct room* room, const char* name){
    if(room==NULL){
        return NULL;
    }
    if(name==NULL){
        return NULL;
    }
    struct item* predmet=get_from_container_by_name(room->items,name);
    
    return predmet; 
}
void delete_item_from_room(struct room* room, struct item* item){
    if(room){
        if(item){
            struct container *hui=remove_container(room->items,item);
            room->items=hui;
        }
    }
}
