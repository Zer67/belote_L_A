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
        {"Dia_1",6,11},
                              {"Spa_7",0,0}, {"Spa_8",1,0}, {"Spa_9",2,0}, {"Spa_Ja",3,2}, {"Spa_Qu",4,3}, {"Spa_Ki",5,10}, {"Spa_10",6,10},
        {"Spa_1",6,11}};
    //Heart :[0;7]   Club :[8;15]   Diamond :[16;23]   Spade :[23;31]


    int l = 0;

    l = FullingHand(North, l, Distribution); //Initializing North's Hand
    l = FullingHand(South, l, Distribution); //Initializing South's Hand
    l = FullingHand(East, l, Distribution); //Initializing East's Hand

    for (int i = 0; i <8; i++){
        West->hand[i] = Distribution[i]; //Initializing West's Hand
    }
    SorteHand(West);
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


    return l;
}



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

    printf("\n%s : ", Player->name);
    for (int i = 0; i<8; i++) {
        printf("%s, ", Player->hand[i].color);
    }

}

void ChangeScore(char trump_color, Player* Player){

    //Changing the score of the Cards of North's hand.
    for (int i = 0; i < 8; i++){
        if(Player->hand[i].color[0] == trump_color){
            Player->hand[i].power += 20;
            
            switch (Player->hand[i].color[5]) {
                case '9':
                    Player->hand[i].point = 14;
                    Player->hand[i].power = 28;
                    break;
                case 'J':
                    Player->hand[i].point = 20;
                    Player->hand[i].power =29;
                default:
                    break;
            }
        }
    }
    
}

/** this function shift an array of four players from a specified number.
 * @param playerArray - the array of player we want to shift
 * @param shift - the number of shift we want to do
 * @return the array of player shifted
 */
Player* shiftPlayers(Player* playerArray, int shift, int size){
    if((playerArray != NULL)||(size!=4)){
        for(int j=0; j<(shift%size);j++){   /* here we use the modulo to avoid extra shifts which will be useless */
            Player temp = playerArray[0];   /* here is a temporal variable which is useful to stock the first player of the array */

            for(int i = 0; i<size-1; i++){

                playerArray[i] = playerArray[i+1];
            }
            playerArray[size-1] = temp;
        }
    }
    return playerArray;
}

/** this function allows us to know where a given player is in an array of player.
 * @param playerArray - the array where we're looking for the player
 * @param player - the player we're looking for
 * @return the position of the player in the array
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


void Game_of_South(Player* South, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color) {
    char readString[5];
    int ind = -1;
    
    
    printf("\nYour Hand : ");
    for (int i = 0; i <= turn; i++) {
          printf("%s, ", South->hand[i].color);
      }

    do {
         printf("\nType the index of the Card you want to play (from 1 to %i) : ", turn+1);
        scanf("%s",readString);
    } while ((sscanf(readString, "%d", &ind) == EOF) || (ind <= 0) || (ind > turn+1));
    
    ind--;
    printf("\nSouth : %s", South->hand[ind].color);
    
    TheTrick->CardsOfTheTrick[0] = South->hand[ind];
    strcpy(TheTrick->NameOfWinner, "South");
    TheTrick->TeamWinningNumber = South->TeamNumber;
    
    for (int u = ind; u < turn; u++) {
        South->hand[u] = South->hand[u+1];
    }
    turn--;
    

}







void printTheTrick(TricksStats* TheTrick, Player* players, int Card_in_theTrick) {
    int i = 0;
    Boolean Found = FALSE;
    
    printf("\n\t\tNorth");
    while(!Found) {
        if (strcmp(players[i].name, "North")==0){
            printf("\n\t\t%s", TheTrick->CardsOfTheTrick[i].color);
            Found = TRUE;
        }
        i++;
    }
    
    Found = FALSE;
    i = 0;
    printf("\nWest");
       while(!Found) {
           if (strcmp(players[i].name, "West")==0){
               printf("\t%s", TheTrick->CardsOfTheTrick[i].color);
               Found = TRUE;
           }
           i++;
       }
    
    Found = FALSE;
    i = 0;
       while(!Found) {
           if (strcmp(players[i].name, "East")==0){
               printf("   %s", TheTrick->CardsOfTheTrick[i].color);
               Found = TRUE;
           }
           i++;
       }
    printf("\tEast");
    
    Found = FALSE;
    i = 0;
       while(!Found) {
           if (strcmp(players[i].name, "South")==0){
               printf("\n\t\t%s", TheTrick->CardsOfTheTrick[i].color);
               Found = TRUE;
           }
           i++;
       }
    printf("\n\t\tSouth");
}

