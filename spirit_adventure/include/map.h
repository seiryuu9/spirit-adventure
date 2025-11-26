//headers are for struct, typedef, enum etc, c files are for logic

#ifndef SPIRIT_ADVENTURE_MAP_H
#define SPIRIT_ADVENTURE_MAP_H

#define MAX_ITEMS 2 //in one room on the ground
#define MAX_NPCS 2
#define ROOM_COUNT 6
#define MAX_DOORS 4

typedef enum { FRIENDLY, ENEMY, NEUTRAL } NPCType;

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

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
    Direction dir;    // direction which door leads to
    int leadsTo;      // index of room where the door leads
    int x, y;         // current door position
    int exitX, exitY; // position in the room it leads to
} Door;

typedef struct {
    char *name;
    char *description;
    int width;
    int height;
    char **grid; // ' ' = empty, 'D' = door, 'N' = npc, 'I' = item (dynamic 2D array)
    Item *items[MAX_ITEMS];
    int itemCount;
    NPC *npcs[MAX_NPCS];
    int npcCount;
    Door doors[MAX_DOORS];
    int doorCount;
} Room;


Room *initializeMap(void);
void freeMap(Room *map);

#endif // SPIRIT_ADVENTURE_MAP_H