#ifndef AIHEADER
#define AIHEADER

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

/**these  functions will allow the artificial player to play one card in a trick
@param Player - the struct of the artificial player
@param turn - it is two things : the number of turns it remains to do, and the size-1 (or the index of the last card) of the player's hand.
@param Card_in_theTrick - the index of the last card of the actual trick
@param TheTrick - the struct that will contain the cards of the trick
@param trump_color - the color of the trump
*/
void Game_of_AI(Player* Player, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color);

Cardtype** BubbleSortChoice(Cardtype** array);

#endif // IAHEADER

