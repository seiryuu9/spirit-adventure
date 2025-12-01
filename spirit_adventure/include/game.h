#ifndef SPIRIT_ADVENTURE_GAME_H
#define SPIRIT_ADVENTURE_GAME_H

#include "map.h"
#include "player.h"

typedef enum {
    INTERACT_TALK,
    INTERACT_FIGHT,
    DONT_INTERACT
} InteractionType;

// movement inside a room - only needs one room
int movePlayerInRoom(Player *player, Room *room, Direction dir);
// movement between rooms through doors - needs the map of the rooms
int movePlayerToRoom(Player *player, Room *map, Direction dir);

// info about current room
void lookAround(Room *room);
void showInventory(Player *player);
void useItem(Player *player, char *item);
void showCommands(void);

// interactions
void pickUpItem(Player *player, Room *room, Item *item);
void interactWithNPC(Player *player, NPC *npc, Room *room, InteractionType action);
void fight(Player *player, NPC *npc, Room *room);

// main game loop and command processing
void startGame(Player *player, Room *map);
void processCommand(Player *player, Room *map, const char *input); //centralized parser for commands, calls relevant function based on player input

#endif // SPIRIT_ADVENTURE_GAME_H
