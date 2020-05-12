#include "menu.h"

int main()
{
    switch(main_menu()){
        case 1:
            clrscr();
            printf("\n\nWe will start a new game, keep ready !");
            /* distribution des cartes */
            bid_menu();

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
