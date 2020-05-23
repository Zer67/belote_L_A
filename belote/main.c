#include "menu.h"
#include "Cartes.h"

int main() {

    int sizeJ = 8;


    biddings* round_bets = (biddings*) malloc(sizeof(biddings));
    round_bets = NULL;
    int bet_choice = -1;
    char** Cards = (char**) malloc(sizeof(char*)*32);


    switch(main_menu()){

    Player North = {"North", (Cards*)malloc(sizeof(Cards)*8),(Cards*)malloc(sizeof(Cards)*8), 0};
    Player South = {"South", (Cards*)malloc(sizeof(Cards)*8),(Cards*)malloc(sizeof(Cards)*8), 0};
    Player East = {"East", (Cards*)malloc(sizeof(Cards)*8),(Cards*)malloc(sizeof(Cards)*8), 0};
    Player West= {"West", (Cards*)malloc(sizeof(Cards)*8),(Cards*)malloc(sizeof(Cards)*8), 0};

    


        case 1:
            clrscr();
            int contract = 82;
            printf("\n\nWe will start a new game, keep ready !");
            /* distribution des cartes */

            DistributeCards(&North, &South, &East, &West);
            while (bet_choice == -1){
                bet_choice = bid_menu(contract,round_bets);
                clrscr();
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

