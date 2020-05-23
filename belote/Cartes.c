//
//  Cartes.c
//  Belote
//
//  Created by Léonard HESSE on 08/05/2020.
//  Copyright © 2020 Léonard HESSE. All rights reserved.
//

#include "Cartes.h"



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
    SorteDeck(West);
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

    SorteDeck(player);


    return l;
}



void SorteDeck(Player* Player) {  // I use the Selection sort
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
