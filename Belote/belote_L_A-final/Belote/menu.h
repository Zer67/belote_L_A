#ifndef MENUHEADER
#define MENUHEADER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include "Cartes.h"

typedef enum {
    TRUE = 0,
    FALSE = 1
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
void clrscr(void);

/** a function which ask the player to choose a trump during the bidding time
 * @return a char which is the chosen trump
 */
char askForTrump(void);
/**
 * @param options - the array containing the options of the menu
 * @param nbre_option - number of options in the menu
 * @return an integer which is the option chosen (from 1 to nbre_option)
 */
int menu(char** options, int nbre_option);

/** a simple function which display the main menu and get the input of the player
 * @return the option chosen in the main menu
 */
int main_menu(void);


/** display the menu of bidding and allow the player to make a bid
 * @param current_contract - the value of the current contract
 * @param struct_bid - the structure containing all the bets
 * @return an integer : -1 if no correct choice have been chosen, 0 if the player skipped, 1 if the player made a "classic" bet, 2 if the player made a coinche
 */
int bid_menu(int current_contract, biddings* struct_bid);

/** display the menu of surcoinche if someone made a coinche
 * @param struct_bid - the structure containing all the bets
 */
void menu_surcoinche(biddings* struct_bid);
/** a function useful to display a structure of type biddings
 * @param b - the structure to display
 */
void printBids(biddings b);


/** A really significant function to add a bet inside a biddinngs struct
 * @param b - a pointer on the struct of type biddings we want to modify
 * @param GivenPlayer - the name of the player who made the bet
 * @param sizeGivenPlayer - the size of the string containing the name of the player
 * @param GivenBet - the bet that the player want to make inside a string
 * @param sizeGivenBet - the size of the string containing the bet
 * @param GivenTrump - the trump that the player chose ( can be 'H', 'C', 'D' or 'S')
 * @return the pointer on the struct b modified
 */
biddings* AddABet(biddings* b, char* GivenPlayer, int sizeGivenPlayer, char* GivenBet, int sizeGivenBet, char GivenTrump);
#endif // MENUHEADER
