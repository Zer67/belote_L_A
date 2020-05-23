#ifndef IAHEADER
#define IAHEADER

#include "menu.h"

/* this struct is helping the ia to make a choice by stocking the possibilty she has */
typedef struct {
    int* valueWithTrump;
    char* color;
    /* score possible with the actual hand if the player is alone and he win all the trick */
    int scorewH;
    int scorewS;
    int scorewD;
    int scorewC;

} choiceMaker;

void AIbid(Player* ai_player, int current_bet);

#endif // IAHEADER
