/**
  * \file menu.h
  * \brief the library containing all the functions related to the menus.
  * \author Alexandre Viala
  * \author Léonard Hesse
  * \date 13th june 2020
  *
  * The header of this library is included in every other libraries.
  * All the principals libraries of the c are included in this header.
  */
#ifndef MENUHEADER
#define MENUHEADER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include "Cartes.h"
/**
 * \enum Boolean
 * \brief a simple boolean implemented which can be useful in some cases
 */
typedef enum {
    TRUE = 0, /** value true */
    FALSE = 1 /** valu FALSE */
} Boolean;


/**
 * \struct bid
 * \brief the struct containing the bid of one player
 */
typedef struct {
    char* player; /** the in-game name of the player (south, north, etc.) */
    char* bet; /** the bet the player made ( could be  a number or "Capot" or "Coinche" etc. */
    char trump; /** the trump chosen by the player to bet*/
} bid;
/**
 * \struct biddings
 * \brief an array with his size containing all the bids made by all the players
 */
typedef struct {
    bid** bidding_array; /** array of pointer on bids */
    int turn;   /** size of the array */
} biddings;

/**
 * \fn void clrscr(void)
 * \brief function which erase all the things on the screen no matter the OS usedvoid clrscr()
 */
void clrscr(void);

/**
 * \fn char askForTrump(void)
 * \brief a function which ask the player to choose a trump during the bidding time
 * \return a char which is the chosen trump
 */
char askForTrump(void);
/**
 * \fn int menu(char** options, int nbre_option)
 * \brief a function displaying a menu with his title according to an array of strings
 * \param options - the array containing the options of the menu
 * \param nbre_option - number of options in the menu
 * \return an integer which is the option chosen (from 1 to nbre_option)
 */
int menu(char** options, int nbre_option);

/**
 * \fn int main_menu(void)
 * \brief a simple function which display the main menu and get the input of the player
 * \return the option chosen in the main menu
 */
int main_menu(void);


/**
 * \fn int bid_menu(int current_contract, biddings* struct_bid)
 * \brief display the menu of bidding and allow the player to make a bid
 * \param current_contract - the value of the current contract
 * \param struct_bid - the structure containing all the bets
 * \return an integer : -1 if no correct choice have been chosen, 0 if the player skipped, 1 if the player made a "classic" bet, 2 if the player made a coinche
 */
int bid_menu(int current_contract, biddings* struct_bid);

/**
 * \fn void menu_surcoinche(biddings* struct_bid)
 * \brief display the menu of surcoinche if someone made a coinche
 * \param struct_bid - the structure containing all the bets
 */
void menu_surcoinche(biddings* struct_bid);
/**
 * \fn void printBids(biddings b)
 * \brief a function useful to display a structure of type biddings
 * \param b - the structure to display
 */
void printBids(biddings b);


/**
 * \fn biddings* AddABet(biddings* b, char* GivenPlayer, int sizeGivenPlayer, char* GivenBet, int sizeGivenBet, char GivenTrump)
 * \brief A really significant function to add a bet inside a biddinngs struct
 * \param b - a pointer on the struct of type biddings we want to modify
 * \param GivenPlayer - the name of the player who made the bet
 * \param sizeGivenPlayer - the size of the string containing the name of the player
 * \param GivenBet - the bet that the player want to make inside a string
 * \param sizeGivenBet - the size of the string containing the bet
 * \param GivenTrump - the trump that the player chose ( can be 'H', 'C', 'D' or 'S')
 * \return the pointer on the struct b modified
 */
biddings* AddABet(biddings* b, char* GivenPlayer, int sizeGivenPlayer, char* GivenBet, int sizeGivenBet, char GivenTrump);
#endif // MENUHEADER
