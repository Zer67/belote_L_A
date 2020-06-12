#include "highscores.h"
/** a function that display the highscore board
 */
void ShowHighscore(void){
    HIGHSCORES* hs_array = (HIGHSCORES*) malloc(sizeof(HIGHSCORES));
    hs_array->winners = NULL;
    hs_array->nbrWinners = 0;
    char* ascii_highscore ="\n\t  ___ ___ .__       .__\n\t /   |   \\|__| ____ |  |__             ______ ____  ___________   ____\n\t/    ~    \\  |/ ___\\|  |  \\   ______  /  ___// ___\\/  _ \\_  __ \\_/ __ \\\n\t\\    Y    /  / /_/  >   Y  \\ /_____/  \\___ \\\\  \\__(  <_> )  | \\/\\  ___/\n\t \\___|_  /|__\\___  /|___|  /         /____  >\\___  >____/|__|    \\___  > \n\t       \\/   /_____/      \\/               \\/     \\/                  \\/\n";
    hs_array = getHighscore(hs_array);

    /*************************************** HIGHSCORES DISPLAY ********************************************************************************************/
    clrscr();
    printf("\t%s\n", ascii_highscore);
    if (hs_array->winners == NULL){
        printf("\n\nNo one won a game for the moment, so there is nothing to show...");
    } else {
        printf("\n\tRANKING\tPLAYER\tSCORE\tNUMBER OF WINS\n\n");
        for(int i = 0; i<hs_array->nbrWinners;i++){
            printf("\t%d\t%s\t%d\t%d\n",hs_array->winners[i].line,hs_array->winners[i].name,hs_array->winners[i].bestScore,hs_array->winners[i].NbrWin);
        }
        freeHighscore(hs_array);
        free(hs_array);
    }

}

/** a function that add a score to the scoreboard or at least one win to the player and save it into "highscore.txt"
 * @param player - a string containing the name of the player who won
 * @param score - an integer containing that the player made during his game
 * @return an integer : TRUE if the name entered has a number of letter strictly lower to 8 or FALSE in the other case
 */
Boolean enterHighScore(char* player, int score){
    int sizePlayer = strlen(player);
    if(sizePlayer<8){

        HIGHSCORES* current_highscore = (HIGHSCORES*) malloc(sizeof(HIGHSCORES));
        current_highscore->winners = NULL;
        current_highscore->nbrWinners = 0;
        current_highscore = getHighscore(current_highscore);
        FILE* file_cur_hs = fopen("highscore.txt","w");
        fprintf(file_cur_hs,"PLAYER\tHIGHSCORE\tNBRWINS");

        if(current_highscore->winners == NULL){
            fprintf(file_cur_hs,"\n%s\t%d\t%d",player,score,1);
        } else {
            int index = findAwinner(player, *current_highscore);

            if(index == -1){

                index = 0;
                current_highscore->nbrWinners++;
                current_highscore->winners = (PEOPLE*) realloc(current_highscore->winners, sizeof(PEOPLE)*current_highscore->nbrWinners);

                while((index<current_highscore->nbrWinners)&&(score<current_highscore->winners[index].bestScore)){
                    index++;
                }
                if(index >= current_highscore->nbrWinners){
                    index--;

                } else{
                    for(int i=current_highscore->nbrWinners-1; i>index;i--){
                        current_highscore->winners[i] = current_highscore->winners[i-1];
                    }
                }
                current_highscore->winners[index].bestScore = score;
                current_highscore->winners[index].line = index;
                current_highscore->winners[index].name = NULL;
                free(current_highscore->winners[index].name);
                current_highscore->winners[index].name = (char*) malloc(sizeof(char)*(sizePlayer));
                current_highscore->winners[index].name = strcpy(current_highscore->winners[index].name, player);
                current_highscore->winners[index].NbrWin = 1;
            } else {
                if(score>current_highscore->winners[index].bestScore){
                    current_highscore->winners[index].bestScore = score;
                    PEOPLE mem;
                    while((index>0)&&(current_highscore->winners[index].bestScore>current_highscore->winners[index-1].bestScore)){
                        mem = current_highscore->winners[index];
                        current_highscore->winners[index] = current_highscore->winners[index-1];
                        current_highscore->winners[index-1] = mem;

                        current_highscore->winners[index].line = index;
                        current_highscore->winners[index-1].line = index-1;
                        index--;
                    }
                }
                current_highscore->winners[index].NbrWin++;
            }
            for(int i = 0; i<current_highscore->nbrWinners;i++){
                fprintf(file_cur_hs,"\n%s\t%d\t%d",current_highscore->winners[i].name,current_highscore->winners[i].bestScore,current_highscore->winners[i].NbrWin);
            }
        }
        fclose(file_cur_hs);
        freeHighscore(current_highscore);
        free(current_highscore);
        return TRUE;
    } else {
        printf("\nThe name entered was too big ! We couldn't afford that !\n");
        return FALSE;
    }
}

