#include "backpack.h"
#include "command.h"
#include "container.h"
#include "game.h"
#include "item.h"
#include "parser.h"
#include "room.h"
#include "world.h"
#include <ctype.h>
#include <stdio.h>

int main() {
    // Инициализация компонентов игры
    struct container* world = create_world();
    struct room* start_room = create_room("Start Room", "The room where your journey begins.");
    struct room* end_room = create_room("End Room", "The final room of the game.");
    add_room_to_world(world, start_room);
    add_room_to_world(world, end_room);

    struct item* key = create_item("Key", "A small key to open doors", MOVABLE | USABLE);
    struct item* book = create_item("Book", "An ancient book", EXAMINABLE);
    add_item_to_room(start_room, key);
    add_item_to_room(end_room, book);

    struct backpack* bp = create_backpack(5);
    add_item_to_backpack(bp, key);

    struct command* look_command = create_command("look", "Look around the room", "^look$", 1);
    struct command* exit_command = create_command("exit", "Exit the game", "^exit$", 1);
    struct parser* game_parser = create_parser();

    struct container* command_container = create_container(NULL, COMMAND, look_command);
    create_container(command_container, COMMAND, exit_command);

    // Игровой контекст и игровой цикл
    struct game* game = create_game();
    game->world = world;
    game->current_room = start_room;
    game->backpack = bp;
    game->parser = game_parser;

    // Получение и удаление предмета из комнаты
    struct item* room_item = get_item_from_room(start_room, "Key");
    if (room_item) {
        delete_item_from_room(start_room, room_item);
    }

    // Получение и удаление предмета из рюкзака
    struct item* backpack_item = get_item_from_backpack(bp, "Key");
    if (backpack_item) {
        delete_item_from_backpack(bp, backpack_item);
    }

    // Удаление контейнера
    remove_container(command_container, exit_command);

    // Запуск игрового цикла
    play_game(game);
	destroy_item(NULL);
	get_room(NULL,NULL);
	parse_input(NULL,NULL);

    // Уничтожение всех объектов и ресурсов
    destroy_game(game);
    destroy_parser(game_parser);
    destroy_containers(command_container);
    destroy_command(look_command);
    destroy_command(exit_command);
    destroy_backpack(bp);
    destroy_room(start_room);
    destroy_room(end_room);
    destroy_world(world);

    return 0;
}