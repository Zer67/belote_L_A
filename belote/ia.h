#ifndef IAHEADER
#define IAHEADER

#include "menu.h"



/* this struct is helping the ia to make a choice by stocking the possibilty she has */
typedef struct {
    int* valueWithTrump;
    char* color;
} choiceMaker;


typedef struct {
    char color;

    int scorewT; /* score possible if we choose this color in trump */
    char* figures; /* figures in the specified color, the values possibles for all these arrays are  : '7', '8','9', '1' for ten, 'J','Q' or 'K' */
    int counter;
    int nbrStg;
} Cardtype;

/** the function which allow the ai to make a bet.
 * @param ai_player - the struct which allows us to know which ai_player is playing
 * @param current_bet_value - the value of the current bet, by example a General have a value of 500
 * @param current_bet - the array containing all the bets already made
 */
int AIbid(Player* ai_player, int current_bet_value, biddings* current_bet);

Cardtype** BubbleSortChoice(Cardtype** array);

#endif // IAHEADER

