#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"world.h"

struct container* create_world(){
    
    // struct room* room1 = create_room("komnata1", "dush");
    // struct room* room2 = create_room("komnata2", "kychnia");
    // struct room* room3 = create_room("komnata3", "nico");
    // struct room* room4 = create_room("komnata4", "neviem co tu");
    // struct room* room5 = create_room("komnata5", "a tu viem");

    // if (!room1 || !room2 || !room3 || !room4 || !room5) {
    //     if (room1) destroy_room(room1);
    //     if (room2) destroy_room(room2);
    //     if (room3) destroy_room(room3);
    //     if (room4) destroy_room(room4);
    //     if (room5) destroy_room(room5);
    //     return NULL;
    // }
    // if(room1==NULL||room2==NULL||room3==NULL||room4==NULL||room5==NULL){
    //     if (room1) destroy_room(room1);
    //     if (room2) destroy_room(room2);
    //     if (room3) destroy_room(room3);
    //     if (room4) destroy_room(room4);
    //     if (room5) destroy_room(room5);
    //     return NULL;
    // }

    // struct container* world = create_container(NULL, ROOM, room1);
    // struct container * vew0 = add_room_to_world(world, room1);
    // struct container * vew = add_room_to_world(world, room2);
    // struct container * vew1 = add_room_to_world(world, room3);
    // struct container * vew2 = add_room_to_world(world, room4);
    // struct container * vew3 = add_room_to_world(world, room5);
    // set_exits_from_room(room1, room2, room3, room4, room5);
    // if (!vew0||!vew || !vew1 || !vew2 || !vew3) {
    //     destroy_containers(world);
    //     return NULL;
    // }
    
    // world->type = ROOM;
    
    // return world;
     struct room* room1 = create_room("komnata1", "dush");
    if (!room1) {
        return NULL;
    }
    
    struct room* room2 = create_room("komnata2", "kychnia");
    if (!room2) {
        destroy_room(room1);
        return NULL;
    }
    
    struct room* room3 = create_room("komnata3", "nico");
    if (!room3) {
        destroy_room(room1);
        destroy_room(room2);
        return NULL;
    }
    
    struct room* room4 = create_room("komnata4", "neviem co tu");
    if (!room4) {
        destroy_room(room1);
        destroy_room(room2);
        destroy_room(room3);
        return NULL;
    }
    
    struct room* room5 = create_room("komnata5", "a tu viem");
    if (!room5) {
        destroy_room(room1);
        destroy_room(room2);
        destroy_room(room3);
        destroy_room(room4);
        return NULL;
    }
    struct room* room6 = create_room("komnata6", "a tu viem");
if (!room6) {
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    return NULL;
}

struct room* room7 = create_room("komnata7", "a tu viem");
if (!room7) {
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    destroy_room(room6);
    return NULL;
}

struct room* room8 = create_room("komnata8", "a tu viem");
if (!room8) {
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    destroy_room(room6);
    destroy_room(room7);
    return NULL;
}

struct room* room9 = create_room("komnata9", "a tu viem");
if (!room9) {
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    destroy_room(room6);
    destroy_room(room7);
    destroy_room(room8);
    return NULL;
}

struct room* room10 = create_room("komnata10", "a tu viem");
if (!room10) {
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    destroy_room(room6);
    destroy_room(room7);
    destroy_room(room8);
    destroy_room(room9);
    return NULL;
}

struct room* room11 = create_room("komnata11", "a tu viem");
if (!room11) {
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    destroy_room(room6);
    destroy_room(room7);
    destroy_room(room8);
    destroy_room(room9);
    destroy_room(room10);
    return NULL;
}

struct room* room12 = create_room("komnata12", "a tu viem");
if (!room12) {
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    destroy_room(room6);
    destroy_room(room7);
    destroy_room(room8);
    destroy_room(room9);
    destroy_room(room10);
    destroy_room(room11);
    return NULL;
}

struct room* room13 = create_room("komnata13", "a tu viem");
if (!room13) {
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    destroy_room(room6);
    destroy_room(room7);
    destroy_room(room8);
    destroy_room(room9);
    destroy_room(room10);
    destroy_room(room11);
    destroy_room(room12);
    return NULL;
}

struct room* room14 = create_room("komnata14", "a tu viem");
if (!room14) {
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    destroy_room(room6);
    destroy_room(room7);
    destroy_room(room8);
    destroy_room(room9);
    destroy_room(room10);
    destroy_room(room11);
    destroy_room(room12);
    destroy_room(room13);
    return NULL;
}

struct room* room15 = create_room("komnata15", "a tu viem");
if (!room15) {
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    destroy_room(room6);
    destroy_room(room7);
    destroy_room(room8);
    destroy_room(room9);
    destroy_room(room10);
    destroy_room(room11);
    destroy_room(room12);
    destroy_room(room13);
    destroy_room(room14);
    return NULL;
}



