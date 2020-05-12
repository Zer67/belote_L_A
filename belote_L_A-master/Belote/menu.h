#ifndef MENUHEADER
#define MENUHEADER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

typedef enum {
    True = 1,
    False = 0
} Boolean;

/** function which erase all the things on the screen no matter the OS usedvoid clrscr()
 */
void clrscr();

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
void bid_menu();
#endif // MENUHEADER
