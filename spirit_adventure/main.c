#include <stdio.h>
#include <string.h>
#include "player.h"
#include "map.h"
#include "save.h"
#include "game.h"

int main(int argc, char **argv) {
    Room *map = NULL;
    Player *player = NULL;

    if (argc != 3) {
        printf("Usage:\n");
        printf("  adv -n <name>   Start new game\n");
        printf("  adv -l <name>   Load saved game\n");
        return 1;
    }

    // load/create map
    map = initializeMap();

    if (strcmp(argv[1], "-n") == 0) {
        // create new player
        player = createPlayer(argv[2]);
        printf("Starting a new game for %s...\n", player->name);
    }
    else if (strcmp(argv[1], "-l") == 0) {
        // create placeholder player, meno sa prepíše pri load
        player = createPlayer("placeholder");

        char filename[64];
        snprintf(filename, sizeof(filename), "%s.dat", argv[2]);

        if (!loadGame(filename, player, map)) {
            printf("Save file not found. Cannot load game.\n");
            return 1;
        }

        printf("Loaded game for %s.\n", player->name);
    }
    else {
        printf("Unknown option %s\n", argv[1]);
        return 1;
    }

    // start game loop
    startGame(player, map);

    // save on exit
    char savefile[64];
    snprintf(savefile, sizeof(savefile), "%s.dat", player->name);
    saveGame(savefile, player, map);

    printf("Game saved to %s.\n", savefile);
    return 0;
}
