#ifndef SPIRIT_ADVENTURE_SAVE_H
#define SPIRIT_ADVENTURE_SAVE_H

#include "player.h"
#include "map.h"

// saves the entire game state to a file
int saveGame(const char *filename, Player *player, Room *map, int roomCount);

// loads the entire game state from a file
int loadGame(const char *filename, Player *player, Room *map, int roomCount);

#endif // SPIRIT_ADVENTURE_SAVE_H

//revise ??? where does it save ???
