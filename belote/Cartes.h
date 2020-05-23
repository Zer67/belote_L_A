//
//  Cartes.h
//  Belote
//
//  Created by Michel HESSE on 08/05/2020.
//  Copyright © 2020 Léonard HESSE. All rights reserved.
//

#ifndef Cartes_h
#define Cartes_h

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

#endif /* Cartes_h */
