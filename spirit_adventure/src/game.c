#include "../include/game.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dragonHornCount = 0;
int enemiesDefeated = 0;
int maskCount = 0;

int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
} // for random dmg

void enterFinalRoom(Player *player) {
    printf("\nYou step into the inner sanctum. A majestic cherry blossom tree stands in the middle. A stone path leads to it, dimly lit by several torches and buzzing fireflies.\n");
    printf("As you approach the tree, you notice something in front of the tree. Or someone? Suddenly, you can't move and the next thing you know, a deep voice echoes in your mind.\n");
    printf("The voice, you assume, belongs to the spirit of the tree.\n");
    printf("\"I see you have finally reached the end of your journey, mortal. But tell me, what is it that you truly seek? Have you done what you truly believe in? Were you brave? Or were you foolish?\"\n");
    printf("You feel a chill run down your spine, but you take a step forward, kneel before the spirit and wait for your judgement.\n");
    if (maskCount == 4 && enemiesDefeated == 0) {
        printf("A gentle voice responds. \"So, you chose the path of mercy and compassion, did you? You were very brave and chose the harder way - even if it doesn't always seem that way. Very well, mortal.\"\n");
        printf("\"Remember, true strength lies not in power, but in kindness and understanding. Use this gift wisely, for it can heal even the deepest wounds but it can also be sly.\"\n");
        printf("The tree spirit flies into your chest. You feel a warm light enveloping you. You have obtained the Fox soul!\n");
        printf("Farewell, %s...", player->name);
    } else if (dragonHornCount == 4 && enemiesDefeated == 5) {
        printf("A different voice chuckles darkly. \"So, you chose the path of strength and ruthlessness, did you? Very well, mortal.\"\n");
        printf("\"Be careful, don't let the power consume you. The dragon spirit is not to be trifled with. Use its power wisely, for it can bring both great strength and great destruction.\"\n");
        printf("The tree spirit flies into your chest. You feel a surge of power coursing through your veins. You have obtained the Dragon soul!\n");
        printf("Farewell, %s...", player->name);
    } else {
        printf("The spirit sighs deeply. \"You have tried but I can feel your heart still sways, mortal. You have not proven yourself worthy of the gift you seek.\"\n");
        printf("A strong shudder passes through your body. \"I can sense the potential within you, but without true conviction, it is wasted. Return when you have found your true path.\"\n");
        printf("You were banished.");
    }
    exit(0);
}

void movePlayerInRoom(Player *player, Room *map, Direction dir) {
    Room *room = &map[player->currentRoom];
    int newX = player->x;
    int newY = player->y;
    int oldX = player->x;
    int oldY = player->y;

    switch (dir) {
        case NORTH: newY++; break;
        case SOUTH: newY--; break;
        case EAST:  newX++; break;
        case WEST:  newX--; break;
        default: return;
    }

    if (newX < 0 || newX >= room->width || newY < 0 || newY >= room->height) {
        printf("You hit a wall!\n");
        return;
    }

    char choice;
    char choiceLong[6];

    player->x = newX;
    player->y = newY;

    if (room->grid[newY][newX] == ' ') {
        printf("You moved to (%d, %d).\n", player->x, player->y);
    } else if (room->grid[newY][newX] == 'D') {
        printf("You are at a door at (%d, %d).\n", player->x, player->y);
        printf("Do you want to enter? (Y/N)\n");
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y') {
            movePlayerToRoom(player, room);
        } else if (choice == 'N' || choice == 'n') {
            printf("You decided not to enter the door and step back to (%d, %d).\n", oldX, oldY);
            player->x = oldX;
            player->y = oldY;
        }

    } else if (room->grid[newY][newX] == 'N') {
        NPC *npc = getNPCAt(room, player->x, player->y);

        printf("You see an NPC at (%d, %d).\n", player->x, player->y);
        printf("Do you want to interact? (Y/N)\n");
        scanf(" %c", &choice);
        if (choice == 'N' || choice == 'n') {
            printf("You decided not to interact with the NPC.\n");
            printf("You move back to (%d, %d).\n", oldX, oldY);
            player->x = oldX;
            player->y = oldY;
        } else if (choice == 'Y' || choice == 'y') {
            printf("Do you wish to TALK or FIGHT?\n");
            scanf("%5s", choiceLong); //reads only 5 chars to avoid overflow
            for (int i = 0; choiceLong[i]; i++) {
                choiceLong[i] = tolower(choiceLong[i]);
            }
            if (strcmp(choiceLong, "talk") == 0) {
                interactWithNPC(player, npc, room, INTERACT_TALK);
            } else if (strcmp(choiceLong, "fight") == 0) {
                interactWithNPC(player, npc, room, INTERACT_FIGHT);
            }
        }

    } else if (room->grid[newY][newX] == 'I') {
        printf("You see an item on the floor at (%d, %d).\n", player->x, player->y);
        printf("Do you want to pick it up? (Y/N)\n");
        scanf(" %c", &choice);
        if (choice == 'N' || choice == 'n') {
            printf("You decided not to pick up the item.\n");
            printf("You move back to (%d, %d).\n", oldX, oldY);
            player->x = oldX;
            player->y = oldY;
        } else if (choice == 'Y' || choice == 'y') {
            printf("You picked up the item.\n");
            Item *item = getItemAt(room, player->x, player->y);
            if (item) {
                pickUpItem(player, room, item);
            }
        }
    }

}

