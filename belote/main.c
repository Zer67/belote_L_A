#include "menu.h"
#include "Cartes.h"

int main() {
    int sizeJ = 8;

    char** North = (char**)malloc(sizeof(char*)*sizeJ);
    char** South = (char**)malloc(sizeof(char*)*sizeJ);
    char** East = (char**)malloc(sizeof(char*)*sizeJ);
    char** West = (char**)malloc(sizeof(char*)*sizeJ);

    biddings* round_bets = (biddings*) malloc(sizeof(biddings));
    round_bets = NULL;
    DistributeCards(North, South, East, West);
    int bet_choice = -1;
    char** Cards = (char**) malloc(sizeof(char*)*32);


    switch(main_menu()){
        case 1:
            clrscr();
            int contract = 82;
            printf("\n\nWe will start a new game, keep ready !");
            /* distribution des cartes */
            while (bet_choice == -1){
                bet_choice = bid_menu(contract,round_bets);
            }
            break;
        case 2:
            printf("\n\nLet's see the higher scores, could you beat them ?");
            break;
        case 3:
            printf("\n\nGoodbye :'(");
            return EXIT_SUCCESS;
        case -1:
            printf("\n\nError during the initialization, please restart the game");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
