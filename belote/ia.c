#include "ia.h"

/** the function which allow the ai to make a bet.
 * @param ai_player - the struct which allows us to know which ai_player is playing
 * @param current_bet_value - the value of the current bet, by example a General have a value of 500
 * @param current_bet - the array containing all the bets already made
 */
int AIbid(Player* ai_player, int current_bet_value, biddings* current_bet){

    /*******************************************************************************************************************************************************************
     **  Computations to set up the information that the ai-player will use to make a choice for his bet ***************************************************************
     *******************************************************************************************************************************************************************/

    Cardtype* h = (Cardtype*) malloc(sizeof(Cardtype));
    Cardtype* d = (Cardtype*) malloc(sizeof(Cardtype));
    Cardtype* s = (Cardtype*) malloc(sizeof(Cardtype));
    Cardtype* c = (Cardtype*) malloc(sizeof(Cardtype));

    h->color = 'H', d->color = 'D', s->color = 'S', c->color = 'C';
    h->counter = -1, d->counter = -1, s->counter = -1, c->counter = -1; /* these variables are used to count how much the ai player have a certain color in their hand */
    h->nbrStg = 0, d->nbrStg = 0, s->nbrStg = 0, c->nbrStg = 0; /* these variables are there to count the number of strongs figure in a certain color */

    choiceMaker* choice = (choiceMaker*) malloc(sizeof(choiceMaker));
    choice->valueWithTrump = (int*) malloc(sizeof(int)*8);
    choice->color = (char*) malloc(sizeof(char)*8);
    h->scorewT = 0, d->scorewT = 0, s->scorewT = 0, c->scorewT = 0;

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
                h->scorewT += choice->valueWithTrump[i];
                s->scorewT += ai_player->hand[i].point;
                d->scorewT += ai_player->hand[i].point;
                c->scorewT += ai_player->hand[i].point;
                if(h->figures == NULL){
                    h->figures = (char*) malloc(sizeof(char));
                    h->counter =1;
                } else {
                    h->counter++;
                    h->figures = realloc(h->figures,sizeof(char)*(h->counter));
                }
                h->figures[h->counter-1] = ai_player->hand[i].color[5];
                if ((h->figures[h->counter-1]=='1')||(h->figures[h->counter-1]=='J') || (h->figures[h->counter-1]=='9') || (h->figures[h->counter-1]=='A')){
                    h->nbrStg++;
                }
                break;
            case ('S'):
                s->scorewT += choice->valueWithTrump[i];
                h->scorewT += ai_player->hand[i].point;
                d->scorewT += ai_player->hand[i].point;
                c->scorewT += ai_player->hand[i].point;
                if(s->figures == NULL){
                    s->figures = (char*) malloc(sizeof(char));
                    s->counter = 1;
                } else {
                    s->counter++;
                    s->figures = realloc(s->figures,sizeof(char)*(s->counter+1));
                }
                s->figures[s->counter-1] = ai_player->hand[i].color[5];
                if ((s->figures[s->counter-1]=='1')||(s->figures[s->counter-1]=='J') || (s->figures[s->counter-1]=='9') || (s->figures[s->counter-1]=='A')){
                    s->nbrStg++;
                }
                break;
            case ('D'):
                d->scorewT += choice->valueWithTrump[i];
                s->scorewT += ai_player->hand[i].point;
                h->scorewT += ai_player->hand[i].point;
                c->scorewT += ai_player->hand[i].point;
                if(d->figures == NULL){
                    d->figures = (char*) malloc(sizeof(char));
                    d->counter = 1;
                } else {
                    d->counter++;
                    d->figures = realloc(d->figures,sizeof(char)*(d->counter));
                }
                d->figures[d->counter-1] = ai_player->hand[i].color[5];
                if ((d->figures[d->counter-1]=='1')||(d->figures[d->counter-1]=='J') || (d->figures[d->counter-1]=='9') || (d->figures[d->counter-1]=='A')){
                    d->nbrStg++;
                }
                break;
            default:
                c->scorewT += choice->valueWithTrump[i];
                s->scorewT += ai_player->hand[i].point;
                d->scorewT += ai_player->hand[i].point;
                h->scorewT += ai_player->hand[i].point;
                if(c->figures == NULL){
                    c->figures = (char*) malloc(sizeof(char));
                    c->counter = 1;
                } else {
                    c->counter++;
                    c->figures = realloc(c->figures,sizeof(char)*(c->counter+1));
                }
                c->figures[c->counter-1] = ai_player->hand[i].color[5];
                if ((c->figures[c->counter-1]=='1')||(c->figures[c->counter-1]=='J') || (c->figures[c->counter-1]=='9') || (c->figures[c->counter-1]=='A')){
                    c->nbrStg++;
                }

        }
    }
    /*******************************************************************************************************************************************************************
     **  Computations where the ai-player will make his choice *********************************************************************************************************
     *******************************************************************************************************************************************************************/

    Cardtype** array_color = (Cardtype**) malloc(sizeof(Cardtype*)*4);
    array_color[0] = h;
    array_color[1] = d;
    array_color[2] = s;
    array_color[3] = c;

      /* sort by number of strong cards : */
    array_color = BubbleSortChoice(array_color);

    if ((array_color[0]->nbrStg>= 4)&&(120>current_bet_value)){
        current_bet = AddABet(current_bet,ai_player->name,sizeof(ai_player->name),"120",3,array_color[0]->color);
        return 1;
    } else if((array_color[0]->nbrStg>= 3)&&(80>current_bet_value)) {
        current_bet = AddABet(current_bet,ai_player->name,sizeof(ai_player->name),"80",2,array_color[0]->color);
        return 1;
    } else {
        printf("\nthe ai-player %s decided to skip", ai_player->name);
        return 0;
    }

    return -1;
}


Cardtype** BubbleSortChoice(Cardtype** array){
    Boolean sorted=FALSE;
    Cardtype* buff = (Cardtype*) malloc(sizeof(Cardtype));
    int i = 3;
    while((!sorted)&&(i>0)){
        sorted = TRUE;
        for(int j=0;j<i;j++){
            if(array[j+1]->nbrStg<array[j]->nbrStg){
                buff = array[j+1];
                array[j+1] = array[j];
                array[j] = buff;
                sorted = FALSE;
            }
        }
        i-= 1;
    }
    free(buff);
    return array;
}
