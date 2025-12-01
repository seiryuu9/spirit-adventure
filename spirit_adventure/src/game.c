#include "../include/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int movePlayerInRoom(Player *player, Room *room, Direction dir) {
    int newX = player->x;
    int newY = player->y;

    switch (dir) {
        case NORTH: newY++; break;
        case SOUTH: newY--; break;
        case EAST:  newX++; break;
        case WEST:  newX--; break;
        default: return 0;
    }

    if (newX < 0 || newX >= room->width || newY < 0 || newY >= room->height) {
        printf("You hit a wall!\n");
        return 0;
    }

    player->x = newX;
    player->y = newY;

    return 1; // 0 on unsuccessful move, 1 on successful move
}

int movePlayerToRoom(Player *player, Room *map, Direction dir) {
    Room *currentRoom = &map[player->currentRoom];

    if (currentRoom->grid[player->y][player->x] == 'D') {
        for (int i = 0; i < currentRoom->doorCount; i++) { //looks for correct door
            Door *door = &currentRoom->doors[i];
            if (door->x == player->x && door->y == player->y) { //moves
                player->currentRoom = door->leadsTo;
                player->x = door->exitX;
                player->y = door->exitY;
                return 1;  // success
            }
        }
        return -1;  // error
    }
    return 0;  // no door at current position
}


void lookAround(Room *room) {
    NPC *npcArray[MAX_NPCS] = {NULL};
    Item *itemArray[MAX_ITEMS] = {NULL};
    Door *doorArray[MAX_DOORS] = {NULL};

    for (int i = 0; i < room->npcCount; i++) {
        NPC *npc = room->npcs[i];
        npcArray[i] = npc;
    }

    for (int i = 0; i < room->itemCount; i++) {
        Item *item = room->items[i];
        itemArray[i] = item;
    }

    for (int i = 0; i < room->doorCount; i++) {
        Door *door = &room->doors[i];
        doorArray[i] = door;
    }

    printf("You look around the %s.\n", room->name);
    if (room->npcCount > 0) {
        printf("You see some beings:\n ");
        for (int i = 0; i < room->npcCount; i++) {
            printf("%s at (%d, %d)\n", npcArray[i]->name, npcArray[i]->x, npcArray[i]->y);
        }
    }
    if (room->itemCount > 0) {
        printf("You notice some items on the floor:\n ");
        for (int i = 0; i < room->itemCount; i++) {
            printf("%s at (%d, %d)\n", itemArray[i]->name, itemArray[i]->x, itemArray[i]->y);
        }
    }
    if (room->doorCount > 0) {
        printf("There's doors leading somewhere:\n ");
        for (int i = 0; i < room->doorCount; i++) {
            char direction[6];
            if (doorArray[i]->dir == 0) {
                strcpy(direction, "NORTH");
            } else if (doorArray[i]->dir == 1) {
                strcpy(direction, "SOUTH");
            } else if (doorArray[i]->dir == 2) {
                strcpy(direction, "EAST");
            } else if (doorArray[i]->dir == 3) {
                strcpy(direction, "WEST");
            }
            printf("Door leading %s at (%d, %d)\n", direction, doorArray[i]->x, doorArray[i]->y);
        }
    }
}

void pickUpItem(Player *player, Room *room, Item *item) {
    if (room->grid[player->y][player->x] == 'I') {
        printf("You picked up %s.\n", item->name);
        addItemToInventory(player, item);
        room->grid[player->y][player->x] = ' ';
    }
}

void interactWithNPC(Player *player, NPC *npc, Room *room, InteractionType action) {
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
                // ADD THIS !!!
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
                // ADD THIS !!!
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
        if (strcmp(player->inventory[i]->name, itemName) == 0) {
            printf("You used the %s.\n", itemName);
            // effects?? for potion, possibly coin??
            return;
        }
    }
    printf("You don't have a %s in your inventory.\n", itemName);
}

void showCommands(void) {
    printf("Available commands:\n");
    //add
}

void fight(Player *player, NPC *npc, Room *room) {
    // turned based combat
}

void startGame(Player *player, Room *map) {
//??
}

void processCommand(Player *player, Room *map, const char *input) {
    // Implement command parsing logic
    // Call relevant functions based on player input
}