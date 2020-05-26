#ifndef IAHEADER
#define IAHEADER

#include "menu.h"



/* this struct is helping the ia to make a choice by stocking the possibilty she has */
typedef struct {
    int* valueWithTrump;
    char* color;
    /* arrays containing the figure in a certain color */
    char* FigureInH;
    char* FigureInD;
    char* FigureInS;
    char* FigureInC;
    /* score possible with the actual hand if the player is alone and he win all the trick */
    int scorewH;
    int scorewS;
    int scorewD;
    int scorewC;

} choiceMaker;


typedef struct {
    char color;

    int scorewT; /* score possible if we choose this color in trump */
    char* figures; /* figures in the specified color, the values possibles for all these arrays are  : '7', '8','9', '1' for ten, 'J','Q' or 'K' */
    int counter;
    int nbrStg;
} Cardtype;

biddings* AIbid(Player* ai_player, int current_bet_value, biddings* current_bet);

Cardtype** BubbleSortChoice(Cardtype** array);

#endif // IAHEADER

