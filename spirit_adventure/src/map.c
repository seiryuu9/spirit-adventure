#include <stdlib.h>
#include "../include/map.h"

void addItem(Room *room, const char *name, int x, int y) {
    if (room->itemCount >= MAX_ITEMS) {
        return;
    }
    Item *item = malloc(sizeof(Item));
    item->name = name; //does malloc and copies the name
    item->x = x;
    item->y = y;
    room->items[room->itemCount] = item;
    room->itemCount++;
}

void addNpc(Room *room, const char *name, NPCType type, int health, int x, int y, Item *reward) {
    if (room->npcCount >= MAX_NPCS) {
        return;
    }
    NPC *npc = malloc(sizeof(NPC));
    npc->name = name;
    npc->type = type;
    npc->health = health;
    npc->x = x;
    npc->y = y;
    npc->reward = reward;
    room->npcs[room->npcCount] = npc;
    room->npcCount++;
}

void addDoor(Room *room, Direction dir, int leadsTo, int x, int y, int exitX, int exitY) {
    if (room->doorCount >= MAX_DOORS) {
        return;
    }

    Door *door = &room->doors[room->doorCount];
    door->dir = dir;
    door->leadsTo = leadsTo;
    door->x = x;
    door->y = y;
    door->exitX = exitX;
    door->exitY = exitY;

    room->doorCount++;
}

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

    addNpc(&map[0], "Mysterious Monk", FRIENDLY, -1, 2, 2, NULL);
    addNpc(&map[0], "Wandering Spirit", NEUTRAL, -1, 2, 1, NULL);

    addDoor(&map[0], NORTH, 1, 1, 2, 2, 0);
    addDoor(&map[0], WEST, 3, 0, 1, 3, 1);
    addDoor(&map[0], SOUTH, 4, 1, 0, 2, 3);
    addDoor(&map[0], EAST, 5, 2, 1, 0, 0);

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

    addItem(&map[1], "Fox mask part", 0, 0);
    addItem(&map[1], "Dragon horn", 2, 2);

    addDoor(&map[1], SOUTH, 0, 2, 0, 1, 2);
    addDoor(&map[1], WEST, 2, 0, 2, 3, 1);

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

    addItem(&map[2], "Fox mask part", 0, 0);
    addItem(&map[2], "Fox mask part", 0, 3);

    addNpc(&map[2], "Hostile spirit", ENEMY, 50, 2, 1, NULL);

    addDoor(&map[2], EAST, 1, 3, 1, 0, 2);

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

    addItem(&map[3], "Dragon horn", 1, 2);

    Item *dragonReward1 = malloc(sizeof(Item));
    dragonReward1->name = "Dragon horn";
    dragonReward1->description = "The spirit dropped a Dragon horn after being defeated.";
    addNpc(&map[3], "Shiny hostile spirit", ENEMY, 75, 2, 1, dragonReward1);

    addDoor(&map[3], EAST, 0, 3, 1, 0, 1);

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

    addItem(&map[4], "Fox mask part", 3, 2);

    Item *dragonReward2 = malloc(sizeof(Item));
    dragonReward2->name = "Dragon horn";
    dragonReward2->description = "The spirit dropped a Dragon horn after being defeated.";

    addNpc(&map[4], "Shiny hostile spirit", ENEMY, 75, 0, 0, dragonReward2);
    addNpc(&map[4], "Hostile spirit", ENEMY, 50, 2, 0, NULL);

    addDoor(&map[4], NORTH, 0, 2, 3, 0, 1);

// room 6 1x1 - boss room
    map[5].name = "";
    map[5].description = "";
    map[5].width = 0;
    map[5].height = 0;
    map[5].grid = 0;

    return map;
}

void freeMap(Room *map) {
    if (!map) return;

    for (int r = 0; r < ROOM_COUNT; r++) {
        Room *room = &map[r]; // pointer to current room

        // frees only items that weren't picked up
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

void removeItemFromRoom(Room *room, Item *item) {
    for (int i = 0; i < room->itemCount; i++) {
        if (room->items[i] == item) {

            // moves the items back in array
            for (int j = i; j < room->itemCount - 1; j++) {
                room->items[j] = room->items[j + 1];
            }

            room->itemCount--;
            room->items[room->itemCount] = NULL; // clears possibly dangling pointer after freeing
            return;
        }
    }
}

void removeNPCFromRoom(Room *room, NPC *npc) {
    for (int i = 0; i < room->npcCount; i++) {
        if (room->npcs[i] == npc) {

            for (int j = i; j < room->npcCount - 1; j++) {
                room->npcs[j] = room->npcs[j + 1];
            }

            room->npcCount--;
            room->npcs[room->npcCount] = NULL;
            return;
        }
    }
}

Item* getItemAt(Room *room, int x, int y) {
    for (int i = 0; i < room->itemCount; i++) {
        Item *item = room->items[i];
        if (item->x == x && item->y == y) {
            return item;
        }
    }
    return NULL; // no item
}

NPC* getNPCAt(Room *room, int x, int y) {
    for (int i = 0; i < room->npcCount; i++) {
        NPC *npc = room->npcs[i];
        if (npc->x == x && npc->y == y) {
            return npc;
        }
    }
    return NULL;
}

