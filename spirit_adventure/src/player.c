#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"
#include "../include/text.h"

Player *createPlayer(char *name) {
    Player *player = malloc(sizeof(Player));
    if (!player) {
        fprintf(stderr, "Failed to allocate memory for player\n");
        exit(EXIT_FAILURE);
    }
    player->name = name;
    player->currentRoom = 0;
    player->inventoryCount = 0;
    player->health = PLAYER_MAX_HEALTH;
    player->x = 0;
    player->y = 1;
    return player;
}

void freePlayer(Player *player) {
    for (int i = 0; i < player->inventoryCount; i++) {
        if (player->inventory[i]) {
            free(player->inventory[i]);  // frees items in inventory
        }
    }

    free(player);
}

void addItemToInventory(Player *player, Item *item) {
    if (player->inventoryCount < MAX_INVENTORY) {
        int index = player->inventoryCount;  // saves the current index
        player->inventory[index] = item;      // inserts the item
        player->inventoryCount++;
        printf("Added %s to the inventory.\n", item->name);
    } else {
        printf("Inventory is full! Cannot add %s\n", item->name);
    }
}

int playerHasItem(Player *player, const char *itemName) {
    for (int i = 0; i < player->inventoryCount; i++) {
        if (strcmp(player->inventory[i]->name, itemName) == 0) {
            return 1;   // has item
        }
    }
    return 0;
}

void removeItemFromInventory(Player *player, const char *itemName) {
    for (int i = 0; i < player->inventoryCount; i++) {
        if (strcmp(player->inventory[i]->name, itemName) == 0) {
            // moves the items back in array
            for (int j = i; j < player->inventoryCount - 1; j++) {
                player->inventory[j] = player->inventory[j + 1];
            }

            player->inventoryCount--;
            player->inventory[player->inventoryCount] = NULL;

            return;
        }
    }
}



