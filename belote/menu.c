#include "menu.h"

/**
 * @param options - the array containing the options of the menu
 * @param nbre_option - number of options in the menu
 * @return an integer which is the option chosen (from 1 to nbre_option)
 */
int menu(char** options, int nbre_option){
    char input[20];
    int value;
    do {
        printf("\n\n");
        for(int i = 0;i<nbre_option; i++){
            printf("\t%d : %s\n", i+1, options[i]);
        }
        printf("\n\n choose your option :\t");
        scanf("%s", input);
        value = atoi(input);
    }while ((value<=0) || (value > nbre_option));
    return value;
}

/**
 * @return the option chosen in the main menu or -1 if there was a problem during the creation of the array main_options
 */
int main_menu(){
    int nbre_main_option = 3;
    char** main_options = (char**) malloc(sizeof(char*)*nbre_main_option);
    if (main_options == NULL){
        return -1;
    }
    printf("\n\t__________       .__          __                       __  .__ \n"
    "\t\\______   \\ ____ |  |   _____/  |_  ____             _/  |_|  |__   ____      _________    _____   ____ \n"
    "\t |    |  _// __ \\|  |  /  _ \\   __\\/ __ \\    ______  \\   __\\  |  \\_/ __ \\    / ___\\__  \\  /     \\_/ __ \\ \n"
    "\t |    |   \\  ___/|  |_(  <_> )  | \\  ___/   /_____/   |  | |   Y  \\  ___/   / /_/  > __ \\|  Y Y  \\  ___/ \n"
    "\t |______  /\\___  >____/\\____/|__|  \\___  >            |__| |___|  /\\___  >  \\___  (____  /__|_|  /\\___  > \n"
    "\t        \\/     \\/                      \\/                       \\/     \\/  /_____/     \\/      \\/     \\/ \n");
    main_options[0] = "Start a new game";
    main_options[1] = "Display the highscores";
    main_options[2] = "Exit";
    return menu(main_options, nbre_main_option);
}
