#include "arenaDisplay.h"
#include "arenaSet.h"

void displayArena(const arena* arena)
{   
    setWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    
    drawGrids(arena);
    displayObstacles(arena);
    displayWalls(arena);
}

void drawGrids(const arena* arena)
{
    background();
    setColour(black);
     
    for (int i=0; i <= arena->arenaTile_x; i++)
    {
        int current_x = (arena->topLeftPixel_x)+i*TILE_SIZE;
        int y_start = (arena->topLeftPixel_y);
        int y_end = (arena->topLeftPixel_y)+(arena->arenaTile_y)*TILE_SIZE;
        
        drawLine(current_x, y_start, current_x, y_end);
    }

    for (int j=0; j <= arena->arenaTile_y; j++)
    {
        int current_y = (arena->topLeftPixel_y)+j*TILE_SIZE;
        int x_start = (arena->topLeftPixel_x);
        int x_end = (arena->topLeftPixel_x)+(arena->arenaTile_x)*TILE_SIZE;

        drawLine(x_start, current_y, x_end, current_y);
    }
}

void drawWall(int x, int y)
{
    setColour(red);
    background();
    fillRect(x-TILE_SIZE/2, y-TILE_SIZE/2, TILE_SIZE+1, TILE_SIZE+1);
}

void displayWalls(const arena* arena)
{
    int x,y;
    for (int i=0; i < (arena->arenaTile_x); i++)
        for (int j=0; j < (arena->arenaTile_y); j++)
            if (arena->map[i][j] == WALL)
            {   
                x=i,y=j;
                tileToPixel(&x, &y, arena);
                drawWall(x,y);
            }
}

void drawObstacle(int x, int y)
{
    background();
    setColour(gray);
    fillRect(x-TILE_SIZE/2+5, y-TILE_SIZE/2+5, TILE_SIZE-9, TILE_SIZE-9);
    setColour(red);
    drawLine(x-TILE_SIZE/2, y-TILE_SIZE/2, x+TILE_SIZE/2-1, y+TILE_SIZE/2-1);
    drawLine(x-TILE_SIZE/2, y+TILE_SIZE/2-1, x+TILE_SIZE/2-1, y-TILE_SIZE/2);
}

void displayObstacles (const arena*arena)
{
    int findList_x[arena->arenaTile_x*arena->arenaTile_y];
    int findList_y[arena->arenaTile_x*arena->arenaTile_y];
    int numsOfObstacle;
    browseAndFindObj(findList_x, findList_y, &numsOfObstacle, OBSTACLE, arena->arenaTile_x*arena->arenaTile_y, arena);
    
    if (numsOfObstacle)
    {
        for (int i=0; i < numsOfObstacle; i++)
        {
            tileToPixel(&findList_x[i], &findList_y[i], arena);
            drawObstacle(findList_x[i], findList_y[i]);
        }       
    }
}

void drawMarker(int x, int y)
{
    foreground();
    setColour(yellow);
    fillRect(x-TILE_SIZE/2+5, y-TILE_SIZE/2+5, TILE_SIZE-9, TILE_SIZE-9);
}

void displayMarkers(const arena*arena)
{
    int findList_x[arena->arenaTile_x*arena->arenaTile_y];
    int findList_y[arena->arenaTile_x*arena->arenaTile_y];
    int numsOfMarker;
    browseAndFindObj(findList_x, findList_y, &numsOfMarker, MARKER, arena->arenaTile_x*arena->arenaTile_y, arena);
    
    if (numsOfMarker)
    {
        for (int i=0; i < numsOfMarker; i++)
        {
            tileToPixel(&findList_x[i], &findList_y[i], arena);
            drawMarker(findList_x[i], findList_y[i]);
        }       
    }
}
