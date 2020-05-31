#include "menu.h"
#include "Cartes.h"
#include "ia.h"

int main() {



    switch(main_menu()){


        case 1:
            srand(time(0));
            int sizeJ = 8;
            biddings* round_bets = NULL;
            int bet_choice = -1;

            Player North = {"North", (Cards*)malloc(sizeof(Cards)*8),(Cards*)malloc(sizeof(Cards)*8), 0};
            Player South = {"South", (Cards*)malloc(sizeof(Cards)*8),(Cards*)malloc(sizeof(Cards)*8), 0};
            Player East = {"East", (Cards*)malloc(sizeof(Cards)*8),(Cards*)malloc(sizeof(Cards)*8), 0};
            Player West= {"West", (Cards*)malloc(sizeof(Cards)*8),(Cards*)malloc(sizeof(Cards)*8), 0};
            Player* players  = (Player*) malloc(sizeof(Player)*4);

            players[0] = South;
            players[1] = West;
            players[2] = North;
            players[3] = East;

            char* lastPlayer = (char*)malloc(sizeof(char)*5); /* this string is used to know who is the last player who made a bet */

            clrscr();
            int contract = 80;
            Boolean coinche = FALSE; /* a variable which is equal to FALSE while nobody makes a coinche and then TRUE if someone makes a coinche */
            printf("\n\nWe will start a new game, keep ready !");
            /* cards are distributed */

            DistributeCards(&North, &South, &East, &West);
            /************************************************************************************************************************************************
             ************************************************Start of the game loop**************************************************************************
             ************************************************************************************************************************************************/

            /************************************************   Biddings    *********************************************************************************/

            int i = 0;
            while((i<4)&&(coinche==TRUE)){
                if(strcmp(players[i].name,"South") == 0){
                    while (bet_choice == -1){
                        bet_choice = bid_menu(contract,round_bets);
                        system("pause");
                        clrscr();
                    }
                } else {
                    bet_choice = AIbid(&(players[i]),contract,round_bets);
                }
                switch(bet_choice){
                        case 1:
                            if(strcmp(round_bets->bidding_array[round_bets->turn-1]->bet,"Capot")){
                                contract = 250;
                            } else if(strcmp(round_bets->bidding_array[round_bets->turn-1]->bet,"General")) {
                                contract = 500;
                            } else {
                                contract = atoi(round_bets->bidding_array[round_bets->turn-1]->bet);
                            }
                            break;
                        case 2:
                            if((round_bets->turn >= 2) && (strcmp(round_bets->bidding_array[round_bets->turn-1]->bet,"Coinche")==0)){
                                contract *= 2;
                                coinche = TRUE;
                            }
                            break;
                        default:
                            break;
                }
            i++;
            }

            if(coinche == TRUE){
                if(strcmp(round_bets->bidding_array[round_bets->turn-2]->player,"South")==0){
                    menu_surcoinche(round_bets);
                } else {
                    /* the ai can't make a surcoinche for the moment */
                }
            }
            lastPlayer = strcpy(lastPlayer,round_bets->bidding_array[round_bets->turn-1]->player);

            /*******************************************   Loop of the tricks  ******************************************************************************/

            players = shiftPlayers(players,FindPosition(players,lastPlayer), 4);



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

