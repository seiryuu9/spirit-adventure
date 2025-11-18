#ifndef SPIRIT_ADVENTURE_GAME_H
#define SPIRIT_ADVENTURE_GAME_H

#include "map.h"
#include "player.h"

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef enum {
    INTERACT_TALK,
    INTERACT_FIGHT
} InteractionType;

// movement inside a room (grid-based)
int movePlayerInRoom(Player *player, Room *room, Direction dir);
// movement between rooms through doors
int movePlayerToRoom(Player *player, Room *map, Direction dir);

// info about current room
void lookAround(Player *player, Room *room);

// interactions
void pickUpItem(Player *player, Room *room, Item *item);
void interactWithNPC(Player *player, NPC *npc, InteractionType action);

// main game loop and command processing
void startGame(Player *player, Room *map);
void processCommand(Player *player, Room *map, const char *input); //centralized parser for commands, calls relevant function based on player input

#endif // SPIRIT_ADVENTURE_GAME_H
