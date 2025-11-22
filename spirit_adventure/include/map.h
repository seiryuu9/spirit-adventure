//headers are for struct, typedef, enum etc, c files are for logic

#ifndef SPIRIT_ADVENTURE_MAP_H
#define SPIRIT_ADVENTURE_MAP_H

#define MAX_ITEMS 2 //in one room on the ground
#define MAX_NPCS 12
#define ROOM_COUNT 6

typedef enum { FRIENDLY, ENEMY, NEUTRAL } NPCType;

typedef struct {
    char *name;
    char *description;
    int x, y;
} Item;

// NPC
typedef struct {
    char *name;
    NPCType type;
    int health;         // for enemies
    Item *reward;       // drops after defeating them
    int x, y;
} NPC;

typedef struct {
    char *name;
    char *description;
    int width;
    int height;
    char **grid; // ' ' = empty, 'D' = door, 'N' = npc, 'I' = item
    Item *items[MAX_ITEMS];
    int itemCount;
    NPC *npcs[MAX_NPCS];
    int npcCount;
} Room;

Room *initializeMap(void);
void freeMap(Room *map);

#endif // SPIRIT_ADVENTURE_MAP_H