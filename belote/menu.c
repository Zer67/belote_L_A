#include "menu.h"
/**
 * \fn void clrscr(void)
 * \brief function which erase all the things on the screen no matter the OS usedvoid clrscr()
 */
void clrscr(void){
   #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
       system("clear");
   #endif

   #if defined(_WIN32) || defined(_WIN64)
       system("cls");
   #endif
}
/**
 * \fn char askForTrump(void)
 * \brief a function which ask the player to choose a trump during the bidding time
 * \return a char which is the chosen trump
 */
char askForTrump(void){
    char trump;
    char trumpString[20];
    do{
        printf("\nChoose a trump between 'H', 'D', 'S' and 'C':\t");
        scanf("%s",trumpString);
    } while((sscanf(trumpString,"%c",&trump)==EOF)||((trump != 'H') && (trump != 'D')&& (trump != 'S') && (trump != 'C')&&(trump != 'u')));
    return trump;
}



/**
 * \fn int menu(char** options, int nbre_option)
 * \brief a function displaying a menu with his title according to an array of strings
 * \param options - the array containing the options of the menu
 * \param nbre_option - number of options in the menu
 * \return an integer which is the option chosen (from 1 to nbre_option)
 */
int menu(char** options, int nbr_option){
    char input[20];
    int value;
    do {
        printf("%s", options[0]);
        printf("\n\n");
        for(int i = 1;i<=nbr_option; i++){
            printf("\t%d : %s\n", i, options[i]);
        }
        printf("\n\n choose your option :\t");
        scanf("%s", input);
        value = atoi(input);
    }while ((value<=0) || (value > nbr_option));
    return value;
}

/**
 * \fn int main_menu(void)
 * \brief a simple function which display the main menu and get the input of the player
 * \return the option chosen in the main menu
 */
int main_menu(void){
    int nbr_main_option = 3;
    char** main_options = (char**) malloc(sizeof(char*)*(1+nbr_main_option));
    int return_menu = -1;
    if (main_options == NULL){
        return -1;
    }
    printf("\n\t__________       .__          __                       __  .__ \n"
    "\t\\______   \\ ____ |  |   _____/  |_  ____             _/  |_|  |__   ____      _________    _____   ____ \n"
    "\t |    |  _// __ \\|  |  /  _ \\   __\\/ __ \\    ______  \\   __\\  |  \\_/ __ \\    / ___\\__  \\  /     \\_/ __ \\ \n"
    "\t |    |   \\  ___/|  |_(  <_> )  | \\  ___/   /_____/   |  | |   Y  \\  ___/   / /_/  > __ \\|  Y Y  \\  ___/ \n"
    "\t |______  /\\___  >____/\\____/|__|  \\___  >            |__| |___|  /\\___  >  \\___  (____  /__|_|  /\\___  > \n"
    "\t        \\/     \\/                      \\/                       \\/     \\/  /_____/     \\/      \\/     \\/ \n");
    main_options[0] = "";
    main_options[1] = "Start a new game";
    main_options[2] = "Display the highscores";
    main_options[3] = "Exit";
    return_menu = menu(main_options, nbr_main_option);
    free(main_options);
    return return_menu;
}


/**
 * \fn int bid_menu(int current_contract, biddings* struct_bid)
 * \brief display the menu of bidding and allow the player to make a bid
 * \param current_contract - the value of the current contract
 * \param struct_bid - the structure containing all the bets
 * \return an integer : -1 if no correct choice have been chosen, 0 if the player skipped, 1 if the player made a "classic" bet, 2 if the player made a coinche
 */
