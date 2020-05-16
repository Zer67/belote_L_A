#include "menu.h"
#include "Cartes.h"
/** function which erase all the things on the screen no matter the OS usedvoid clrscr()
 */
void clrscr(){
   #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
       system("clear");
   #endif

   #if defined(_WIN32) || defined(_WIN64)
       system("cls");
   #endif
}
/** a function which ask the player to choose a trump during the bidding time
 * @param title - the title of the menu to make the interface more a e s t h e t i c
 * @return a char which is the chosen trump
 */
char askForTrump(char* title){
    char trump;
    char trumpString[20];
    do{
        clrscr();
        printf("%s",title);
        printf("\nChoose a trump between 'H', 'D', 'S' and 'C':\t");
        scanf("%s",trumpString);
    } while((sscanf(trumpString,"%c",&trump)==EOF)||((trump != 'H') && (trump != 'D')&& (trump != 'S') && (trump != 'C')));
    return trump;
}

/** function that take an array of string in argument. Each element in this array is an option except the first element which is the title of the menu.
 * @param options - the array containing the options of the menu
 * @param nbr_option - number of options in the menu
 * @return an integer which is the option chosen (from 1 to nbr_option)
 */
int menu(char** options, int nbr_option){
    char input[20];
    int value;
    do {
        printf("\n\n\t%s\n",options[0]);
        for(int i = 1;i<=nbr_option; i++){
            printf("\t%d : %s\n", i, options[i]);
        }
        printf("\n\n choose your option :\t");
        scanf("%s", input);
        value = atoi(input);
    }while ((value<=0) || (value > nbr_option));
    return value;
}

/** a function that display the main menu of the game
 * @return the option chosen in the main menu or -1 if there was a problem during the creation of the array main_options
 */
int main_menu(){
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


/** display the bidding's menu
 */
void bid_menu(int current_contract){
    // DistributeCards(North, South, East, West); I can't compile with this function at this place
    FILE *bid_file;
    char bidString[20];
    int bid;
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
            clrscr();
            printf("\nyou just decided to skip, time for the player West to play");
            break;
        case 2:
            do{
                clrscr();
                printf("%s",bid_options[0]);
                printf("\ntell me your bid knowing that the last contract was %d:\t",current_contract);
                scanf("%s",bidString);
            } while((sscanf(bidString,"%d",&bid)==EOF)||(bid<current_contract));
            trump = askForTrump(bid_options[0]);
            printf("\nyou bet that you'll make a score of %d with the trump %c",bid, trump);
            /* write this bid in a file with the other bids to stock this data */
            bid_file = fopen("bid.txt","w");
            fprintf(bid_file,"south:\t%d\t%c",bid,trump);
            fclose(bid_file);

            break;
        case 3:
            clrscr();
            bid_file = fopen("bid.txt", "a+");

            char read_player[10];
            char read_bid[7]; /* it is not the same bid that we have in case 2 but here, it is  a string which let us put the value "capot" or "general" in the the second column */
            char read_trump;

            while((fscanf(bid_file,"%s\t%s\t%c\n",read_player,read_bid,&read_trump) != EOF)&&(strcmp(read_bid,"General")!=0)&&(strcmp(read_bid,"Capot")!=0)){
                fscanf(bid_file, "%*[^\n]\n");
            }
            if (getc(bid_file)!= EOF){
                printf("%s\n\n\tYou can't do that, someone already made a %s",bid_options[0], read_bid);
            } else {
                trump = askForTrump(bid_options[0]);
                fprintf(bid_file,"\nsouth:\tCapot\t%c",trump);
                printf("\nyou bet that you'll make a 'Capot' with the trump %c", trump);
            }

            break;
        case 4:
            break;
        case 5:
            break;
        default :
            printf("It seems that something wrong happened :(");
    }
}
