#include "AI.h"
#include "Cartes.h"
#include "menu.h"

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
        printf("The ai-player %s decided to skip\n", ai_player->name);
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




void Game_of_AI(Player* Player, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color){
    Boolean HasPlayed = FALSE;
    int i = 0, min = 0, max = 0;
    

    
if (Card_in_theTrick == 0){                                   //Checks if the Player plays the first card of the trick.

        while (HasPlayed == FALSE && i<= turn) {                  //First, plays a non-trump big Card, if possible
           if(Player->hand[i].color[0] != trump_color && Player->hand[i].power > 5){
                TheTrick->CardsOfTheTrick[0] = Player->hand[i];
                HasPlayed = TRUE;                                 //if the conditions are verified, it means he has played,
                i--;                                              //then the function stops.
            }
            i++;
        }

        if(HasPlayed == FALSE){                                    //If not played before, the Player plays a non-trump small Card.
            i = 0;
            while (HasPlayed == FALSE && i<= turn){
                if(Player->hand[i].color[0] != trump_color && Player->hand[i].power < 3){
                    TheTrick->CardsOfTheTrick[0] = Player->hand[i];
                    HasPlayed = TRUE;
                    i--;
                }
                i++;
            }
            if (HasPlayed == FALSE){
                i = 0;
                while (HasPlayed == FALSE && i<=turn){       //If not played before, the Player plays a trump.
                   if(Player->hand[i].color[0] == trump_color){
                       TheTrick->CardsOfTheTrick[0] = Player->hand[i];
                       HasPlayed = TRUE;
                       i--;
                   }
                   i++;
                }
                if (HasPlayed == FALSE){                    //If the player can't respect all the previous condition,
                    i = 0;                          //he plays the first card of his hand.
                    TheTrick->CardsOfTheTrick[0] = Player->hand[i];
                }
            }

        }
        strcpy(TheTrick->NameOfWinner, Player->name);
        TheTrick->TeamWinningNumber = Player->TeamNumber;
        TheTrick->indexWinningCards = Card_in_theTrick;
        for (int u = i; u <= turn; u++) {
              Player->hand[u] = Player->hand[u+1];
        }
        Player->hand = realloc(Player->hand, sizeof(Cards)*turn);

    }
else {                                                                      //If the player isn't the first to play

        int o = 0;
        Cards FirstCardPlayed = TheTrick->CardsOfTheTrick[0]; //It is the first card played.
        Cards WinningCard = TheTrick->CardsOfTheTrick[TheTrick->indexWinningCards];//It is the card that wins the trick
        
        for (int u = 0; u <= turn; u++){
            if (Player->hand[u].power < Player->hand[min].power){
                min = u;                                //min takes the index of the card with the less value in the player's hand.
            }
        }
        
        for (int u = 0; u <= turn; u++){
            if (Player->hand[u].color[0] != trump_color && Player->hand[u].point > Player->hand[max].point){
                max = u;                                //max takes the index of the non-trump card with the most value in the player's hand
            }
        }


        while (Player->hand[i].color[0] != FirstCardPlayed.color[0] && i <= turn+1){
            i++;
        }
        // If i < turn+1, it means the player has at least one card of the trick's color,
        // and i is the index of the smallest card of the trick's color in his hand.
        

        if ( i <= turn){                                     //If the player has the trick's color
                o = i;
                while (HasPlayed == FALSE && o <= turn){                //We take the index of the biggest card of the trick's color in his hand
                    if (Player->hand[o].color[0] != Player->hand[o+1].color[0]){
                        HasPlayed = TRUE;
                        o--;
                    } else if (o==turn){
                        HasPlayed = TRUE;
                        o--;
                    }
                    o++;
                }
            //Player->hand[o] is the biggest card of the trick's color in the player's hand
            
            if (FirstCardPlayed.color[0] != trump_color) {
                    if (Player->hand[o].power > WinningCard.power){                     //The player wins the trick
                        TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];
                        strcpy(TheTrick->NameOfWinner, Player->name);
                        TheTrick->TeamWinningNumber = Player->TeamNumber;
                        TheTrick->indexWinningCards = Card_in_theTrick;

                    }else if (TheTrick->TeamWinningNumber == Player->TeamNumber) {      //The player plays a big card since is team wins the trick
                        TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];

                    } else {                                                            //The player plays the smallest card of the trick's color
                        o = i;
                        TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];
                    }
            }
            else {                                                                      //If the first card is a trump
                if (Player->hand[o].power > WinningCard.power){                         //If the player can win the trick
                    TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];
                    strcpy(TheTrick->NameOfWinner, Player->name);
                    TheTrick->TeamWinningNumber = Player->TeamNumber;
                    TheTrick->indexWinningCards = Card_in_theTrick;
            
                }else{                                                                  //If the player can't win the trick
                    o = i;
                    TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];
              
                }
            }
        }else {                                              //If the player has not the trick's color
                    HasPlayed = FALSE;
                    o = 0; i =0;
            

                    while (Player->hand[i].color[0] != trump_color && i <= turn+1){ //We check if the player has still some trump
                        i++;
                    }
                    // If i < turn+1, it means the player has at least a trump, and i is the index of the smallest trump card in his hand.

                    if(TheTrick->TeamWinningNumber == Player->TeamNumber && Card_in_theTrick == 3){
                        // if the winning card is a trump, if the player's team wins the trick and if the player is the last to play
                        o = max;
                        TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];   //He plays his biggest non-trump card


                    }else if (WinningCard.color[0] == trump_color && TheTrick->TeamWinningNumber != Player->TeamNumber && i <= turn){
                        //If the winning card is a trump, if the player's team looses the trick and if the player has a trump
                        o = i;
                        while (HasPlayed==FALSE && o <= turn+1){       //We search for a trump card who wins the trick
                            if (Player->hand[o].color[0] == trump_color && Player->hand[o].power > WinningCard.power) {
                                HasPlayed = TRUE;
                                o--;
                            }
                            o++;
                        }
                        
                        
                        if (HasPlayed == TRUE){         //If he can win the trick
                            TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];  //He plays the card that wins the trick
                            strcpy(TheTrick->NameOfWinner, Player->name);
                            TheTrick->TeamWinningNumber = Player->TeamNumber;
                            TheTrick->indexWinningCards = Card_in_theTrick;

                        }else {                         //If he can't win the trick
                            o = min;                    //He plays his smallest card
                            TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];
                        }
                        
                        
                    }else if (WinningCard.color[0] != trump_color && i <= turn) {        //If the winning card is not a trump and if he has a trump
                   
                        o = i;
                        TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];      //he plays the smallest trump card
                        strcpy(TheTrick->NameOfWinner, Player->name);
                        TheTrick->TeamWinningNumber = Player->TeamNumber;
                        TheTrick->indexWinningCards = Card_in_theTrick;
                        
                    }else{                                                               //If he has no trump card
                        o = min;
                        TheTrick->CardsOfTheTrick[Card_in_theTrick] = Player->hand[o];  //he plays the smallest card of his hand
                    }
            }
        for (int u = o; u <= turn; u++) {
              Player->hand[u] = Player->hand[u+1];
        }
        Player->hand = realloc(Player->hand, sizeof(Cards)*turn);
    }
}
