#ifndef MENUHEADER
#define MENUHEADER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include "Cartes.h"

typedef enum {
    True = 0,
    False = 1
} Boolean;



typedef struct {
    char* player;
    char* bet;
    char trump;
} bid;

typedef struct {
    bid** bidding_array;
    int turn;
} biddings;

/** function which erase all the things on the screen no matter the OS usedvoid clrscr()
 */
void clrscr();

/** a function which ask the player to choose a trump during the bidding time
 * @param title - the title of the menu to make the interface more a e s t h e t i c
 * @return a char which is the chosen trump
 */
char askForTrump(char* title);
/**
 * @param options - the array containing the options of the menu
 * @param nbre_option - number of options in the menu
 * @return an integer which is the option chosen (from 1 to nbre_option)
 */
int menu(char** options, int nbre_option);

/** a simple function which display the main menu and get the input of the player
 * @return the option chosen in the main menu
 */
int main_menu();
/** display the interface with the cards
 * @return the option chosen by the user
 */

/** display the menu of bidding
 */
int bid_menu(int current_contract, biddings* struct_bid);

void menu_surcoinche(biddings* struct_bid);

void printBids(biddings b);

biddings* AddABet(biddings* b, char* GivenPlayer, int sizeGivenPlayer, char* GivenBet, int sizeGivenBet, char GivenTrump);
#endif // MENUHEADER
