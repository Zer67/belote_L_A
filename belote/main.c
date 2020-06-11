#include "menu.h"
#include "Cartes.h"
#include "AI.h"
#include "highscores.h"
#include <string.h>

int main() {

    Player North = {"North", (Cards*)malloc(sizeof(Cards)*8), 0, 1};
    Player South = {"South", (Cards*)malloc(sizeof(Cards)*8), 0, 1};
    Player East = {"East", (Cards*)malloc(sizeof(Cards)*8), 0, 2};
    Player West = {"West", (Cards*)malloc(sizeof(Cards)*8), 0, 2};
    srand(time(0));
    Player* players  = (Player*) malloc(sizeof(Player)*4);

    switch(main_menu()){
            


        case 1:
            while (North.score + South.score < 701 || East.score + West.score < 701 ){
                

                biddings round_bets;
                round_bets.turn = 0;
                round_bets.bidding_array = (bid**) malloc( sizeof(bid*));
                round_bets.bidding_array[0] = NULL;

                int bet_choice = -1, GameTurn = 7;


                TricksStats TheTrick = {(Cards*)malloc(sizeof(Cards)*4), (char*)malloc(sizeof(char)*5), 0, 0};

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
                 printf("\nLet's start the switch");
                while((i<4)&&(coinche==FALSE)){
                    if(players[i].name[0] == 'S'){
                        while (bet_choice == -1){
                            bet_choice = bid_menu(contract,&round_bets);
                            clrscr();
                        }
                    } else {
                        bet_choice = AIbid(&(players[i]),contract,&round_bets);
                    }
                   
                    switch(bet_choice){
                            case 1:
                                if(round_bets.bidding_array[round_bets.turn-1]->bet[0]=='C'){
                                    contract = 250;
                                } else if(round_bets.bidding_array[round_bets.turn-1]->bet[0] == 'G') {
                                    contract = 500;
                                } else {
                                    contract = atoi(round_bets.bidding_array[round_bets.turn-1]->bet);
                                }
                                break;
                            case 2:
                                if((round_bets.turn >= 2) && (round_bets.bidding_array[round_bets.turn-1]->bet[0]=='C')){
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
                    if(strcmp(round_bets.bidding_array[round_bets.turn-2]->player,"South")==0){
                        menu_surcoinche(&round_bets);
                    } else {
                        /* the ai can't make a surcoinche for the moment */
                    }
                }
                lastPlayer = strcpy(lastPlayer, round_bets.bidding_array[round_bets.turn-1]->player);
                ChangeScore(round_bets.bidding_array[round_bets.turn-1]->trump, &North);
                ChangeScore(round_bets.bidding_array[round_bets.turn-1]->trump, &South);
                ChangeScore(round_bets.bidding_array[round_bets.turn-1]->trump, &East);
                ChangeScore(round_bets.bidding_array[round_bets.turn-1]->trump, &West);
                SorteHand(&North);SorteHand(&South);SorteHand(&West);SorteHand(&East);
                

                /*******************************************   Loop of the tricks  ******************************************************************************/
                while (GameTurn > 0){
                    players = shiftPlayers(players,FindPosition(players,lastPlayer));
                    int y;
                    for (y =0; y < 4; y++) {
                        TheTrick.indexWinningCards = 0;

                        if (players[y].name[0] == 'S' ){
                            Game_of_South(&South, GameTurn, y, &TheTrick, round_bets.bidding_array[round_bets.turn-1]->trump);
                        }else {
                            Game_of_AI(&players[y], GameTurn, y, &TheTrick, round_bets.bidding_array[round_bets.turn-1]->trump);
                        }
                    }
                    printTheTrick(&TheTrick, players, y);
                    players = shiftPlayers(players, TheTrick.indexWinningCards);
                    for (int A = 0; A < 4; A++){
                        players[TheTrick.indexWinningCards].score += TheTrick.CardsOfTheTrick[A].point;
                    }
                    printf("\n%s wins the Trick", players[TheTrick.indexWinningCards].name);
                    GameTurn--;
                }
            }
            break;
        case 2:
            printf("\n\nLet's see the higher scores, could you beat them ?");

            ShowHighscore();
            /** simples tests ********/
            enterHighScore("Paul",1200);
            enterHighScore("Alice",1050);  /*a simple example for the moment */
            enterHighScore("Bob",1100);
            enterHighScore("Jerome", 1070);
            enterHighScore("Alice",1110);
            /** end of simples tests */
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
