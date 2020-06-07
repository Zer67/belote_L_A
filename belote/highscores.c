#include "highscores.h"

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
        printf("\n\n\aNo one won a game for the moment, so there is nothing to show...");
    } else {
        printf("\n\tRANKING\tPLAYER\tSCORE\tNUMBER OF WINS\n\n");
        for(int i = 0; i<hs_array->nbrWinners;i++){
            printf("\t%d\t%s\t%d\t%d\n",hs_array->winners[i].line,hs_array->winners[i].name,hs_array->winners[i].bestScore,hs_array->winners[i].NbrWin);
        }
    }

}

HIGHSCORES* getHighscore(HIGHSCORES* hs){
    FILE* file_hs = fopen("highscore.txt","r");
    char playerName[40];
    int HighestScore;
    int nbrVictories;
    int i = 0;

    fscanf(file_hs,"%*[^\n]\n");
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

    return hs;
}
