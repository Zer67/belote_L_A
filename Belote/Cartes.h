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
/**
 * \struct Cards
 * \brief the structure containing one card
 */
struct Cards{
    char color[6]; /** color of the card (it contains the symbol and the color by example Hea_Ki for king of heart */
    int power; /** the power of the card */
    int point; /** the points the card worth */
};

/**
 * \struct Player
 * \brief the structure containing the player
 */
struct Player{
    char name[5];   /** the name of the player */
    struct Cards* hand; /** the array of cards containing all the cards he can possibly play */
    int score;  /** the score he has done */
    int TeamNumber;  /** Define the number of the Team : 1 for Team North-South, 2 for Team East-West */
};
/**
 * \struct TrickStats
 * \brief the structure which contains all the main informations of the current trick
 */
typedef struct {
    struct Cards* CardsOfTheTrick; /** an array of cards containing all the cards that were played during the trick */
    char* NameOfWinner; /** the winner's name of the trick */
    int indexWinningCards;  /** the index( inside CardsOfTheTrick ) of the card which win the trick */
    int TeamWinningNumber;  /** the number of the team who win : 1 for North-South and 2 for Team East-West */
}TricksStats;


typedef struct Cards Cards;
typedef struct Player Player;

//Sub-program that gathers the functions to distribute the cards to each Player. It will call the function "FullingHand".
void DistributeCards(Player* North, Player* South, Player* East, Player* West);




//Function that randomly gives to each player 8 cards. It will call the function "SorteHand".
int FullingHand (Player* player, int l, Cards* Distribution);



/**
 * \fn void SorteHand(Player* Player)
 * \brief Function that sorte the hand of the player by group of color, and then by the power of each card
 * \param Player - the struct of the player that the function is treating
 */
void SorteHand(Player* Player);

//Function that changes the score of each cards according to the chosen trump.
void ChangeScore(char trump_color, Player* Player);

//The function to make the AI play is very different from the function to make the user play.

/**
 * \fn void Game_of_South(Player* South, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color)
 * \brief these two functions will allow the player to play one card in a trick
 * \param South - the struct of the user, if it is turn to play
 * \param turn - it is two things : the number of turns it remains to do, and the size-1 (or the index of the last card) of the player's hand.
 * \param Card_in_theTrick - the index of the last card of the actual trick
 * \param TheTrick - the struct that will contain the cards of the trick
 * \param trump_color - the color of the trump
 */
void Game_of_South(Player* South, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color);

/**
 * \fn void Game_of_AI(Player* Player, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color)
 * \brief these two functions will allow the player to play one card in a trick
 * \param Player - the struct of the artificial player
 * \param turn - it is two things : the number of turns it remains to do, and the size-1 (or the index of the last card) of the player's hand.
 * \param Card_in_theTrick - the index of the last card of the actual trick
 * \param TheTrick - the struct that will contain the cards of the trick
 * \param trump_color - the color of the trump
 */
void Game_of_AI(Player* Player, int turn, int Card_in_theTrick, TricksStats* TheTrick, char trump_color);

/**
 * \fn void printTheTrick(TricksStats* TheTrick, Player* players)
 * \brief function that print the current trick
 * \param TheTrick - The structure that gathered the cards that will be played, the name of the winner... (see the rest above)
 * \param players - the array in which the players are placed according to when they play.
 */
void printTheTrick(TricksStats* TheTrick, Player* players);

/**
 * \fn Player* shiftPlayers(Player* playerArray, int Index)
 * \brief this function shift an array of four players from a specified number.
 * \param playerArray - the array of player we want to shift
 * \param Index - the index of the future first player of the future array, so the index of the winner of the trick in playerArray;
 * \return the array of player shifted
 */
Player* shiftPlayers(Player* playerArray, int Index);

/**
 * \fn int FindPosition(Player* playerArray,char* player)
 * \brief this function allows us to know where a given player is in an array of player.
 * \param playerArray - the array where we're looking for the player
 * \param player - the player we're looking for
 * \return the position of the player in the array
 */
int FindPosition(Player* playerArray,char* player);

void updatePlayerScore(Player* playerToUpdate,Player* ArrayOfPlayers);
/**
 * \fn void freeTheTrick(TrickStats* trick)
 * \brief a function useful to free a pointer on a TrickStats structure
 * \param trick - the trick to free
 */
void freeTheTrick(TricksStats* trick);

#endif /* Cartes_h */
