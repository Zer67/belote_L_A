//
//  Cartes.c
//  Belote
//
//  Created by Léonard HESSE on 08/05/2020.
//  Copyright © 2020 Léonard HESSE. All rights reserved.
//

#include "Cartes.h"
#include "menu.h"



/*
 *******************************************************************************************************************
 ****************************************** Distribution of the Cards **********************************************
 *******************************************************************************************************************/

void DistributeCards (Player* North, Player* South, Player* East, Player* West) {
    srand(time(0));

    Cards Distribution[32] = {{"Hea_7",0,0}, {"Hea_8",1,0}, {"Hea_9",2,0}, {"Hea_Ja",3,2}, {"Hea_Qu",4,3}, {"Hea_Ki",5,4}, {"Hea_10",6,10}, {"Hea_1",7,11},
                              {"Clu_7",0,0}, {"Clu_8",1,0}, {"Clu_9",2,0}, {"Clu_Ja",3,2}, {"Clu_Qu",4,3}, {"Clu_Ki",5,4}, {"Clu_10",6,10},
        {"Clu_1",7,11},
                              {"Dia_7",0,0}, {"Dia_8",1,0}, {"Dia_9",2,0}, {"Dia_Ja",3,2}, {"Dia_Qu",4,3}, {"Dia_Ki",5,4}, {"Dia_10",6,10},
        {"Dia_1",7,11},
                              {"Spa_7",0,0}, {"Spa_8",1,0}, {"Spa_9",2,0}, {"Spa_Ja",3,2}, {"Spa_Qu",4,3}, {"Spa_Ki",5,4}, {"Spa_10",6,10},
        {"Spa_1",7,11}};
    //Heart :[0;7]   Club :[8;15]   Diamond :[16;23]   Spade :[23;31]


    int l = 0;

    l = FullingHand(North, l, Distribution); //Initializing North's Hand
    l = FullingHand(South, l, Distribution); //Initializing South's Hand
    l = FullingHand(East, l, Distribution); //Initializing East's Hand

    for (int i = 0; i <8; i++){
        West->hand[i] = Distribution[i]; //Initializing West's Hand
    }


    SorteHand(West);

    printf("\nWest : ");
       for (int i = 0; i<8; i++) {
          if (West->hand[i].color[0] == 'H' || West->hand[i].color[0] == 'D'){
               printf("\x1b[107m\x1b[91m%s", West->hand[i].color);
           }else {
               printf("\x1b[107m\x1b[30m%s", West->hand[i].color);
           }
           printf("\x1b[0m, ");
       }
}



int FullingHand(Player* player, int l, Cards* Distribution) {
    int a;

    for (int i = 0; i <8; i++) {
        a = rand()%(31-l);
        player->hand[i] = Distribution[a];


        for (int u = a; u < 31-l; u++) {
            Distribution[u] = Distribution[u+1];
        }
    l++;
    }

    SorteHand(player);
    printf("\n%s : ", player->name);
       for (int i = 0; i<8; i++) {
           if (player->hand[i].color[0] == 'H' || player->hand[i].color[0] == 'D'){
               printf("\x1b[107m\x1b[91m%s", player->hand[i].color);
           }else {
               printf("\x1b[107m\x1b[30m%s", player->hand[i].color);
           }
            printf("\x1b[0m, ");
       }

    return l;
}


/**
 * \fn void SorteHand(Player* Player)
 * \brief Function that sorte the hand of the player by group of color, and then by the power of each card
 * \param Player - the struct of the player that the function is treating
 */
void SorteHand(Player* Player) {  // I use the Selection sort
    int l= 0, max_index;
    Cards max;

     do{
         max = Player->hand[0];
         max_index = 0;

         for (int i = 1; i < 8-l; i++){
             if (Player->hand[i].color[0] > max.color[0]){  //Comparing the first character of the field "color"
                     max = Player->hand[i];                 //Sorting the hands of each player by gathering the Cards according to their colors
                     max_index = i;
             }else if (Player->hand[i].color[0] == max.color[0] && Player->hand[i].power > max.power) {
                     max = Player->hand[i];                 //and then in ascending order according to the field "power" of the struct Cards
                     max_index = i;
            }
        }

         for (int u = max_index; u < 7-l; u++) {
             Player->hand[u] = Player->hand[u+1];
         }
         Player->hand[7-l] = max;
         l++;

     }while(l<7);


}

void ChangeScore(char trump_color, Player* Player){


    for (int i = 0; i < 8; i++){
        if(Player->hand[i].color[0] == trump_color){

            if (Player->hand[i].color[4] == '9'){
                    Player->hand[i].point = 14;
                    Player->hand[i].power = 18;
            }else if (Player->hand[i].color[4] == 'J'){
                    Player->hand[i].point = 20;
                    Player->hand[i].power = 19;
            }else{
                    Player->hand[i].power = Player->hand[i].power + 10;
            }
        }
    }

}