void movePlayerToRoom(Player *player, Room *map) {
    Room *currentRoom = &map[player->currentRoom];

    if (currentRoom->grid[player->y][player->x] == 'D') {
        for (int i = 0; i < currentRoom->doorCount; i++) { //looks for correct door
            Door *door = &currentRoom->doors[i];
            if (door->x == player->x && door->y == player->y) { //moves
                player->currentRoom = door->leadsTo;
                player->x = door->exitX;
                player->y = door->exitY;
                printf("%s", currentRoom->description);

                if (player->currentRoom == FINAL_ROOM_INDEX) {
                    enterFinalRoom(player);
                }
                return;
            }
        }
    }
}

void lookAround(Room *room) {

    printf("You look around the %s.\n", room->name);
    if (room->npcCount > 0) {
        printf("You see some beings:\n ");
        for (int i = 0; i < room->npcCount; i++) {
            NPC *npc = room->npcs[i];
            printf("%s at (%d, %d)\n", npc->name, npc->x, npc->y);
        }
    }
    if (room->itemCount > 0) {
        printf("You notice some items on the floor:\n ");
        for (int i = 0; i < room->itemCount; i++) {
            Item *item = room->items[i];
            printf("%s at (%d, %d)\n", item->name, item->x, item->y);
        }
    }
    if (room->doorCount > 0) {
        printf("There's doors leading somewhere:\n ");
        for (int i = 0; i < room->doorCount; i++) {
            Door *door = &room->doors[i];
            printf("Door at (%d, %d)\n", door->x, door->y);
        }
    }
}

void spawnGoldenCoinIfNeeded(Player *player, Room *map) {
    Room *firstRoom = &map[0];

    // counts the mask parts
    maskCount = 0;
    for (int i = 0; i < player->inventoryCount; i++) {
        if (strcmp(player->inventory[i]->name, "Fox Mask Part") == 0) {
            maskCount++;
        }
    }

    // if less than 4, do nothing
    if (maskCount < 4) {
        return;
    }

    getNPCAt(firstRoom, 2, 1)->type = ENEMY;

    if (rand() % 2 != 0) {
        return; // 50% chance nothing happens
    }

    // checks if it already exists
    for (int i = 0; i < firstRoom->itemCount; i++) {
        if (strcmp(firstRoom->items[i]->name, "Golden Coin") == 0) {
            return;
        }
    }

    addItem(firstRoom, "Golden coin", 1, 1);
    firstRoom->grid[1][1] = 'I';

    printf("\nYou hear the rustle of leaves. Something important appeared somewhere. Maybe worth checking the place where your journey began?\n");
}

void checkDragon(Player *player, Room *map) {
    dragonHornCount = 0;
    for (int i = 0; i < player->inventoryCount; i++) {
        if (strcmp(player->inventory[i]->name, "Dragon horn") == 0) {
            dragonHornCount++;
        }
    }

    if (dragonHornCount >= 4 && enemiesDefeated >= 4) {
        getNPCAt(&map[0], 2, 1)->type = ENEMY;

    }
}

void pickUpItem(Player *player, Room *map, Item *item) {
    Room *room = &map[player->currentRoom];

    if (room->grid[player->y][player->x] == 'I') {
        printf("You picked up %s.\n", item->name);
        addItemToInventory(player, item);
        removeItemFromRoom(room, item);
        room->grid[player->y][player->x] = ' ';
    }

    spawnGoldenCoinIfNeeded(player, map);
    checkDragon(player, map);
}

