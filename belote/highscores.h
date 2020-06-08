#ifndef HIGHSCOREHEADER
#define HIGHSCOREHEADER
#include "menu.h"

typedef struct {
    int line; /* line of the player in the file 'higschores.txt' */
    char* name; /*name of the player that he entered at the beginning of the game */
    int bestScore; /* we'll only display the best score of the player */
    int NbrWin; /* the number of times the player won */
} PEOPLE;

typedef struct {
    int nbrWinners; /* length of the array of player */
    PEOPLE* winners; /* an array of people containing all the people who win at the game */
} HIGHSCORES;
/** a function that display the highscore board
 */
void ShowHighscore(void);
/** a function that add a score to the scoreboard or at least one win to the player and save it into "highscore.txt"
 * @param player - a string containing the name of the player who won
 * @param score - an integer containing that the player made during his game
  * @return an integer : TRUE if the name entered has a number of letter strictly lower to 8 or FALSE in the other case
 */
Boolean enterHighScore(char* player, int score);
/** a function that allows us to write the highscore contained in the file into a struct which is more simple to manage
 * @param hs - a pointer on a struct HIGHSCORES which will contain the highscore
 * @return the pointer on HIGHSCORES hs which will be modified inside the function
 */
HIGHSCORES* getHighscore(HIGHSCORES* hs);

/** a function which will free all the fields of a HIGHSCORES struct  but it won't free the pointer on HIGHSCORES because this depends of the way the struct was implemented
 * @param hs - the HIGHSCORES struct to free
 */
void freeHighscore(HIGHSCORES* hs);

/** a function allowing to find a given winner in a struct HIGHSCORES
 * @param name - the name of the player we're looking for
 * @param hs_array - a HIGHSCORES struct where we want to search our winner
 * @return the index of the player found in the winners field of hs_array OR -1 if the player isn't already there
 */
int findAwinner(char* name, HIGHSCORES hs_array);
#endif // HIGHSCOREHEADER
