#include <math.h>
#include "arenaSet.h"
#include "robotSet.h"

void calculateRobotVertex(int x, int y, int direction, double radius, int*vertexList_x, int*vertexList_y )
{   
    switch (direction) 
    {
        case NORTH:
            vertexList_x[0] = x;
            vertexList_y[0] = (int)round(y-radius);

            vertexList_x[1] = (int)round(x-((radius/2)*sqrt(3)));
            vertexList_y[1] = (int)round(y+radius/2);

            vertexList_x[2] = (int)round(x+((radius/2)*sqrt(3)));
            vertexList_y[2] = (int)round(y+radius/2);

            break;

        case EAST:
            vertexList_x[0] = (int)round(x+radius);
            vertexList_y[0] = y;

            vertexList_x[1] = (int)round(x-radius/2);
            vertexList_y[1] = (int)round(y-((radius/2)*sqrt(3)));

            vertexList_x[2] = (int)round(x-radius/2);
            vertexList_y[2] = (int)round(y+((radius/2)*sqrt(3)));

            break;

        case SOUTH:
            vertexList_x[0] = x;
            vertexList_y[0] = (int)round(y+radius);

            vertexList_x[1] = (int)round(x-((radius/2)*sqrt(3)));
            vertexList_y[1] = (int)round(y-radius/2);

            vertexList_x[2] = (int)round(x+((radius/2)*sqrt(3)));
            vertexList_y[2] = (int)round(y-radius/2);

            break;

        default:  //WEST
            vertexList_x[0] = (int)round(x-radius);
            vertexList_y[0] = y;

            vertexList_x[1] = (int)round(x+radius/2);
            vertexList_y[1] = (int)round(y-((radius/2)*sqrt(3)));

            vertexList_x[2] = (int)round(x+radius/2);
            vertexList_y[2] = (int)round(y+((radius/2)*sqrt(3)));
    }
}

void generateRobot(robot* robot, const arena*arena)
{   
    robot->radius=RADIUS;
    robot->marker=0;

    int emptyTiles_x[arena->arenaTile_x * arena->arenaTile_y];
    int emptyTiles_y[arena->arenaTile_x * arena->arenaTile_y];
    int numValidTiles;
    browseAndFindObj(emptyTiles_x, emptyTiles_y, &numValidTiles, CONNECTED_TILE, arena->arenaTile_x * arena->arenaTile_y, arena);

    if (numValidTiles == 0)
    {
        return;
    }

    int randomValidTile = getRandomNum(0, numValidTiles - 1);
    int randomDirection=getRandomNum(0, 3);

    (robot->coordinate.grid_x) = emptyTiles_x[randomValidTile];
    (robot->coordinate.grid_y) = emptyTiles_y[randomValidTile];
    (robot->direction) = randomDirection; 

}