int bid_menu(int current_contract, biddings* struct_bid){
    // DistributeCards(North, South, East, West); I can't compile with this function at this place
    char bidString[20];
    int bid;
    int i=0; /* variable used to iterate in few while loops */
    char trump;
    int nbr_bid_option = 5;
    int choice = 0;
    char** bid_options = (char**) malloc(sizeof(char*)*(1+nbr_bid_option));
    if (bid_options == NULL){
        choice = -1;
    } else {
    bid_options[0] ="\n___.   .__    .___  .___.__                   __  .__\n\\_ |__ |__| __| _/__| _/|__| ____    ____   _/  |_|__| _____   ____\n | __ \\|  |/ __ |/ __ | |  |/    \\  / ___\\  \\   __\\  |/     \\_/ __ \\ \n | \\_\\ \\  / /_/ / /_/ | |  |   |  \\/ /_/  >  |  | |  |  Y Y  \\  ___/\n |___  /__\\____ \\____ | |__|___|  /\\___  /   |__| |__|__|_|  /\\___  >\n\t\b\b\b\\/        \\/    \\/         \\//_____/                  \\/     \\/\n";
    bid_options[1] ="Skip";
    bid_options[2] ="Bid";
    bid_options[3] ="Capot";
    bid_options[4] ="General";
    bid_options[5] = "Coinche";
    choice = menu(bid_options,nbr_bid_option);
    }
    switch (choice){
        case 1:
            printf("\nYou just decided to skip, time for the player West to play\n");
            return 0;
        case 2:
            do{
                printf("\nTell me your bid knowing that the last contract was %d:\t",current_contract);
                scanf("%s",bidString);
            } while((strcmp(bidString,"u")!=0)&&((sscanf(bidString,"%d",&bid)==EOF)||(bid<current_contract)||(bid%10 != 0)));
            if (strcmp(bidString,"u")==0){
                break;
            }
            trump = askForTrump();
            if (trump == 'u'){
                break;
            }
            printf("\nYou bet that you'll make a score of %d with the trump %c",bid, trump);
            /* write this bid in a structure with the other bids to stock this data */

            struct_bid = AddABet(struct_bid, "south",5,bidString,strlen(bidString), trump);
            printBids(*struct_bid);
            return 1;
        case 3:
            i =0;
            if (struct_bid->bidding_array[0] != NULL){
                while((i<struct_bid->turn)&&(strcmp(struct_bid->bidding_array[i]->bet,"General")!=0)&&(strcmp(struct_bid->bidding_array[i]->bet,"Capot")!=0)){
                    i++;
                }
                if (i >= struct_bid->turn){
                    trump = askForTrump();
                    if (trump == 'u'){
                        break;
                    }
                } else {
                    printf("\n\n\tYou can't do that, someone already made a Capot");
                    break;
                }
            } else {
                trump = askForTrump();
                if (trump == 'u'){
                    break;
                }
            }

            struct_bid = AddABet(struct_bid, "south",5,"Capot",5, trump);

            printf("\nyou bet that you'll make a 'Capot' with the trump %c\n", trump);
            printBids(*struct_bid);
            return 1;



            break;
        case 4:

            i =0;
            if (struct_bid->bidding_array[0] != NULL){
                while((i<struct_bid->turn)&&(strcmp(struct_bid->bidding_array[i]->bet,"General")!=0)){
                i++;
                }
                if (i >= struct_bid->turn){
                    trump = askForTrump();
                    if (trump == 'u'){
                        break;
                    }
                } else {
                    printf("\n\n\tYou can't do that, someone already made a General");
                    break;
                }
            } else {
                trump = askForTrump();
                if (trump == 'u'){
                        break;
                }
            }
                struct_bid = AddABet(struct_bid, "south",5,"General",7, trump);

                printf("\nyou bet that you'll make a 'General' with the trump %c\n", trump);
                printBids(*struct_bid);
                return 1;

            break;
        case 5:
            i=0;
            printf("%s",bid_options[0]);
            if ((struct_bid == NULL) || (struct_bid->turn<=1)){
                printf("nobody makes a bid, you can't bet a Coinche !");
            } else if(strcmp(struct_bid->bidding_array[struct_bid->turn-1]->bet,"Coinche")==0){
                trump = askForTrump();
                if (trump == 'u'){
                    break;
                }
                struct_bid = AddABet(struct_bid, "south",5,"Coinche",7, trump);

                printf("\nyou bet that you'll make a 'Coinche' with the trump %c\n", trump);
                printBids(*struct_bid);
                return 2;
            } else {
                printf("somebody already makes 'Coinche', you can't do coinche now");
            }

            break;
        default :
            printf("It seems that something wrong happened :(\n");

    }
    printf("Let's come back to your choice !");
    return -1;
}

