#ifndef SPIRIT_ADVENTURE_GAME_H
#define SPIRIT_ADVENTURE_GAME_H
extern int maskCount;
extern int dragonHornCount;
extern int enemiesDefeated;

#include "map.h"
#include "player.h"

typedef enum {
    INTERACT_TALK,
    INTERACT_FIGHT,
    DONT_INTERACT
} InteractionType;

// movement inside a room - only needs one room
void movePlayerInRoom(Player *player, Room *map, Direction dir);
// movement between rooms through doors
void movePlayerToRoom(Player *player, Room *map);

// info about current room
void lookAround(Room *room);
void showInventory(Player *player);
void useItem(Player *player, char *itemName);
void showCommands(void);

// interactions
void pickUpItem(Player *player, Room *map, Item *item);
void interactWithNPC(Player *player, NPC *npc, Room *room, InteractionType action);
void fight(Player *player, NPC *npc, Room *map);

// main game loop and command processing
void startGame(Player *player, Room *map);
void processCommand(Player *player, Room *map, const char *input); //centralized parser for commands, calls relevant function based on player input

#endif // SPIRIT_ADVENTURE_GAME_H
