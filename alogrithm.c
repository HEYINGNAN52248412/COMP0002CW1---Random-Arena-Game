#include "alogrithm.h"
#include "arenaSet.h"
#include "arenaDisplay.h"
#include "robotMethods.h"
#include "robotSet.h"
#include "robotDisplay.h"


int isNotVisited(int x, int y, const robot* robot, const arena* arena)
{
    if (!isValidPosition(x, y, arena))
        return 0; 
    if (arena->map[x][y] == WALL || arena->map[x][y] == OBSTACLE)
        return 0;
    if (robot->footPrint[x][y] == 1) 
        return 0; 
    
    return 1;
}

void search(robot *robot, const arena *arena)
{
    int next_x = robot->coordinate.grid_x;
    int next_y = robot->coordinate.grid_y; 

    robot->footPrint[next_x][next_y] = 1;
    
    if (isNotVisited(next_x, next_y-1, robot, arena))
    {
        robot->direction=NORTH;
        return;
    }

    if (isNotVisited(next_x+1, next_y, robot, arena))
    {
        robot->direction=EAST;
        return;
    }

    if (isNotVisited(next_x, next_y+1, robot, arena))
    {
        robot->direction=SOUTH;
        return;
    }

    if (isNotVisited(next_x-1, next_y, robot, arena))
    {
        robot->direction=WEST;
        return;
    }
    
    //backtrack
    randomMove(robot, arena);
    return;
}

void randomMove(robot* robot , const arena* arena)
{
    if (canMoveForward(robot, arena))
    {   
        if (getRandomNum(0, 9)<6)
            return;
        if (getRandomNum(0, 1))
        {
            left(robot);
            return;
        }
        right(robot);
        return;    
    }
    else
    {
        if (getRandomNum(0, 1))
        {
            left(robot); 
            if (canMoveForward(robot, arena))
                return;
            else
            {
                right(robot);
                right(robot);
                if (canMoveForward(robot, arena))   
                    return;
                else
                {
                    right(robot);
                    return;
                }
            }        
        }
        else
        {
            right(robot);
            if (canMoveForward(robot, arena))
                    return;
            else
            {
                left(robot);
                left(robot);
                if (canMoveForward(robot, arena))   
                    return;
                else
                {
                    left(robot);
                    return;
                }
            }
        }
    }
}

void gameStart(robot* robot, arena*arena)
{
    while (1) 
    {
        foreground();
        clear();
        displayMarkers(arena);
        displayRobot(robot, arena);
        sleep(100);

        if (robot->marker == markerNum)
        {
            setColour(black);
            setStringTextSize(50);
            drawString("Finish!", 100, 100);
            setStringTextSize(40);
            drawString("All the markers are found!", 100, 160);
            break; 
        }
    
        if (atMarker(robot, arena))
        {    
            pickUpMarker(robot, arena);
        }
        else
        {   
            //only one action in one frame
            Direction previousDirection = robot->direction;
            search(robot, arena); 

            if (previousDirection == robot->direction)
                if (canMoveForward(robot, arena))
                    forward(robot, arena);
        } 
    }
}

