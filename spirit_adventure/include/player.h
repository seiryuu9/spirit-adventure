#ifndef SPIRIT_ADVENTURE_PLAYER_H //include guard, so the file is only included once
#define SPIRIT_ADVENTURE_PLAYER_H

#include "map.h"

#define MAX_INVENTORY 12
#define PLAYER_MAX_HEALTH 100

typedef struct {
    char *name;
    int currentRoom; //index of the current room, from map array
    Item *inventory[MAX_INVENTORY];
    int inventoryCount;
    int health;
    int x, y;
} Player;

// functions for the player
Player *createPlayer(char *name);
void freePlayer(Player *player);
void addItemToInventory(Player *player, Item *item);
int playerHasItem(Player *player, const char *itemName);
int removeItemFromInventory(Player *player, const char *itemName);


#endif // SPIRIT_ADVENTURE_PLAYER_H
