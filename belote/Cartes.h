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

struct Team {
    char name[5];
    struct Cards deck;
    int score;
};

typedef struct Cards Cards;
typedef struct Player Player;

void DistributeCards(Cards* North, Cards* South, Cards* East, Cards* West);
void SorteDeck(Cards* Player);

#endif /* Cartes_h */
