#include "../include/save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// writes a string to file
static void writeString(FILE *f, const char *str) {
    size_t len = strlen(str);
    fwrite(&len, sizeof(size_t), 1, f);
    fwrite(str, sizeof(char), len, f);
}

//reads a string from file
static void readString(FILE *f, char *buffer, size_t maxLen) {
    size_t len;
    fread(&len, sizeof(size_t), 1, f);
    if (len >= maxLen) len = maxLen - 1;
    fread(buffer, sizeof(char), len, f);
    buffer[len] = '\0';
}

// saves the entire game state to a binary file
int saveGame(const char *filename, Player *player, Room *map) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        perror("Failed to open file for saving");
        return 0;
    }

    // saves player
    writeString(f, player->name);
    fwrite(&player->health, sizeof(int), 1, f);
    fwrite(&player->x, sizeof(int), 1, f);
    fwrite(&player->y, sizeof(int), 1, f);
    fwrite(&player->currentRoom, sizeof(int), 1, f);

    // inventory
    fwrite(&player->inventoryCount, sizeof(int), 1, f);
    for (int i = 0; i < player->inventoryCount; i++) {
        writeString(f, player->inventory[i]->name);
    }

    // rooms
    int roomCount = ROOM_COUNT;
    fwrite(&roomCount, sizeof(int), 1, f);
    for (int r = 0; r < 6; r++) {
        Room *room = &map[r];
        fwrite(&room->width, sizeof(int), 1, f);
        fwrite(&room->height, sizeof(int), 1, f);

        // grid
        for (int y = 0; y < room->height; y++) {
            fwrite(room->grid[y], sizeof(char), room->width, f);
        }

        // npcs
        fwrite(&room->npcCount, sizeof(int), 1, f);
        for (int n = 0; n < room->npcCount; n++) {
            NPC *npc = room->npcs[n];
            writeString(f, npc->name);
            fwrite(&npc->type, sizeof(int), 1, f);
            fwrite(&npc->x, sizeof(int), 1, f);
            fwrite(&npc->y, sizeof(int), 1, f);
            fwrite(&npc->health, sizeof(int), 1, f);
        }

        // items on the ground
        fwrite(&room->itemCount, sizeof(int), 1, f);
        for (int i = 0; i < room->itemCount; i++) {
            Item *item = room->items[i];
            writeString(f, item->name);
            fwrite(&item->x, sizeof(int), 1, f);
            fwrite(&item->y, sizeof(int), 1, f);
        }
    }

    fclose(f);
    printf("Game saved to %s.\n", filename);
    return 1;
}

// loads only the dynamic things - others are static so you don't need to load them manually
int loadGame(const char *filename, Player *player, Room *map) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("Failed to open file");
        return 0;
    }

    char buffer[128];

    // player
    readString(f, buffer, sizeof(buffer));
    player->name = strdup(buffer);  // allocate name dynamically
    fread(&player->health, sizeof(int), 1, f);
    fread(&player->x, sizeof(int), 1, f);
    fread(&player->y, sizeof(int), 1, f);
    fread(&player->currentRoom, sizeof(int), 1, f);

    fread(&player->inventoryCount, sizeof(int), 1, f);
    for (int i = 0; i < player->inventoryCount; i++) {
        readString(f, buffer, sizeof(buffer));
        player->inventory[i] = malloc(sizeof(Item));
        player->inventory[i]->name = strdup(buffer);
    }

    // rooms
    for (int r = 0; r < ROOM_COUNT; r++) {
        Room *room = &map[r];

        // npcs
        fread(&room->npcCount, sizeof(int), 1, f);
        for (int n = 0; n < room->npcCount; n++) {
            NPC *npc = room->npcs[n];
            fread(&npc->x, sizeof(int), 1, f);
            fread(&npc->y, sizeof(int), 1, f);
            fread(&npc->health, sizeof(int), 1, f);
        }

        // items
        fread(&room->itemCount, sizeof(int), 1, f);
        for (int i = 0; i < room->itemCount; i++) {
            Item *item = room->items[i];
            fread(&item->x, sizeof(int), 1, f);
            fread(&item->y, sizeof(int), 1, f);
        }
    }

    fclose(f);
    printf("Game loaded from %s.\n", filename);
    return 1;
}