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
/**
 * @param options - the array containing the options of the menu
 * @param nbre_option - number of options in the menu
 * @return an integer which is the option chosen (from 1 to nbre_option)
 */
int menu(char** options, int nbre_option);

/**
 * @return the option chosen in the main menu
 */
int main_menu();
#endif // MENUHEADER