/**
 * \fn Player* shiftPlayers(Player* playerArray, int Index)
 * \brief this function shift an array of four players from a specified number.
 * \param playerArray - the array of player we want to shift
 * \param Index - the index of the future first player of the future array, so the index of the winner of the trick in playerArray;
 * \return the array of player shifted
 */
Player* shiftPlayers(Player* playerArray, int Index){
    Player* Temp  = (Player*) malloc(sizeof(Player)*4);

    if(playerArray != NULL){
        for(int j=0; j < 4;j++){
            Temp[j] = playerArray[(j+Index)%4];        //If shift = 3, Temp[0] = playerArray[3], Temp[1] = playerArray[0]...
        }
    }
    return Temp;

}
/**
 * \fn int FindPosition(Player* playerArray,char* player)
 * \brief this function allows us to know where a given player is in an array of player.
 * \param playerArray - the array where we're looking for the player
 * \param player - the player we're looking for
 * \return the position of the player in the array
 */
int FindPosition(Player* playerArray,char* player){
    int index = 0;
    while((strcmp(playerArray[index].name, player)!=0) &&(index<4)){
        index++;
    }
    return index;
}

/*
*******************************************************************************************************************
*********************************************** Inside the game ***************************************************
*******************************************************************************************************************/

/**
 * \fn void Game_of_South(Player* South, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color)
 * \brief these two functions will allow the player to play one card in a trick
 * \param South - the struct of the user, if it is turn to play
 * \param turn - it is two things : the number of turns it remains to do, and the size-1 (or the index of the last card) of the player's hand.
 * \param Card_in_theTrick - the index of the last card of the actual trick
 * \param TheTrick - the struct that will contain the cards of the trick
 * \param trump_color - the color of the trump
 */
void Game_of_South(Player* South, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color) {
    char readString[5];
    int ind = -1, i = 0, o = 0;

    printf("\nYour Hand : ");
    for (int u = 0; u <= turn; u++) {
        if (South->hand[u].color[0] == 'H' || South->hand[u].color[0] == 'D'){
            printf("\x1b[107m\x1b[91m%s", South->hand[u].color);
        }else {
            printf("\x1b[107m\x1b[30m%s", South->hand[u].color);
        }
         printf("\x1b[0m, ");
    }

    while (South->hand[i].color[0] != trump_color && i <= turn+1){  //We check if South has some trump
            i++;
    }

    o = i;
        if (i < turn){                                                           //If South has some trump
            while (South->hand[o].color[0] != trump_color && o <= turn+1 ){         //We search for the biggest trump of South's hand.
                    o++;
            }
    }

if ( Card_in_theTrick != 0) {                                    //If South isn't the first to play
        char FirstCardColor = TheTrick->CardsOfTheTrick[0].color[0]; //It is the trick's color, the color of the first played card
        Cards WinningCard = TheTrick->CardsOfTheTrick[TheTrick->indexWinningCards];//It is the card that wins the trick
        i = 0;

                   while (South->hand[i].color[0] != FirstCardColor && i <= turn+1){  //We check if South has the color's trick.
                       i++;
                   }


    if (i <= turn) {                                                            //If South has the trick's color
        if (FirstCardColor != trump_color || South->hand[o].power < WinningCard.power){                             //If the trick's color is not the trump color, or if the trick's color is a trump and South doesn't have the biggest trump of trick
                    do {
                        do {
                                printf("\nType the index of the Card you want to play (from 1 to %i) : ", turn+1);
                                scanf("%s",readString);
                        } while ((sscanf(readString, "%d", &ind) == EOF) || (ind <= 0) || (ind > turn+1));

                        ind--;
                        if (South->hand[ind].color[0] != FirstCardColor){
                                printf("\nYou must play a Card of the trick's color.");
                        }

                    }while (South->hand[ind].color[0] != FirstCardColor);

        }else {                                                         //If the trick's color is the trump color and
                                                                        //if South has a biggest trump than the Winning Card
                        do {
                            do {
                                    printf("\nType the index of the Card you want to play (from 1 to %i) : ", turn+1);
                                    scanf("%s",readString);
                            } while ((sscanf(readString, "%d", &ind) == EOF) || (ind <= 0) || (ind > turn+1));

                            ind--;
                            if (South->hand[ind].color[0] != trump_color){
                                printf("\nYou must play a Card of the trick's color.");
                            }else if (South->hand[ind].power < WinningCard.power){
                                printf("\nYou must play a bigger trump than the last one");
                            }

                        }while ((South->hand[ind].color[0] != trump_color) && (South->hand[ind].power < WinningCard.power));
                            //He must play the biggest trump of the trick


        }
    }else {                                                 //If South has not the trick's color

            if (WinningCard.color[0] == trump_color && South->hand[o].power > WinningCard.power) {//If South has a biggest trump than the Winning Card
                    do {
                        do {
                             printf("\nType the index of the Card you want to play (from 1 to %i) : ", turn+1);
                            scanf("%s",readString);
                        } while ((sscanf(readString, "%d", &ind) == EOF) || (ind <= 0) || (ind > turn+1));

                        ind--;
                        if (ind != o){
                            printf("\nYou must play a bigger trump than the last one");
                        }

                    }while (ind != o);
            } else {                                                //If the winning card is not a trump or if South doesn't have the biggest trump
                    do {
                         printf("\nType the index of the Card you want to play (from 1 to %i) : ", turn+1);
                        scanf("%s",readString);
                    } while ((sscanf(readString, "%d", &ind) == EOF) || (ind <= 0) || (ind > turn+1));
                ind--;
                }



            }

}else{                                                  //If South is the first to play
        do {
             printf("\nType the index of the Card you want to play (from 1 to %i) : ", turn+1);
            scanf("%s",readString);
        } while ((sscanf(readString, "%d", &ind) == EOF) || (ind <= 0) || (ind > turn+1));
        ind--;
    }


    TheTrick->CardsOfTheTrick[Card_in_theTrick] = South->hand[ind];
    for (int u = ind; u < turn; u++) {
        South->hand[u] = South->hand[u+1];
    }
    South->hand = realloc(South->hand, sizeof(Cards)*turn);

}






