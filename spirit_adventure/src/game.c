#include "../include/game.h"
#include <stdio.h>

int movePlayerInRoom(Player *player, Room *room, Direction dir) {
    int newX = player->x;
    int newY = player->y;

    switch (dir) {
        case NORTH: newY++; break;
        case SOUTH: newY--; break;
        case EAST:  newX++; break;
        case WEST:  newX--; break;
        default: return 0;
    }

    if (newX < 0 || newX >= room->width || newY < 0 || newY >= room->height) {
        printf("You hit a wall!\n");
        return 0;
    }

    player->x = newX;
    player->y = newY;

    return 1; // 0 on unsuccessful move, 1 on successful move
}

int movePlayerToRoom(Player *player, Room *map, Direction dir) {
    if (map->grid[player->y][player->x] == 'D') {

    }

    return 0; // Return 0 on success
}

void lookAround(Player *player, Room *room) {
    // Implement logic to describe the current room and its contents
}

void pickUpItem(Player *player, Room *room, Item *item) {
    // Implement logic for player to pick up an item from the room
}

void interactWithNPC(Player *player, NPC *npc, InteractionType action) {
    // Implement interaction logic based on action type (talk or fight)
}

void startGame(Player *player, Room *map) {
    // Implement the main game loop
    // Continuously prompt for player input and process commands
}

void processCommand(Player *player, Room *map, const char *input) {
    // Implement command parsing logic
    // Call relevant functions based on player input
}