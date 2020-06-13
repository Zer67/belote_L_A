/**
  * \file AI.c
  * \brief the library containing all the functions related to the AI.
  * \author Léonard Hesse
  * \author Alexandre Viala
  * \date 13th june 2020
  *
  * In this library, we define the way the AI will bet and how she will play.
  */

#include "AI.h"

/**
 * \fn int AIbid(Player* ai_player, int current_bet_value, biddings* current_bet)
 * \brief the function which allow the ai to make a bet.
 * \param ai_player - the struct which allows us to know which ai_player is playing
 * \param current_bet_value - the value of the current bet, by example a General have a value of 500
 * \param current_bet - the array containing all the bets already made
 */
int AIbid(Player* ai_player, int current_bet_value, biddings* current_bet){

    /*******************************************************************************************************************************************************************
     **  Computations to set up the information that the ai-player will use to make a choice for his bet ***************************************************************
     *******************************************************************************************************************************************************************/

    Cardtype* h = (Cardtype*) malloc(sizeof(Cardtype));
    Cardtype* d = (Cardtype*) malloc(sizeof(Cardtype));
    Cardtype* s = (Cardtype*) malloc(sizeof(Cardtype));
    Cardtype* c = (Cardtype*) malloc(sizeof(Cardtype));

    h->figures = NULL, d->figures =NULL, s->figures = NULL, c->figures = NULL;
    h->color = 'H'; (void)(d->color = 'D'); (void)(s->color = 'S'); c->color = 'C';
    (void)(h->counter = -1), (void)(d->counter = -1), (void)(s->counter = -1), c->counter = -1; /* these variables are used to count how much the ai player have a certain color in their hand */
    (void)(h->nbrStg = 0), (void)(d->nbrStg = 0), (void)(s->nbrStg = 0), c->nbrStg = 0; /* these variables are there to count the number of strongs figure in a certain color */

    choiceMaker* choice = (choiceMaker*) malloc(sizeof(choiceMaker));
    choice->valueWithTrump = (int*) malloc(sizeof(int)*8);
    choice->color = (char*) malloc(sizeof(char)*8);
    (void)(h->scorewT = 0), (void)(d->scorewT = 0), (void)(s->scorewT = 0), c->scorewT = 0;

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
                h->figures[h->counter-1] = ai_player->hand[i].color[4];
                if ((h->figures[h->counter-1]=='1')||(h->figures[h->counter-1]=='J') || (h->figures[h->counter-1]=='9')){
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
                s->figures[s->counter-1] = ai_player->hand[i].color[4];
                if ((s->figures[s->counter-1]=='1')||(s->figures[s->counter-1]=='J') || (s->figures[s->counter-1]=='9')){
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
                d->figures[d->counter-1] = ai_player->hand[i].color[4];
                if ((d->figures[d->counter-1]=='1')||(d->figures[d->counter-1]=='J') || (d->figures[d->counter-1]=='9')){
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
                c->figures[c->counter-1] = ai_player->hand[i].color[4];
                if ((c->figures[c->counter-1]=='1')||(c->figures[c->counter-1]=='J') || (c->figures[c->counter-1]=='9')){
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
        printf("The ai-player %s decided to bet 120 points\n", ai_player->name);
        return 1;
    } else if((array_color[0]->nbrStg>= 3)&&(80>current_bet_value)) {
        current_bet = AddABet(current_bet,ai_player->name,sizeof(ai_player->name),"80",2,array_color[0]->color);
        printf("The ai-player %s decided to bet 80 points\n", ai_player->name);
        return 1;
    } else {
        printf("The ai-player %s decided to skip\n", ai_player->name);
        return 0;
    }

    return -1;
}

/**
 * \fn Cardtype** BubbleSortChoice(Cardtype** array)
 * \brief a bubble sort which sort an array of Cardtype according to their number strong cards contained
 * \param array - an array of pointers on Cardtype which will be sorted
 * \return the array in argument sorted
 */
Cardtype** BubbleSortChoice(Cardtype** array){
    Boolean sorted=FALSE;
    Cardtype* buff = (Cardtype*) malloc(sizeof(Cardtype));
    int i = 3;
    while((sorted==FALSE)&&(i>0)){
        sorted = TRUE;
        for(int j=0;j<i;j++){
            if(array[j+1]->nbrStg>array[j]->nbrStg){
                buff = array[j+1];
                array[j+1] = array[j];
                array[j] = buff;
                sorted = FALSE;
            }
        }
        i-= 1;
    }
    return array;
}



/**
 * \fn void Game_of_AI(Player* Player, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color)
 * \brief these  functions will allow the artificial player to play one card in a trick
 * \param Player - the struct of the artificial player
 * \param turn - it is two things : the number of turns it remains to do, and the size-1 (or the index of the last card) of the player's hand.
 * \param Card_in_theTrick - the index of the last card of the actual trick
 * \param TheTrick - the struct that will contain the cards of the trick
 * \param trump_color - the color of the trump
*/
void Game_of_AI(Player* Player, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color){
    Boolean HasPlayed = FALSE;
    int i = 0, min = 0, max = 0;

    for (int u = 0; u <= turn; u++){
        if (Player->hand[u].color[0] != trump_color && Player->hand[u].power > Player->hand[max].power){
            max = u;                                //max takes the index of the non-trump card with the most value in the player's hand
        }
    }


    for (int u = 0; u <= turn; u++){
        if (Player->hand[u].power < Player->hand[min].power){
            min = u;                                //min takes the index of the card with the less value in the player's hand.
        }
    }


if (Card_in_theTrick == 0){                                   //Checks if the Player plays the first card of the trick.

        if (Player->hand[max].power > 5) {  //First, plays a non-trump big Card, if possible
            i = max;
        }else {

                                                  //If not played before, the Player plays a non-trump small Card.
                while (Player->hand[i].color[0] != trump_color && Player->hand[i].power > 3 && i <= turn+1){
                    i++;
                }
                if (i > turn){
                    i = 0;
                    while (Player->hand[i].color[0] == trump_color && i<=turn){       //If not played before, the Player plays a trump.
                       i++;
                    }

                    if (i > turn){                    //If the player can't respect all the previous condition,
                        i = min;                          //he plays the first card of his hand.
                    }
                }
            }

    TheTrick->CardsOfTheTrick[0] = Player->hand[i];
        for (int u = i; u <= turn; u++) {
              Player->hand[u] = Player->hand[u+1];
        }
        Player->hand = realloc(Player->hand, sizeof(Cards)*turn);
        //printf("\n %s : %i", Player->name, i);

    }
else {                                                                      //If the player isn't the first to play

        int o = 0;
        char FirstCardColor = TheTrick->CardsOfTheTrick[0].color[0]; //It is the first card played.
        Cards WinningCard = TheTrick->CardsOfTheTrick[TheTrick->indexWinningCards];//It is the card that wins the trick

        while (Player->hand[i].color[0] != FirstCardColor && i <= turn+1){
            i++;
        }
        // If i < turn+1, it means the player has at least one card of the trick's color,
        // and i is the index of the smallest card of the trick's color in his hand.


        if ( i <= turn){                                     //If the player has the trick's color
                o = i;
            if( i < turn) {
                while (HasPlayed == FALSE && o <= turn){                //We take the index of the biggest card
                    if (o < turn && Player->hand[o].color[0] != Player->hand[o+1].color[0]){
                        HasPlayed = TRUE;
                        o--;
                    }else if(o == turn){
                        HasPlayed = TRUE;
                        o--;
                    }
                    o++;
                }

            //Player->hand[o] is the biggest card of the trick's color in the player's hand

                if ((Player->hand[o].power < WinningCard.power) && (TheTrick->TeamWinningNumber != Player->TeamNumber)){
                //If the player can't win the trick and if the player's team doesn't win the trick
                    o = i;
                }
            }
        }else {                                              //If the player has not the trick's color
                    o = 0; i =0;

                    while (Player->hand[i].color[0] != trump_color && i <= turn+1){ //We check if the player has still some trump
                        i++;
                    }
                    // If i < turn+1, it means the player has at least a trump, and i is the index of the smallest trump card in his hand.

                    if(TheTrick->TeamWinningNumber == Player->TeamNumber){
                        // if the winning card is a trump, if the player's team wins the trick and if the player is the last to play
                        o = max;                                                        //He plays the biggest non-trump card

                    }else if (WinningCard.color[0] == trump_color && TheTrick->TeamWinningNumber != Player->TeamNumber && i <= turn){
                        //If the winning card is a trump, if the player's team looses the trick and if the player has a trump
                        o = i;
                        while (Player->hand[o].power > WinningCard.power && o <= turn+1){       //We search for a trump card who wins the trick
                            o++;
                        }


                        if (o > turn){
                            o = min;
                        }



                    }else if (WinningCard.color[0] != trump_color && o <= turn) {        //If the winning card is not a trump and if he has a trump
                        o = i;                                                          //he plays the smallest trump card

                    }else{                                                               //If he has no trump card
                        o = min;                                                    //he plays the smallest card of his hand
                    }
            }
    TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];
        for (int u = o; u <= turn; u++) {
              Player->hand[u] = Player->hand[u+1];
        }
        Player->hand = realloc(Player->hand, sizeof(Cards)*turn);
    //printf("\n %s : %i, %i", Player->name, i, o);
    }


}
