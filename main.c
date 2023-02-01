
/* --------------------------------------------------- */
/* HEADERS AND CONSTANTS                               */
/* --------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Game.h"

#define LINE_MAX 128

Game game;

/* --------------------------------------------------- */
/* FUNCTIONS                                           */
/* --------------------------------------------------- */

void Describe(int location)
{
    Location *pLocation;

    pLocation = &game.map[location];

    printf("------------------------------------------\n");
    printf("Player Location: %s\n", pLocation->name);
    printf("\n");
    printf("Location Description: %s\n", pLocation->description);

    for (int i = 0; i < pLocation->items.itemCount; i++)
    {
        int itemNumber;
        itemNumber = pLocation->items.items[i];
        printf("There is a %s here\n", game.items[itemNumber].name);
    }
    printf("------------------------------------------\n");
    printf("> ");
}
int GetUserInput(char *aline, int maxLine) 
{
    fgets(aline, maxLine, stdin);
    if (strlen(aline) > 0)
    {
        aline[strlen(aline) - 1] = '\0';
    }
    return strlen(aline);
}
void ParseUserInput(char *aline)
{
    char *verb;
    char *noun;
    Location *pLocation;

    pLocation = &game.map[game.player.Locations];

    verb = strtok(aline, " ");
    noun = strtok(NULL, " ");


    if (verb != NULL)
    {
        switch (verb[0])
        {
        case 'n':
        case 'N':
            if (game.map[game.player.Locations].north == -1)
            {
                printf("You can't go that way.\n\n");
            }
            else
            {
                game.player.Locations = game.map[game.player.Locations].north;
            }
            break;
        case 'e':
        case 'E':
            if (game.map[game.player.Locations].east == -1)
            {
                printf("You can't go that way.\n\n");
            }
            else
            {
                game.player.Locations = game.map[game.player.Locations].east;
            }
            break;
        case 's':
        case 'S':
            if (game.map[game.player.Locations].south == -1)
            {
                printf("You can't go that way.\n\n");
            }
            else
            {
                game.player.Locations = game.map[game.player.Locations].south;
            }
            break;
        case 'w':
        case 'W':
            if (game.map[game.player.Locations].west == -1)
            {
                printf("You can't go that way.\n\n");
            }
            else
            {
                game.player.Locations = game.map[game.player.Locations].west;
            }
            break;
        case 'g': ;
        case 'G': ;

            if (noun == NULL)
            {
            printf("INVALID INPUT!\n");
            }
            else
            {
            int itemNumber;

            itemNumber = ItemGetItemNumber(game.items, game.itemCount, noun);
            if (itemNumber == -1)
            {
                printf("====%s IS NOT FOUND!====\n", noun);
            }
            else
            {
                //add item to player
                PlayerAddItem(&game.player, itemNumber);
                printf("\nYOU GOT THE %s!\n", noun);

                //remove object from location
                if (LocationHasItem(pLocation, itemNumber) != 0)
                {
                    LocationRemoveItem(pLocation, itemNumber);
                }
            }
            }
            break;
        case 'd': ;
        case 'D': ;

            if (noun == NULL)
            {
            printf("INVALID INPUT!\n");
            }
            else
            {

            int itemNumber2;

            itemNumber2 = ItemGetItemNumber(game.items, game.itemCount, noun);
            if (itemNumber2 == -1)
            {
                printf("====%s IS NOT FOUND!====\n", noun);
            }
            else
            {
                if (PlayerHasItem(&game.player, itemNumber2) != 0)
                {
                    PlayerRemoveItem(&game.player, itemNumber2);
                    printf("%s HAS BEEN REMOVED FROM INVENTORY\n", noun);
                    LocationAddItem(pLocation, itemNumber2);
                }
                else
                {
                    printf("====YOU DO NOT HAVE %s!====\n", noun);
                }
            }
            }
            break;
        case 'i': ;
        case 'I': ;

            if (game.player.items.itemCount != 0)
                {
                    printf("========= YOU ARE CARRYING: =========\n");
                    for (int j = 0; j < game.player.items.itemCount; j++)
                    {
                        int playerItems;
                        playerItems = game.player.items.items[j];
                        printf("Item %d:     %s\n", j, game.items[playerItems].name);
                    }
                    printf("=====================================\n");
                }
            else
            {
                printf("========= INVENTORY IS EMPTY! =========\n\n");
            }

            break;
        case 'l': ;
        case 'L': ;
            Describe(game.player.Locations);
            break;
        
        }
    }
}

/* --------------------------------------------------- */
/* MAIN                                                */
/* --------------------------------------------------- */

int main()
{

    char input[LINE_MAX];

    GameInitialize(&game);

    printf("\n===========================================\n");
    printf("WELCOME TO THE GAME!\n");
    printf("===========================================\n\n");
    printf("INSTRUCTIONS: GET ALL ITEMS!                \n\n");
    printf("===========================================\n");
    printf("CHARACTER         DESCRIPTION\n");
    printf("-----------------------------\n");
    printf("n, N              North: Go North\n");
    printf("e, E              East: Go East\n");
    printf("s, S              South: Go South\n");
    printf("w, W              West: Go West\n");
    printf("g, G              Get <item>: Gets Item from Location. TYPE ITEM\'S NAME IN QUOTES!\n");
    printf("d, D              Drop <item>: Drops Item from Location. TYPE ITEM\'S NAME IN QUOTES!\n");
    printf("i, I              Inventory: Lists Items Carried\n");
    printf("l, L              Look: Describes your Current Location\n");
    printf("------------------------------\n\n\n");



    while(game.player.items.itemCount < 6)
    {
        Describe(game.player.Locations);
        GetUserInput(input, LINE_MAX);
        ParseUserInput(input);
    }

    printf("\n\n==================================================\n");
    printf("YOU GOT ALL OF THE ITEMS!!!! CONGRATULATIONS!!\n");
    printf("==================================================\n");
}   