void interactWithNPC(Player *player, NPC *npc, Room *map, InteractionType action) {
    Room *room = &map[player->currentRoom];

    if (room->grid[player->y][player->x] == 'N') {
        if (strcmp(npc->name, "Mysterious monk") == 0) {
            if (action == INTERACT_TALK) {
                printf("You come up to the monk and bow respectfully. He nods in return and says, \"Peace be with you, traveler.\"\n");
                printf("The monk offers you a healing potion as a token of goodwill. Do you take it? (Y/N)\n");
                char choice;
                scanf(" %c", &choice);
                if (choice == 'Y' || choice == 'y') {
                    Item *potion = malloc(sizeof(Item));
                    potion->name = "Healing Potion";
                    addItemToInventory(player, potion);
                    printf("You received a Healing Potion!\n");
                    printf("You bow and turn to leave, but the monk suddenly grabs your arm. \"And remember. Use it before your biggest foe, otherwise there's no guarantee what fate will befall you.\"\n");
                } else {
                    printf("You decline the monk's offer. He just shrugs.\n");
                }
                printf("Before you leave, the monk offers to tell you more about this place. Would you like to hear it? (Y/N)\n");
                scanf(" %c", &choice);
                if (choice == 'Y' || choice == 'y') {
                    printf("\"You have fallen into this place because your soul seeks something. Only by overcoming the challenges here can you find what you truly desire.\n");
                    printf("Will you be ruthless but strong and level-headed, or face the weakness within you and offer mercy to those you meet? The choice is yours, but remember, every action has its consequences.\"\n");
                    printf("You feel something tug at your soul. You distantly hear the flapping of wings and feel something fluffy brush your legs. When you look down, nothing's there.");
                    printf("\"But be careful. Should you try to please everyone, you may end up pleasing no one - not even yourself.\"\n");
                } else {
                    printf("The monk doesn't say anything else and let's you leave.\n");
                }
            } else if (action == INTERACT_FIGHT) {
                printf("You cannot fight them.\n");
            } else if (action == DONT_INTERACT) {
                printf("You chose not to interact with %s.\n", npc->name);
            }


        } else if (strcmp(npc->name, "Wandering spirit") == 0 && npc->type == NEUTRAL) {
            if (action == INTERACT_FIGHT || action == INTERACT_TALK) {
                printf("They don't seem to notice you.");
            }  else if (action == DONT_INTERACT) {
                printf("You chose not to interact with %s.\n", npc->name);
            }

        } else if (strcmp(npc->name, "Wandering spirit") == 0 && npc->type == ENEMY) {
            if (action == INTERACT_FIGHT) {
                fight(player, npc, room);
                room->grid[npc->y][npc->x] = 'D';
                printf("You feel exhausted but know your goal is near. You step through the door.\n");
                movePlayerToRoom(player, room);
            } else if (action == INTERACT_TALK) {
               printf("\"What is it that you seek, mortal? You seem hesitant to fight me, yet you know I am an obstacle in your path.\"\n");
                if (playerHasItem(player, "Golden Coin")) {
                    printf("You suddenly remember the golden coin you found earlier. Would you like to offer it? (Y/N).\n");
                    char choice;
                    scanf(" %c", &choice);
                    if (choice == 'Y' || choice == 'y') {
                        printf("You offer the golden coin to the spirit. It takes the coin and without another word, it vanishes into thin air.\n");
                        printf("\"Thank you, kind stranger.\" You hear faintly as it departs.\n");
                        removeItemFromInventory(player, "Golden Coin");
                        room->grid[player->y][player->x] = 'D'; // enables door
                        printf("Without further hesitation, you step through the door.\n");
                        movePlayerToRoom(player, room);
                    } else {
                        printf("You decide not to offer the coin. The spirit looks disappointed.\n");
                    }
                } else {
                    printf("The spirit eyes you menacingly. \"You have nothing of value to offer me. Now leave.\"\n");
                }
            } else if (action == DONT_INTERACT) {
                printf("You chose not to interact with %s.\n", npc->name);
            }


        } else if (strcmp(npc->name, "Hostile spirit") == 0 || strcmp(npc->name, "Shiny hostile spirit") == 0) {
            if (action == INTERACT_FIGHT) {
                fight(player, npc, room);
            } else if (action == INTERACT_TALK) {
                printf("%s looks at you menacingly. You can't get a word out.\n", npc->name);
            } else if (action == DONT_INTERACT) {
                printf("You wisely chose not to interact with %s.\n", npc->name);
            }
        }
    }
}

void showInventory(Player *player) {
    printf("Your health is: %d\n", player->health);
    if (player->inventoryCount == 0) {
        printf("Your inventory is empty.\n");
    } else {
        printf("Your inventory contains:\n");
        for (int i = 0; i < player->inventoryCount; i++) {
            printf("- %s\n", player->inventory[i]->name);
        }
    }
}

void useItem(Player *player, char *itemName) {
    for (int i = 0; i < player->inventoryCount; i++) {
        if (strcmp(itemName, "Healing Potion") == 0) {
            printf("You used the %s.\n", itemName);
            if (enemiesDefeated == 4) {
                player->health = 200;
            } else {
                player->health = PLAYER_MAX_HEALTH;
            }
            printf("Your health is now %d HP.\n", player->health);
            removeItemFromInventory(player, itemName);
            return;
        }
    }
    printf("You don't have a %s in your inventory.\n", itemName);
}

