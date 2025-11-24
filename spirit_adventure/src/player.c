#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"

Player *createPlayer(const char *name) {
    Player *player = malloc(sizeof(Player));
    if (!player) {
        fprintf(stderr, "Failed to allocate memory for player\n");
        exit(EXIT_FAILURE);
    }
    player->name = strdup(name); // duplicates the name - safer (lost pointer or change name changes the copy)
    player->currentRoom = 0;
    player->inventoryCount = 0;
    player->health = PLAYER_MAX_HEALTH;
    player->x = 0;
    player->y = 1;
    return player;
}

void freePlayer(Player *player) {
    if (player) {
        free(player->name);
        free(player);
    }
}

void addItemToInventory(Player *player, Item *item) {
    if (player->inventoryCount < MAX_INVENTORY) {
        int index = player->inventoryCount;  // saves the current index
        player->inventory[index] = item;      // inserts the item
        player->inventoryCount++;
    } else {
        printf("Inventory is full! Cannot add %s\n", item->name);
    }
}