/**
 * \fn void printTheTrick(TricksStats* TheTrick, Player* players)
 * \brief function that print the current trick
 * \param TheTrick - The structure that gathered the cards that will be played, the name of the winner... (see the rest above)
 * \param players - the array in which the players are placed according to when they play.
 */
void printTheTrick(TricksStats* TheTrick, Player* players) {

    int i = FindPosition(players, "North");


    printf("\n\t\t\t\x1b[94mNorth\n\n\t\t\t");

    if (TheTrick->CardsOfTheTrick[i].color[0] == 'H' || TheTrick->CardsOfTheTrick[i].color[0] == 'D'){
        printf("\x1b[107m\x1b[91m%s", TheTrick->CardsOfTheTrick[i].color);
    }else if (TheTrick->CardsOfTheTrick[i].color[0] == 'C' || TheTrick->CardsOfTheTrick[i].color[0] == 'S') {
        printf("\x1b[107m\x1b[30m%s", TheTrick->CardsOfTheTrick[i].color);
    }
    printf("\x1b[0m\t");

    i = FindPosition(players, "West");
    printf("\n\x1b[93mWest\t\t");

        if (TheTrick->CardsOfTheTrick[i].color[0] == 'H' || TheTrick->CardsOfTheTrick[i].color[0] == 'D'){
            printf("\x1b[107m\x1b[91m%s", TheTrick->CardsOfTheTrick[i].color);
        }else if (TheTrick->CardsOfTheTrick[i].color[0] == 'C' || TheTrick->CardsOfTheTrick[i].color[0] == 'S'){
            printf("\x1b[107m\x1b[30m%s", TheTrick->CardsOfTheTrick[i].color);
        }else {
        printf("\t\t");
    }
    printf("\x1b[0m\t\t");


    i = FindPosition(players, "East");
        if (TheTrick->CardsOfTheTrick[i].color[0] == 'H' || TheTrick->CardsOfTheTrick[i].color[0] == 'D'){
            printf("\x1b[107m\x1b[91m%s", TheTrick->CardsOfTheTrick[i].color);
        }else if (TheTrick->CardsOfTheTrick[i].color[0] == 'S' || TheTrick->CardsOfTheTrick[i].color[0] == 'C'){
            printf("\x1b[107m\x1b[30m%s", TheTrick->CardsOfTheTrick[i].color);
        }else {
            printf("\t\t");
        }
        printf("\x1b[0m\t");
    printf("\t\x1b[93mEast\n\t\t\t");

    i = FindPosition(players, "South");
    if (TheTrick->CardsOfTheTrick[i].color[0] == 'H' || TheTrick->CardsOfTheTrick[i].color[0] == 'D'){
        printf("\x1b[107m\x1b[91m%s", TheTrick->CardsOfTheTrick[i].color);
    }else if (TheTrick->CardsOfTheTrick[i].color[0] == 'C' || TheTrick->CardsOfTheTrick[i].color[0] == 'S') {
        printf("\x1b[107m\x1b[30m%s", TheTrick->CardsOfTheTrick[i].color);
    }else{
        printf("\t\t");
    }
    printf("\x1b[0m\t\n");

    printf("\n\t\t\t\x1b[94mSouth");
    printf("\x1b[0m \n");
}

