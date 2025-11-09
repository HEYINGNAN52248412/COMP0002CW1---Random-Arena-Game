#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arenaSet.h"
#include "arenaDisplay.h"
#include "robotSet.h"
#include "alogrithm.h"


int main(int argc, char **argv)
{   
    //from coursework PDF
    //default mode
    int gameMode=0;

    if (argc == 1)
    { 
        gameMode = atoi(argv[1]);

    }

    srand(time(NULL));
    arena arena={ .map={{0}}};
    robot player={ .footPrint={{0}}};
    generateGoodArena(&arena, gameMode);
            
    generateRobot(&player, &arena);;
    displayArena(&arena);
    
    gameStart(&player, &arena);
    return 0;
}