/** a function that allows us to write the highscore contained in the file into a struct which is more simple to manage
 * @param hs - a pointer on a struct HIGHSCORES which will contain the highscore
 * @return the pointer on HIGHSCORES hs which will be modified inside the function
 */
HIGHSCORES* getHighscore(HIGHSCORES* hs){
    FILE* file_hs = NULL;
    file_hs = fopen("highscore.txt","r");
    if(file_hs != NULL){

        char playerName[40];
        int HighestScore;
        int nbrVictories;
        int i = 0;

        if(fscanf(file_hs,"%*[^\n]\n")!=EOF){
            if (fscanf(file_hs,"%s\t%d\t%d\n",playerName,&HighestScore,&nbrVictories)!= EOF){
                hs->winners = (PEOPLE*) malloc(sizeof(PEOPLE));
                hs->nbrWinners = 1;
                hs->winners[i].line = i+1;
                hs->winners[i].name = (char*) malloc(sizeof(char)*strlen(playerName));
                hs->winners[i].name = strcpy(hs->winners[i].name, playerName);
                hs->winners[i].bestScore = HighestScore;
                hs->winners[i].NbrWin = nbrVictories;
                i++;
            }
            while(fscanf(file_hs,"%s\t%d\t%d\n",playerName,&HighestScore,&nbrVictories)!= EOF){
                hs->nbrWinners++;
                hs->winners = (PEOPLE*) realloc(hs->winners,sizeof(PEOPLE)*hs->nbrWinners);

                hs->winners[i].line = i+1;
                hs->winners[i].name = (char*) malloc(sizeof(char)*strlen(playerName));
                hs->winners[i].name = strcpy(hs->winners[i].name, playerName);
                hs->winners[i].bestScore = HighestScore;
                hs->winners[i].NbrWin = nbrVictories;
                i++;
            }
        }
        fclose(file_hs);
    }
    return hs;
}

/** a function allowing to find a given winner in a struct HIGHSCORES
 * @param name - the name of the player we're looking for
 * @param hs_array - a HIGHSCORES struct where we want to search our winner
 * @return the index of the player found in the winners field of hs_array OR -1 if the player isn't already there
 */
int findAwinner(char* name, HIGHSCORES hs_array){
    int i = 0;
    while((i<hs_array.nbrWinners) &&(strcmp(hs_array.winners[i].name, name)!=0)){
        i++;
    }
    if(i>= hs_array.nbrWinners){
        return -1;
    } else {
        return i;
    }
}


/** a function which will free all the fields of a HIGHSCORES struct  but it won't free the pointer on HIGHSCORES because this depends of the way the struct was implemented
 * @param hs - the HIGHSCORES struct to free
 */
void freeHighscore(HIGHSCORES* hs){
    for(int i = 0; i<hs->nbrWinners;i++){
        free(hs->winners[i].name);
    }
    free(hs->winners);
}