/**
 * \fn void menu_surcoinche(biddings* struct_bid)
 * \brief display the menu of surcoinche if someone made a coinche
 * \param struct_bid - the structure containing all the bets
 */
void menu_surcoinche(biddings* struct_bid){
    char trump;
    char surcoinche_y_n = 'y';
    char surcoincheString[20];
    printf("_________        .__              .__\n"
            "\\_   ___ \\  ____ |__| ____   ____ |  |__   ____"
            "/    \\  \\/ /  _ \\|  |/    \\_/ ___\\|  |  \\_/ __ \\n"
            "\\     \\___(  <_> )  |   |  \\  \\___|   Y  \\  ___/\n"
            " \\______  /\\____/|__|___|  /\\___  >___|  /\\___  >\n"
            "        \\/               \\/     \\/     \\/     \\/");

    do{
        printf("Someone make a coinche on your bet. You could make a surcoinche, would you ?(answer with 'y' or 'n')\t");
        scanf("%s",surcoincheString);
        printf("\n\n");
    } while((sscanf(surcoincheString,"%c",&surcoinche_y_n)==EOF) && ((surcoinche_y_n!='y')||(surcoinche_y_n!='n')));
    if (surcoinche_y_n == 'y'){
        trump = struct_bid->bidding_array[struct_bid->turn-1]->trump;
        struct_bid = AddABet(struct_bid, "south",5,"Surcoinche",10, trump);
        printf("\nyou bet that you'll make a 'SurCoinche'\n");
    } else {
        printf("let's go back to the game\n");
    }
}

/**
 * \fn void printBids(biddings b)
 * \brief a function useful to display a structure of type biddings
 * \param b - the structure to display
 */
void printBids(biddings b){
    for(int i =0; i<b.turn;i++){

        printf("\nPlayer %d :\t%s\t%s\t%c\n",i+1,b.bidding_array[i]->player,b.bidding_array[i]->bet,b.bidding_array[i]->trump);
    }
}

/**
 * \fn biddings* AddABet(biddings* b, char* GivenPlayer, int sizeGivenPlayer, char* GivenBet, int sizeGivenBet, char GivenTrump)
 * \brief A really significant function to add a bet inside a biddinngs struct
 * \param b - a pointer on the struct of type biddings we want to modify
 * \param GivenPlayer - the name of the player who made the bet
 * \param sizeGivenPlayer - the size of the string containing the name of the player
 * \param GivenBet - the bet that the player want to make inside a string
 * \param sizeGivenBet - the size of the string containing the bet
 * \param GivenTrump - the trump that the player chose ( can be 'H', 'C', 'D' or 'S')
 * \return the pointer on the struct b modified
 */
biddings* AddABet(biddings* b, char* GivenPlayer, int sizeGivenPlayer, char* GivenBet, int sizeGivenBet, char GivenTrump){

    b->turn++;
    b->bidding_array = (bid**) realloc(b->bidding_array, sizeof(bid*)*b->turn);

    b->bidding_array[b->turn-1] = (bid*) malloc(sizeof(bid));
    b->bidding_array[b->turn-1]->player = (char*) malloc( sizeof(char)*sizeGivenPlayer);
    b->bidding_array[b->turn-1]->bet = (char*) malloc( sizeof(char)*sizeGivenBet);
    b->bidding_array[b->turn-1]->player = strcpy(b->bidding_array[b->turn-1]->player, GivenPlayer);
    b->bidding_array[b->turn-1]->bet = strcpy(b->bidding_array[b->turn-1]->bet,GivenBet);
    b->bidding_array[b->turn-1]->trump = GivenTrump;
    return b;
}
