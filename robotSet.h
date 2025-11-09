#ifndef ROBOT_SET
#define ROBOT_SET

#include <stdbool.h>
#include "arenaSet.h"

#define ROBOT_HESITATE_TIME 10
#define RADIUS 20

typedef enum
{
    NORTH=0,
    EAST=1,
    SOUTH=2,
    WEST=3,
}Direction;

typedef struct grid
{
    int grid_x;
    int grid_y;
}grid;

typedef struct robot 
{
    grid coordinate;
    Direction direction;
    double radius; //the size of the robot
    int marker;
    int footPrint[MAX_ARENA_COLS][MAX_ARENA_ROWS];
}robot;


void calculateRobotVertex(int x, int y, int direction, double radius, int*vertexList_x, int*vertexList_y );
void generateRobot(robot* robot, const arena*arena);

#endif