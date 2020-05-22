//
//  Cartes.c
//  Belote
//
//  Created by Léonard HESSE on 08/05/2020.
//  Copyright © 2020 Léonard HESSE. All rights reserved.
//

#include "Cartes.h"



void DistributeCards (Cards* North, Cards* South, Cards* East, Cards* West) {
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
    
/*
************************************************************************************************************************************************
 ************************************************************Initializing North's hand***********************************************************
  *************************************************************************************************************************************************/
    
    for (int i = 0; i < 8; i++) {
        int a = rand()%(31-l);
        North[i] = Distribution[a] ;
        
        for (int u = a; u < 31-l; u++) {
            Distribution[u] = Distribution[u+1];
        }
        l++;
    }
    
    SorteDeck(North);
    
    printf("\nNorth : ");
      for (int i = 0; i <8; i++) {
          printf("%s, ", North[i].color);
      }
   
/*
************************************************************************************************************************************************
************************************************************Initializing East's hand***********************************************************
 ************************************************************************************************************************************************
*/

    for (int i = 0; i < 8; i++) {
        int a = rand()%(31-l);
        East[i] = Distribution[a];
        
        for (int u = a; u < 31-l; u++) {
            Distribution[u] = Distribution[u+1];
        }

        l++;
    }
    
     SorteDeck(East);
    
     printf("\nEast : ");
       for (int i = 0; i <8; i++) {
           printf("%s, ", East[i].color);
       }
    

/*
************************************************************************************************************************************************
************************************************************Initializing South's hand***********************************************************
 ************************************************************************************************************************************************
*/
    
    for (int i = 0; i < 8; i++) {
        int a = rand()%(31-l);
        South[i] = Distribution[a];
        
        for (int u = a; u < 31-l; u++) {
            Distribution[u] = Distribution[u+1];
        }
        l++;
    }
    
     SorteDeck(South);
    
     printf("\nSouth : ");
       for (int i = 0; i <8; i++) {
           printf("%s, ", South[i].color);
       }
    

    

/*
************************************************************************************************************************************************
************************************************************Initializing West's hand***********************************************************
 ************************************************************************************************************************************************
*/
    
    for (int i = 0; i <= 31-l; i++) {
        West[i] = Distribution[i];

    }
 
     SorteDeck(West);
}



void SorteDeck(Cards* Player) {
    int l= 0, max_index;
    Cards max;

     do{
        max = Player[0];
         max_index = 0;
         
         for (int i = 1; i < 8-l; i++){
             if (Player[i].color[0] > max.color[0]){
                     max = Player[i];
                     max_index = i;
             }else if (Player[i].color[0] == max.color[0] && Player[i].power > max.power) {
                     max = Player[i];
                     max_index = i;
            }
        }
            
         for (int u = max_index; u < 7-l; u++) {
             Player[u] = Player[u+1];
         }
         Player[7-l] = max;
         l++;
         
     }while(l<7);

}

