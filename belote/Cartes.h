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
#include <string.h>
#include "menu.h"

struct Cards{
    char color[6];
    int power;
    int point;
};


struct Player{
    char name[5];
    struct Cards* hand;
    struct Cards* WonTricks;
    int score;
    int TeamNumber;                     //Define the number of the Team : 1 for Team North-South, 2 for Team East-West;
};

typedef struct {
    struct Cards* CardsOfTheTrick;
    char NameOfWinner[5];
    int indexWinningCards;
    int TeamWinningNumber;
}TricksStats;


typedef struct Cards Cards;
typedef struct Player Player;

//Sub-program that gathers the functions to distribute the cards to each Player. It will call the function "FullingHand".
void DistributeCards(Player* North, Player* South, Player* East, Player* West);




//Function that randomly gives to each player 8 cards. It will call the function "SorteHand".
int FullingHand (Player* player, int l, Cards* Distribution);



/**Function that sorte the hand of the player by group of color, and then by the power of each card
 *@param Player - the struct of the player that the function is treating 
 */
void SorteHand(Player* Player);

//Function that changes the score of each cards according to the chosen trump.
void ChangeScore(char trump_color, Player* Player);

//The function to make the AI play is very different from the function to make the user play.

/**these two functions will allow the player to play one card in a trick
 *@param South - the struct of the user, if it is turn to play
 *@param turn - it is two things : the number of turns it remains to do, and the size-1 (or the index of the last card) of the player's hand.
 *@param Card_in_theTrick - the index of the last card of the actual trick
 *@param TheTrick - the struct that will contain the cards of the trick
 *@param trump_color - the color of the trump
 */
void Game_of_South(Player* South, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color);

/**these two functions will allow the player to play one card in a trick
@param Player - the struct of the artificial player
@param turn - it is two things : the number of turns it remains to do, and the size-1 (or the index of the last card) of the player's hand.
@param Card_in_theTrick - the index of the last card of the actual trick
@param TheTrick - the struct that will contain the cards of the trick
@param trump_color - the color of the trump
*/
void Game_of_AI(Player* Player, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color);

void printTheTrick(TricksStats* TheTrick, Player* players, int Card_in_theTrick);

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
