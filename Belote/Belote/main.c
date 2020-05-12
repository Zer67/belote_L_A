//
//  main.c
//  Belote
//
//  Created by Michel HESSE on 08/05/2020.
//  Copyright © 2020 Léonard HESSE. All rights reserved.
//

#include "Cartes.h"

int main() {
    int sizeJ = 8;
    
    char** North = (char**)malloc(sizeof(char*)*sizeJ);
    char** South = (char**)malloc(sizeof(char*)*sizeJ);
    char** East = (char**)malloc(sizeof(char*)*sizeJ);
    char** West = (char**)malloc(sizeof(char*)*sizeJ);
    
    DistributeCards(North, South, East, West);
}

