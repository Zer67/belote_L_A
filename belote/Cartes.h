//
//  Cartes.h
//  Belote
//
//  Created by Michel HESSE on 08/05/2020.
//  Copyright © 2020 Léonard HESSE. All rights reserved.
//

#ifndef Cartes_h
#define Cartes_h
#include <time.h>
#include "menu.h"
struct Cards {
    char color[6];
    int power;
    int point;
};

struct Player {
    char name[5];
    struct Cards* hand;
    struct Cards* tricks;
    int score;
};

typedef struct Cards Cards;
typedef struct Player Player;

void DistributeCards(Player* North, Player* South, Player* East, Player* West);
int FullingHand (Player* player, int l, Cards* Distribution);
void SorteDeck(Player* Player);

/** this function shift an array of four players from a specified number.
 * @param playerArray - the array of player we want to shift
 * @param shift - the number of shift we want to do
 * @return the array of player shifted
 */
Player* shiftPlayers(Player* playerArray, int shift, int size);

/** this function allows us to know where a given player is in an array of player.
 * @param playerArray - the array where we're looking for the player
 * @param player - the player we're looking for
 * @return the position of the player in the array
 */
int FindPosition(Player* playerArray,char* player);

#endif /* Cartes_h */