    // Створюємо контейнер для світу та додаємо кімнати
    struct container* world = create_container(NULL, ROOM, room1);
    if (!world) {
        destroy_room(room2);
        destroy_room(room3);
        destroy_room(room4);
        destroy_room(room5);
        destroy_room(room6);
        destroy_room(room7);
        destroy_room(room8);
        destroy_room(room9);
        destroy_room(room10);
        destroy_room(room11);
        destroy_room(room12);
        destroy_room(room13);
        destroy_room(room14);
        destroy_room(room15);
        return NULL;
    }
    
   add_room_to_world(world, room2);
    // if (!vew0) {
    //     destroy_world(world);
    //     return NULL;
    // }
    
     add_room_to_world(world, room3);
    // if (!vew) {
    //     destroy_world(world);
    //     return NULL;
    // }
    
    add_room_to_world(world, room4);
    // if (!vew1) {
    //     destroy_world(world);
    //     return NULL;
    // }
    
     add_room_to_world(world, room5);
    // if (!vew2) {
    //     destroy_world(world);
    //     return NULL;
    // }
     add_room_to_world(world, room6);
    // if (!vew22) {
    //     destroy_world(world);
    //     return NULL;
    // }
     add_room_to_world(world, room7);
    // if (!vew23) {
    //     destroy_world(world);
    //     return NULL;
    // }
     add_room_to_world(world, room8);
    // if (!vew24) {
    //     destroy_world(world);
    //     return NULL;
    // }
     add_room_to_world(world, room9);
    // if (!vew25) {
    //     destroy_world(world);
    //     return NULL;
    // }
     add_room_to_world(world, room10);
    // if (!vew26) {
    //     destroy_world(world);
    //     return NULL;
    // }
    add_room_to_world(world, room11);
    // if (!vew27) {
    //     destroy_world(world);
    //     return NULL;
    // }
     add_room_to_world(world, room12);
    // if (!vew28) {
    //     destroy_world(world);
    //     return NULL;
    // }
     add_room_to_world(world, room13);
    // if (!vew29) {
    //     destroy_world(world);
    //     return NULL;
    // }
     add_room_to_world(world, room14);
    // if (!vew30) {
    //     destroy_world(world);
    //     return NULL;
    // }
     add_room_to_world(world, room15);
    // if (!vew31) {
    //     destroy_world(world);
    //     return NULL;
    // }
    
// struct item* item1=create_item("STRIEBORNY KLUC", "first key from exit", 1);
// struct item* item2=create_item("MEDENY KLUC", "second key from exit", 2);
// struct item* item3=create_item("ZELEZNY KLUC", "third key from exit", 3);
// struct item* item4=create_item("ZLATY KLUC", "fourth key from exit", 4);
// struct item* item5=create_item("PLATINOVY KLUC", "fifth key from exit", 5);
// if(!item1){

//     destroy_world(world);
//     return NULL;
// }
// if(!item2){
//     destroy_item(item1);
//     destroy_world(world);
//     return NULL;
// }
// if(!item3){

//     destroy_item(item1);
//     destroy_item(item2);
//     destroy_world(world);
//     return NULL;
// }
// if(!item4){
//         destroy_item(item1);
//                 destroy_item(item2);
//         destroy_item(item3);


//     destroy_world(world);
//     return NULL;
// }
// if(!item5){
//     destroy_item(item1);
//             destroy_item(item2);
//         destroy_item(item3);
//         destroy_item(item4);

//     destroy_world(world);
//     return NULL;
// }
//////////////////////////////////
struct item* item1 = create_item("STRIEBORNY KLUC", "first key from exit", MOVABLE|USABLE);
if (item1==NULL) {
    destroy_world(world);
    return NULL;
}
add_item_to_room(room1,item1);

struct item* item2 = create_item("MEDENY KLUC", "second key from exit", OPENABLE);
if (item2==NULL) {
    destroy_item(item1);
    destroy_world(world);
    return NULL;
}
add_item_to_room(room2,item2);
struct item* item3 = create_item("ZELEZNY KLUC", "third key from exit", USABLE);
if (item3==NULL) {
    destroy_item(item1);
    destroy_item(item2);
    destroy_world(world);
    return NULL;
}
add_item_to_room(room3,item3);

struct item* item4 = create_item("ZLATY KLUC", "fourth key from exit", MOVABLE|USABLE);
if (item4==NULL) {
    destroy_item(item1);
    destroy_item(item2);
    destroy_item(item3);
    destroy_world(world);
    return NULL;
}
add_item_to_room(room4,item4);
struct item* item5 = create_item("PLATINOVY KLUC", "fifth key from exit", OPENABLE);
if (item5==NULL) {
    destroy_item(item1);
    destroy_item(item2);
    destroy_item(item3);
    destroy_item(item4);
    destroy_world(world);
    return NULL;
}
add_item_to_room(room5,item5);
set_exits_from_room(room1, room2, NULL, NULL, NULL);
set_exits_from_room(room2, room3, NULL, NULL, NULL);
set_exits_from_room(room3, room4, NULL, NULL, NULL);
set_exits_from_room(room4, room5, NULL, NULL, NULL);
set_exits_from_room(room5, room6, NULL, NULL, NULL);
set_exits_from_room(room6, room7, NULL, NULL, NULL);
set_exits_from_room(room7, room8, NULL, NULL, NULL);
set_exits_from_room(room8, room9, NULL, NULL, NULL);
set_exits_from_room(room9, room10, NULL, NULL, NULL);
set_exits_from_room(room10, room11, NULL, NULL, NULL);
set_exits_from_room(room11, room12, NULL, NULL, NULL);
set_exits_from_room(room12, room13, NULL, NULL, NULL);
set_exits_from_room(room13, room14, NULL, NULL, NULL);
set_exits_from_room(room14, room15, NULL, NULL, NULL);
set_exits_from_room(room15, NULL, NULL, NULL, NULL);

    
    return world;
}

