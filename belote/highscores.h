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

void ShowHighscore(void);

HIGHSCORES* getHighscore(HIGHSCORES* hs);
#endif // HIGHSCOREHEADER
