#include"robotMethods.h"
#include "arenaSet.h"
#include "markerSet.h"
#include "robotSet.h"

int canMoveForward(const robot* robot, const arena* arena)
{
    int next_x=robot->coordinate.grid_x, next_y=robot->coordinate.grid_y;
    
    switch (robot->direction) 
    {
        case NORTH:
            next_y--;
            break;
        case EAST:
            next_x++;
            break;
        case SOUTH:
            next_y++;
            break;
        default:  //WEST
            next_x--;
    }

    if (next_x<0 || next_y<0 || next_x>=(arena->arenaTile_x) || next_y>=(arena->arenaTile_y))
        return 0;

    if (arena->map[next_x][next_y]==OBSTACLE || arena->map[next_x][next_y]==WALL)
        return 0;

    return 1;
}

void forward(robot* robot, const arena* arena)
{

    if (canMoveForward(robot, arena))
    {
        switch (robot->direction) 
        {
            case NORTH:
                robot->coordinate.grid_y--;
                break;
            case EAST:
                robot->coordinate.grid_x++;
                break;
            case SOUTH:
                robot->coordinate.grid_y++;
                break;
            default:  //WEST
                robot->coordinate.grid_x--;
        }
    }
}

void left(robot* robot)
{
    robot->direction = (robot->direction+3)%4;
}

void right(robot* robot)
{
    robot->direction = (robot->direction+1)%4;
}

int atMarker(const robot *robot, const arena *arena)
{
    if (arena->map[robot->coordinate.grid_x][robot->coordinate.grid_y] == MARKER)
        return 1;
    return 0;
}

int markerCount(const robot* robot)
{
    return robot->marker;
}

void pickUpMarker(robot* robot, arena* arena)
{
    if(atMarker(robot, arena))
    {
        arena->map[robot->coordinate.grid_x][robot->coordinate.grid_y]=EMPTY;
        robot->marker++;
        clearMarker(robot->coordinate.grid_x, robot->coordinate.grid_y, arena);
    }
}

void dropMarker(robot *robot, arena *arena)
{
    arena->map[robot->coordinate.grid_x][robot->coordinate.grid_y]=MARKER;
    robot->marker--;
    addMarker(robot->coordinate.grid_x, robot->coordinate.grid_y, arena);
}