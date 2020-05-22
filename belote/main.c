#include "menu.h"
#include "Cartes.h"

int main() {
    Cards* North = (Cards*)malloc(sizeof(Cards)*8);
    Cards* South = (Cards*)malloc(sizeof(Cards)*8);
    Cards* East = (Cards*)malloc(sizeof(Cards)*8);
    Cards* West = (Cards*)malloc(sizeof(Cards)*8);
    
    
    DistributeCards(North, South, East, West);

  switch(main_menu()){
        case 1:
            clrscr();
            printf("\n\nWe will start a new game, keep ready !");
            /* distribution des cartes */
              DistributeCards(North, South, East, West);
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
