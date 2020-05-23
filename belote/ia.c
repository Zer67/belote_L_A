#include "ia.h"

void AIbid(Player* ai_player, int current_bet){
    int strongCards =0; /* number of strong cards with a given trump */

    choiceMaker* choice = (choiceMaker*) malloc(sizeof(choiceMaker));
    choice->valueWithTrump = (int*) malloc(sizeof(int)*8);
    choice->color = (char*) malloc(sizeof(char)*8);
    choice->scorewH = 0, choice->scorewS = 0, choice->scorewD = 0, choice->scorewC = 0;

    for (int i = 0; i<8;i++){
        switch(ai_player->hand[i].color[4]){
            case ('J'):
                choice->valueWithTrump[i] = 20;
                break;
            case ('9'):
                choice->valueWithTrump[i] = 14;
                break;
            default:
                choice->valueWithTrump[i] = ai_player->hand[i].point;
        }
        choice->color[i]= ai_player->hand[i].color[4];
        switch(ai_player->hand[i].color[0]){
            case ('H'):
                choice->scorewH += choice->valueWithTrump[i];
                choice->scorewS += ai_player->hand[i].point;
                choice->scorewD += ai_player->hand[i].point;
                choice->scorewC += ai_player->hand[i].point;
                break;
            case ('S'):
                choice->scorewS += choice->valueWithTrump[i];
                choice->scorewH += ai_player->hand[i].point;
                choice->scorewD += ai_player->hand[i].point;
                choice->scorewC += ai_player->hand[i].point;
                break;
            case ('D'):
                choice->scorewD += choice->valueWithTrump[i];
                choice->scorewS += ai_player->hand[i].point;
                choice->scorewH += ai_player->hand[i].point;
                choice->scorewC += ai_player->hand[i].point;
                break;
            default:
                choice->scorewC += choice->valueWithTrump[i];
                choice->scorewS += ai_player->hand[i].point;
                choice->scorewD += ai_player->hand[i].point;
                choice->scorewH += ai_player->hand[i].point;
        }
    }

}

