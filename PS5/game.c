#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "world.h"
#include"backpack.h"
#include"room.h"

struct game* create_game() {
    struct game* play = (struct game*)calloc(1, sizeof(struct game));
    if (play == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    play->state = PLAYING;
    play->parser = create_parser();
    play->world = create_world();
    play->backpack = create_backpack(5);
    play->current_room = play->world->room;

    return play;
}

struct game* destroy_game(struct game* game) {
    if (game == NULL) {
        return NULL;
    }
    if(game){
        if (game->parser!=NULL) {
            destroy_parser(game->parser);
            game->parser = NULL;
        }
        if (game->world!=NULL) {
            destroy_containers(game->world);
            game->world = NULL;
        }
        if (game->backpack!=NULL) {
            destroy_backpack(game->backpack);
            game->backpack = NULL;
        }
        free(game);
    }
    return NULL;
}

void play_game(struct game* game) {
    if (game == NULL) {
        printf("Game is not initialized\n");
        return;
    }

    printf("WELCOME TO THE GAME\n");

    char input[INPUT_BUFFER_SIZE];
    while (game->state == PLAYING) {
        printf("\n> ");
        fgets(input, INPUT_BUFFER_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0';

        struct command* cmd = parse_input(game->parser, input);
        if (cmd == NULL) {
            printf("Invalid command\n");
            continue;
        }

        execute_command(game, cmd);

        if (game->state == GAMEOVER) {
            printf("YOU LOSE. GOODBYE.\n");
            
        } else if (game->state == SOLVED) {
            printf("CONGRATULATIONS! YOU SOLVED THE GAME.\n");
        } else if (game->state == RESTART) {
            printf("RESTARTING THE GAME...\n");
            destroy_game(game);
            game = create_game();
        }
    }
    

}

void execute_command(struct game* game, struct command* command) {
    // if (game == NULL || command == NULL) {
    //     return;
    // }

    // if (!strcmp(command->name, "KONIEC")) {
    //     game->state = GAMEOVER;
    //     return;
    // }

    // if (!strcmp(command->name, "RESTART")) {
    //     free(game);
    //     game->state = RESTART;
    //     return;
    // }
    // //sever
    // if (!strcmp(command->name, "SEVER")) {
    //     if (game->current_room->north == NULL) {
    //         printf("There's no room to the north\n");
    //     } else {
    //         game->current_room = game->current_room->north;
    //         printf("You moved to the north\n");
    //     }
    //     return;
    // }
    // //juh
    // if (!strcmp(command->name, "JUH")) {
    //     if (game->current_room->south == NULL) {
    //         printf("There's no room to the south\n");
    //     } else {
    //         game->current_room = game->current_room->south;
    //         printf("You moved to the south\n");
    //     }
    //     return;
    // }
    // //zapad
    // if (!strcmp(command->name, "ZAPAD")) {
    //     if (game->current_room->west == NULL) {
    //         printf("There's no room to the west\n");
    //     } else {
    //         game->current_room = game->current_room->west;
    //         printf("You moved to the west\n");
    //     }
    //     return;
    // }
    // //vuhod
    // if (!strcmp(command->name, "VYHOD")) {
    //     if (game->current_room->east == NULL) {
    //         printf("There's no room to the east\n");
    //     } else {
    //         game->current_room = game->current_room->east;
    //         printf("You moved to the east\n");
    //     }
    //     return;
    // }
    // if (!strcmp(command->name, "ROZHLIADNI SA")) {
    //     show_room(game->current_room);
    //     return;
    // }

    // if (!strcmp(command->name, "PRIKAZY")) {
    //     printf("Available commands:\n");
    //     // Implement logic to print available commands
    //     return;
    // }

    // if (!strcmp(command->name, "O HRE")) {
    //     printf("Once upon a time...\n");
    //     return;
    // }

    // if (!strcmp(command->name, "VERZIA")) {
    //     printf("Game Version 1.0\n");
    //     return;
    // }

    // if (!strcmp(command->name, "VEZMI")) {
    //     // Implement logic to take an item
    //     return;
    // }

    // if (!strcmp(command->name, "INVENTAR")) {
    //     // Implement logic to view inventory
    //     return;
    // }

    // if (!strcmp(command->name, "PRESKUMAJ")) {
    //     // Implement logic to examine an item
    //     return;
    // }

    // printf("Unknown command: %s\n", command->name);
    /////////////////////////////////////////////
    if (game == NULL || command == NULL) {
        return;
    }
    if (!strcmp(command->name, "KONIEC")) {
        game->state = GAMEOVER;
    } else if (!strcmp(command->name, "RESTART")) {
        game->state = RESTART;
    } else if (!strcmp(command->name, "SEVER")) {
        if (game->current_room->north == NULL) {
            printf("There's no room to the north\n");
        } else {
            game->current_room = game->current_room->north;
            printf("You moved to the north\n");
        }
    } else if (!strcmp(command->name, "JUH")) {
        if (game->current_room->south == NULL) {
            printf("There's no room to the south\n");
        } else {
            game->current_room = game->current_room->south;
            printf("You moved to the south\n");
        }
    } else if (!strcmp(command->name, "ZAPAD")) {
        if (game->current_room->west == NULL) {
            printf("There's no room to the west\n");
        } else {
            game->current_room = game->current_room->west;
            printf("You moved to the west\n");
        }
    } else if (!strcmp(command->name, "VYHOD")) {
        if (game->current_room->east == NULL) {
            printf("There's no room to the east\n");
        } else {
            game->current_room = game->current_room->east;
            printf("You moved to the east\n");
        }
    }else if (!strcmp(command->name, "ROZHLIADNI SA")) {
        show_room(game->current_room);
         return;
    }
     else {
        printf("Unknown command: %s\n", command->name);
    destroy_command(command);
    
    return;
}
}