void showCommands(void) {
    printf("Available commands:\n");
    printf("- north, south, east, west: Move in the specified direction.\n");
    printf("- look around, info: Get information about the current room.\n");
    printf("- inventory: Show your current inventory and health.\n");
    printf("- use <item name>: Use an item from your inventory.\n");
    printf("- help, commands: Show this list of commands.\n");
    printf("- quit: Exit the game.\n");
}

void fight(Player *player, NPC *npc, Room *map) {
    printf("You engage in combat with %s!\n", npc->name);

    printf("%s has %d HP.\n", npc->name, npc->health);
    printf("You have %d HP.\n", player->health);

    int enemyMinDmg = 0;
    int enemyMaxDmg = 0;

    if (strcmp(npc->name, "Hostile spirit") == 0) {
        enemyMinDmg = 1;
        enemyMaxDmg = 20;
    }
    else if (strcmp(npc->name, "Shiny hostile spirit") == 0) {
        enemyMinDmg = 1;
        enemyMaxDmg = 25;
    }
    else if (strcmp(npc->name, "Wandering spirit") == 0 && npc->type == ENEMY) {
        enemyMinDmg = 1;
        enemyMaxDmg = 50;
    }

    // turn based loop
    while (player->health > 0 && npc->health > 0) {

        printf("\nYour turn:\n");

        int playerDmg = randomInRange(25, 50);
        npc->health -= playerDmg;

        printf("You strike %s for %d damage! (Enemy HP: %d)\n", npc->name, playerDmg, npc->health);

        if (npc->health <= 0) {
            printf("\nYou defeated %s!\n", npc->name);
            enemiesDefeated++;
            if (npc->reward) {
                printf("He dropped %s!\n", npc->reward->name);
                addItemToInventory(player, npc->reward);
                npc->reward = NULL; // the npc doesnt own it so it does get double freed
            }
            map->grid[npc->y][npc->x] = ' ';
            removeNPCFromRoom(map, npc);
            checkDragon(player, map);
            return;
        }

        printf("\nEnemy turn:\n");

        int enemyDmg = randomInRange(enemyMinDmg, enemyMaxDmg);
        player->health -= enemyDmg;

        printf("%s hits you for %d damage! (Your HP: %d)\n",
               npc->name, enemyDmg, player->health);

        if (player->health <= 0) {
            printf("\nYou have fallen in battle.\n");
            printf("GAME OVER\n");
        }
    }
}

void startGame(Player *player, Room *map) {
    char input[100]; // buffer for player input

    printf("Welcome, %s!\n", player->name);
    Room *currentRoom = &map[player->currentRoom];
    printf("%s\n", currentRoom->description);
    lookAround(currentRoom);
    showCommands();


    while (1) { // main game loop
        printf("\nEnter command: ");
        if (!fgets(input, sizeof(input), stdin)) {
            continue; // tries again if failed
        }

        // deletes \n
        input[strcspn(input, "\n")] = 0;

        // process command
        processCommand(player, map, input);

        // ends game if
        if (player->health <= 0) {
            printf("You have died. Game over.\n");
            break;
        }
    }
}

void processCommand(Player *player, Room *map, const char *input) {
    // makes all lowercase
    char cmd[100];
    int i = 0;
    for (; input[i] && i < 99; i++) {
        cmd[i] = tolower(input[i]);
    }
    cmd[i] = '\0';

    // movement
    if (strcmp(cmd, "north") == 0) {
        movePlayerInRoom(player, map, NORTH);
    } else if (strcmp(cmd, "south") == 0) {
        movePlayerInRoom(player, map, SOUTH);
    } else if (strcmp(cmd, "east") == 0) {
        movePlayerInRoom(player, map, EAST);
    } else if (strcmp(cmd, "west") == 0) {
        movePlayerInRoom(player, map, WEST);
    }
    // inventory + health
    else if (strcmp(cmd, "inventory") == 0) {
        showInventory(player);
    }
    // use item
    else if (strncmp(cmd, "use ", 4) == 0) {
        useItem(player, cmd + 4); // skips "use "
    }
    // look around
    else if ((strcmp(cmd, "info") == 0) || strcmp(cmd, "look around") == 0 ){
        lookAround(&map[player->currentRoom]);
    }
    // help /commands
    else if (strcmp(cmd, "help") == 0 || strcmp(cmd, "commands") == 0) {
        showCommands();
    }
    // quits game
    else if (strcmp(cmd, "quit") == 0) {
        printf("Thanks for playing!\n");
        exit(0);
    }
    else {
        printf("Unknown command. Type 'help' to see available commands.\n");
    }
}


