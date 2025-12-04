//headers are for struct, typedef, enum etc, c files are for logic

#ifndef SPIRIT_ADVENTURE_MAP_H
#define SPIRIT_ADVENTURE_MAP_H

#define MAX_ITEMS 2 //in one room on the ground
#define MAX_NPCS 2
#define ROOM_COUNT 6
#define MAX_DOORS 4
#define FINAL_ROOM_INDEX 5
#define MAX_WIDTH 4
#define MAX_HEIGHT 4

typedef enum { FRIENDLY, ENEMY, NEUTRAL } NPCType;

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef struct {
    const char *name;
    char *description;
    int x, y;
} Item;

typedef struct {
    const char *name;
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
    const char *name;
    char *description;
    int width;
    int height;
    char grid[MAX_WIDTH][MAX_HEIGHT]; // ' ' = empty, 'D' = door, 'N' = npc, 'I' = item
    Item *items[MAX_ITEMS];
    int itemCount;
    NPC *npcs[MAX_NPCS];
    int npcCount;
    Door doors[MAX_DOORS];
    int doorCount;
} Room;


Room *initializeMap(void);
void freeMap(Room *map);
void removeItemFromRoom(Room *room, Item *item);
void removeNPCFromRoom(Room *room, NPC *npc);
void addItem(Room *room, const char *name, int x, int y);
void addNpc(Room *room, const char *name, NPCType type, int health, int x, int y, Item *reward);
void addDoor(Room *room, Direction dir, int leadsTo, int x, int y, int exitX, int exitY); // being in header makes then accessible to other files
Item *getItemAt(Room *room, int x, int y);
NPC *getNPCAt(Room *room, int x, int y);

#endif // SPIRIT_ADVENTURE_MAP_H