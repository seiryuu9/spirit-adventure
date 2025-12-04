#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "player.h"
#include "map.h"
#include "save.h"
#include "game.h"

int main(int argc, char **argv) {
    srand(time(NULL)); // ensures different random numbers each run

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
        // create new player and input name
        char name[50];

        strncpy(name, argv[2], sizeof(name) - 1); // copies the name from command line
        name[sizeof(name) - 1] = '\0';

        //overwriting if name is alrd taken
        char savefile[64];
        snprintf(savefile, sizeof(savefile), "%s.save", name);
        FILE *f_check = fopen(savefile, "rb");
        if (f_check) {
            fclose(f_check);

            printf("A save for '%s' already exists. Overwrite and start new game? (Y/N): ", name);

            char input[6];
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            if (strcmp(input, "N") == 0 || strcmp(input, "n") == 0) {
                printf("New game canceled.\n");
                return 0;
            } else if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) {
                printf("Overwriting existing save for '%s'.\n", name);
            }
        }

        player = createPlayer(name);
        printf("Starting a new game for %s...\n", player->name);
    }
    else if (strcmp(argv[1], "-l") == 0) {
         // create placeholder player so we can run loadGame function, then overwrite with loaded data
        player = createPlayer("placeholder");

        char filename[64];
        snprintf(filename, sizeof(filename), "%s.save", argv[2]); // creates filename in the buffer, name.save and ensures buffer overflow doesn't happen

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
    snprintf(savefile, sizeof(savefile), "%s.save", player->name);
    saveGame(savefile, player, map);

    printf("Game saved to %s.\n", savefile);
    return 0;
}