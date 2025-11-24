#include <stdlib.h>
#include "../include/map.h"

Room *initializeMap(void) {
    Room *map = malloc(sizeof(Room) * ROOM_COUNT); // array of 6 rooms of type Room in heap
    if (!map) {return NULL;}

// room 1 3x3
    map[0].name = "Middle of Nowhere";
    map[0].description = "You find yourself in the middle of a room that looks like it's supposed to resemble the inside of a shrine. Everything looks abandoned.";
    map[0].width = 3;
    map[0].height = 3;
    map[0].grid = malloc(sizeof(char *) * map[0].height); // mem for array of char pointers for each row
    for (int i = 0; i < map[0].height; i++) { // for each row / pointer allocate an array of chars
        map[0].grid[i] = malloc(sizeof(char) * (map[0].width + 1)); // '\0'
    }
    map[0].grid[2][0] = ' '; map[0].grid[2][1] = 'D'; map[0].grid[2][2] = 'N';
    map[0].grid[1][0] = 'D'; map[0].grid[1][1] = ' '; map[0].grid[1][2] = 'N';
    map[0].grid[0][0] = ' '; map[0].grid[0][1] = 'D'; map[0].grid[0][2] = ' ';

    map[0].itemCount = 0;

    map[0].npcCount = 2;
    map[0].npcs[0] = malloc(sizeof(NPC));
    map[0].npcs[0]->name = "Mysterious Monk";
    map[0].npcs[0]->type = FRIENDLY;
    map[0].npcs[0]->x = 2;
    map[0].npcs[0]->y = 2;

    map[0].npcs[1] = malloc(sizeof(NPC));
    map[0].npcs[1]->name = "Wandering Spirit";
    map[0].npcs[1]->type = NEUTRAL;
    map[0].npcs[1]->x = 2;
    map[0].npcs[1]->y = 1;

// room 2 4x4
    map[1].name = "Garden";
    map[1].description = "You enter the shrine garden with beautiful flowers and a small pond with lotus flowers. Surprisingly, it looks well-maintained.";
    map[1].width = 4;
    map[1].height = 4;
    map[1].grid = malloc(sizeof(char *) * map[1].height);
    for (int i = 0; i < map[1].height; i++) {
        map[1].grid[i] = malloc(sizeof(char) * (map[1].width + 1));
    }
    map[1].grid[3][0] = ' '; map[1].grid[3][1] = ' '; map[1].grid[3][2] = ' '; map[1].grid[3][3] = ' ';
    map[1].grid[2][0] = 'D'; map[1].grid[2][1] = ' '; map[1].grid[2][2] = 'I'; map[1].grid[2][3] = ' ';
    map[1].grid[1][0] = ' '; map[1].grid[1][1] = ' '; map[1].grid[1][2] = ' '; map[1].grid[1][3] = ' ';
    map[1].grid[0][0] = 'I'; map[1].grid[0][1] = ' '; map[1].grid[0][2] = 'D'; map[1].grid[0][3] = ' ';

    map[1].itemCount = 2;
    map[1].items[0] = malloc(sizeof(Item));
    map[1].items[0]->name = "Fox mask part";
    map[1].items[0]->x = 0;
    map[1].items[0]->y = 0;

    map[1].items[1] = malloc(sizeof(Item));
    map[1].items[1]->name = "Dragon horn";
    map[1].items[1]->x = 2;
    map[1].items[1]->y = 2;

    map[1].npcCount = 0;

// room 3 4x4
    map[2].name = "Outer Courtyard";
    map[2].description = "You step into the outer courtyard of the shrine, surrounded by cherry blossom trees, enclosed by tall stone walls.";
    map[2].width = 4;
    map[2].height = 4;
    map[2].grid = malloc(sizeof(char *) * map[2].height);
    for (int i = 0; i < map[2].height; i++) {
        map[2].grid[i] = malloc(sizeof(char) * (map[2].width + 1));
    }
    map[2].grid[3][0] = 'I'; map[2].grid[3][1] = ' '; map[2].grid[3][2] = ' '; map[2].grid[3][3] = ' ';
    map[2].grid[2][0] = ' '; map[2].grid[2][1] = ' '; map[2].grid[2][2] = ' '; map[2].grid[2][3] = ' ';
    map[2].grid[1][0] = ' '; map[2].grid[1][1] = ' '; map[2].grid[1][2] = 'N'; map[2].grid[1][3] = 'D';
    map[2].grid[0][0] = 'I'; map[2].grid[0][1] = ' '; map[2].grid[0][2] = ' '; map[2].grid[0][3] = ' ';

    map[2].itemCount = 2;
    map[2].items[0] = malloc(sizeof(Item));
    map[2].items[0]->name = "Fox mask part";
    map[2].items[0]->x = 0;
    map[2].items[0]->y = 0;

    map[2].items[1] = malloc(sizeof(Item));
    map[2].items[1]->name = "Fox mask part";
    map[2].items[1]->x = 0;
    map[2].items[1]->y = 3;

    map[2].npcCount = 1;
    map[2].npcs[0] = malloc(sizeof(NPC));
    map[2].npcs[0]->name = "Hostile spirit";
    map[2].npcs[0]->type = ENEMY;
    map[2].npcs[0]->health = 50;
    map[2].npcs[0]->x = 2;
    map[2].npcs[0]->y = 1;
    map[2].npcs[0]->reward = NULL;

// room 4 4x4
    map[3].name = "Library";
    map[3].description = "You find yourself in a quiet library filled with ancient scrolls and books on spirituality and martial arts.";
    map[3].width = 4;
    map[3].height = 4;
    map[3].grid = malloc(sizeof(char *) * map[3].height);
    for (int i = 0; i < map[3].height; i++) {
        map[3].grid[i] = malloc(sizeof(char) * (map[3].width + 1));
    }
    map[3].grid[3][0] = ' '; map[3].grid[3][1] = ' '; map[3].grid[3][2] = ' '; map[3].grid[3][3] = ' ';
    map[3].grid[2][0] = ' '; map[3].grid[2][1] = 'I'; map[3].grid[2][2] = ' '; map[3].grid[2][3] = ' ';
    map[3].grid[1][0] = ' '; map[3].grid[1][1] = ' '; map[3].grid[1][2] = 'N'; map[3].grid[1][3] = 'D';
    map[3].grid[0][0] = ' '; map[3].grid[0][1] = ' '; map[3].grid[0][2] = ' '; map[3].grid[0][3] = ' ';

    map[3].itemCount = 1;
    map[3].items[0] = malloc(sizeof(Item));
    map[3].items[0]->name = "Dragon horn";
    map[3].items[0]->x = 1;
    map[3].items[0]->y = 2;

    map[3].npcCount = 1;
    map[3].npcs[0] = malloc(sizeof(NPC));
    map[3].npcs[0]->name = "Shiny hostile spirit";
    map[3].npcs[0]->type = ENEMY;
    map[3].npcs[0]->health = 75;
    map[3].npcs[0]->x = 2;
    map[3].npcs[0]->y = 1;
    map[3].npcs[0]->reward = malloc(sizeof(Item));
    map[3].npcs[0]->reward->name = "Dragon horn";
    map[3].npcs[0]->reward->description = "The spirit dropped a Dragon horn after being defeated.";


// room 5 4x4
    map[4].name = "Tea Room";
    map[4].description = "You enter a tea room with mats and a low table set for a traditional tea ceremony. It looks like it hasn't been used in a while.";
    map[4].width = 4;
    map[4].height = 4;
    map[4].grid = malloc(sizeof(char *) * map[4].height);
    for (int i = 0; i < map[4].height; i++) {
        map[4].grid[i] = malloc(sizeof(char) * (map[4].width + 1));
    }
    map[4].grid[3][0] = ' '; map[4].grid[3][1] = ' '; map[4].grid[3][2] = 'D'; map[4].grid[3][3] = ' ';
    map[4].grid[2][0] = ' '; map[4].grid[2][1] = ' '; map[4].grid[2][2] = ' '; map[4].grid[2][3] = 'I';
    map[4].grid[1][0] = ' '; map[4].grid[1][1] = ' '; map[4].grid[1][2] = ' '; map[4].grid[1][3] = ' ';
    map[4].grid[0][0] = 'N'; map[4].grid[0][1] = ' '; map[4].grid[0][2] = 'N'; map[4].grid[0][3] = ' ';

    map[4].itemCount = 1;
    map[4].items[0] = malloc(sizeof(Item));
    map[4].items[0]->name = "Fox mask part";
    map[4].items[0]->x = 3;
    map[4].items[0]->y = 2;

    map[4].npcCount = 2;
    map[4].npcs[0] = malloc(sizeof(NPC));
    map[4].npcs[0]->name = "Shiny hostile spirit";
    map[4].npcs[0]->type = ENEMY;
    map[4].npcs[0]->health = 75;
    map[4].npcs[0]->x = 0;
    map[4].npcs[0]->y = 0;
    map[4].npcs[0]->reward = malloc(sizeof(Item));
    map[4].npcs[0]->reward->name = "Dragon horn";
    map[4].npcs[0]->reward->description = "The spirit dropped a Dragon horn after being defeated.";

    map[4].npcs[1] = malloc(sizeof(NPC));
    map[4].npcs[1]->name = "Hostile spirit";
    map[4].npcs[1]->type = ENEMY;
    map[4].npcs[1]->health = 50;
    map[4].npcs[1]->x = 2;
    map[4].npcs[1]->y = 0;
    map[4].npcs[1]->reward = NULL;

// room 6 1x1 - boss room
    map[5].name = "Inner Sanctum";
    map[5].description = "You step into the inner sanctum of the shrine, you see an enormous cherry blossom tree in the middle of an otherwise empty room.";
    map[5].width = 1;
    map[5].height = 1;
    map[5].grid = malloc(sizeof(char *) * map[5].height);
    for (int i = 0; i < map[5].height; i++) {
        map[5].grid[i] = malloc(sizeof(char) * (map[5].width + 1));
    }
    map[5].grid[0][0] = ' ';
    map[5].itemCount = 0;
    map[5].npcCount = 0;

    return map;
}

void freeMap(Room *map) {
    if (!map) return;

    for (int r = 0; r < ROOM_COUNT; r++) {
        Room *room = &map[r]; // pointer to current room

        // frees items
        for (int i = 0; i < room->itemCount; i++) {
            if (room->items[i]) { // easier way of accessing the item pointer (*room).items[i]
                free(room->items[i]);
            }
        }

        // frees npcs and their rewards
        for (int n = 0; n < room->npcCount; n++) {
            if (room->npcs[n]) {
                if (room->npcs[n]->reward) {
                    free(room->npcs[n]->reward);
                }
                free(room->npcs[n]);
            }
        }

        // frees grid
        if (room->grid) {
            for (int y = 0; y < room->height; y++) {
                free(room->grid[y]);
            }
            free(room->grid); // array of row pointers
        }
    }
    free(map);
}