struct container* destroy_world(struct container* world){
    if(world==NULL){
        return NULL;
    }
    if(world){
        if(world!=NULL){
            destroy_containers(world);

        }
    }
    return NULL;
}
struct container* add_room_to_world(struct container* world, struct room* room){
    // if (!room) return NULL;
    // if(room==NULL){
    //     return NULL;
    // }
    // if(world==NULL&&room!=NULL){
    //     world=create_container(NULL,ROOM,room);
    //     return world;
    // }
    // struct container* cur = world;
    // while (cur != NULL) {
    //     int i = 0;
    //     while (cur->room->name[i] != '\0' && room->name[i] != '\0' && cur->room->name[i] == room->name[i]) {
    //         i++;
    //     }        
    //     if (cur->room->name[i] == '\0' && room->name[i] == '\0') {
    //         return NULL;
    //     }
        
    //     cur = cur->next;
    // }
    // struct container* contain = create_container(world,ROOM,room);
    // //contain->next = world;
    // return contain;
    if (!room) return NULL;
    if (world == NULL && room != NULL) {
        world = create_container(NULL, ROOM, room);
        return world;
    }
    struct container* cur = world;
    while (cur != NULL) {
        int i = 0;
        while (cur->room->name[i] != '\0' && room->name[i] != '\0' && cur->room->name[i] == room->name[i]) {
            i++;
        }
        if (cur->room->name[i] == '\0' && room->name[i] == '\0') {
            return NULL;
        }

        cur = cur->next;
    }
    struct container* contain = create_container(world, ROOM, room);
    return contain;
}
struct room* get_room(struct container* world, char* name){
    if(world==NULL || name==NULL){
        return NULL;
    }
    struct room* nieco=get_from_container_by_name(world, name);
    return nieco;
}