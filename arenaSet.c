#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arenaSet.h"
#include "robotSet.h"

int markerNum;

int getRandomNum(int min, int max)
{
    return rand() % (max-min+1) + min;
}

void tileToPixel(int* ptr_x, int* ptr_y, const arena*arena)
{
    *ptr_x= (*ptr_x) * (TILE_SIZE) + (arena->topLeftPixel_x) + (TILE_SIZE/2.0);
    *ptr_y= (*ptr_y) * (TILE_SIZE) + (arena->topLeftPixel_y) + (TILE_SIZE/2.0);
}

void browseAndFindObj(int x[], int y[], int* numOfObject, const int target, const int maxSize, const arena*arena)
{
    int findObj=0;

    for (int i=0; i<(arena->arenaTile_x); i++)
        for (int j=0; j<(arena->arenaTile_y); j++)
        {
            if (arena->map[i][j] == target)
            {   
                if (findObj < maxSize)
                {
                    x[findObj] = i;
                    y[findObj] = j;
                    findObj++;
                }
            }
        }
    
    if (numOfObject!=NULL)
    {
        *numOfObject = findObj;
        return;
    }
    else
        return;
}

void getMarkerNum(arena *arena)
{
    int markerFind;
    int findList_x[(arena->arenaTile_x)*(arena->arenaTile_y)];
    int findList_y[(arena->arenaTile_x)*(arena->arenaTile_y)];
    browseAndFindObj(findList_x, findList_y, &markerFind, MARKER,arena->arenaTile_x*arena->arenaTile_y, arena);
    
    markerNum=markerFind;      
}

int isValidPosition(int x, int y, const arena* arena)
{
    if (x<0 || y<0 || x >= (arena->arenaTile_x) ||  y >= (arena->arenaTile_y))
        return 0;
    return 1;
}



void setArena(arena* arena)
{
    arena->arenaTile_x=getRandomNum(8, 15);
    arena->arenaTile_y=getRandomNum(8, 15);

    arena->topLeftPixel_x=WINDOW_SIZE/2-(arena->arenaTile_x)/2*TILE_SIZE;
    arena->topLeftPixel_y=WINDOW_SIZE/2-(arena->arenaTile_y)/2*TILE_SIZE;

    for (int i = 0; i < arena->arenaTile_x; i++)
    {
        for (int j = 0; j < arena->arenaTile_y; j++)
        {
            arena->map[i][j] = EMPTY;
        }
    }
}

void setWall(arena* arena)
{
    for (int i=0; i<arena->arenaTile_x; i++)
    {
        arena->map[i][0] = WALL;
        arena->map[i][arena->arenaTile_y-1] = WALL;
    }

    for (int j=0; j<arena->arenaTile_y; j++)
    {
        arena->map[0][j] = WALL;
        arena->map[arena->arenaTile_x-1][j] = WALL;
    }
}

void setRandomObstacle(arena* arena)
{
    for (int i=0; i<arena->arenaTile_x; i++)
        for (int j=0; j<arena->arenaTile_y; j++)
            if (isValidPosition(i, j, arena) && (arena->map[i][j] != WALL))
                if(getRandomNum(0, 99) < OBSTACLE_PROBE)
                    arena->map[i][j] = OBSTACLE; 
}

void setWallChunkObstacle(arena* arena)
{
    int chunkGenerateIndex = ((arena->arenaTile_x)+(arena->arenaTile_y))*2;
    int chunksNum = getRandomNum(chunkGenerateIndex/10, chunkGenerateIndex/5);
    
    for (int i = 0; i < chunksNum; i++)
    {
        //get the point at which the chunks begin to form
        int seed_x, seed_y;
        int sideToStick = getRandomNum(0, 3);
        switch (sideToStick)
        {
            case NORTH:
                seed_x = getRandomNum(1, arena->arenaTile_x-2);
                seed_y = 1;
                break;
            case EAST:
                seed_x = arena->arenaTile_x-2;
                seed_y = getRandomNum(1, arena->arenaTile_y-2);
                break;
            case SOUTH:
                seed_x = getRandomNum(1, arena->arenaTile_x-2);
                seed_y = arena->arenaTile_y-2;
                break;
            default: //WEST
                seed_x = 1;
                seed_y = getRandomNum(1, arena->arenaTile_y-2);
        }

        int chunkSize = getRandomNum(chunkGenerateIndex / 4, chunkGenerateIndex / 2);
        
        //randomly grow from the point
        for (int j = 0; j < chunkSize; j++)
        {
            if (isValidPosition(seed_x, seed_y, arena) && arena->map[seed_x][seed_y] == EMPTY)
            {
                arena->map[seed_x][seed_y] = OBSTACLE;
            }

            int growDirection = getRandomNum(0, 3);
            switch(growDirection)
            {
                case NORTH:
                    seed_y--;
                case EAST:
                    seed_x++;
                case SOUTH:
                    seed_y++;
                default: //WEST
                    seed_x--;
            }

            //in case out of available area
            if (seed_x < 1) 
                seed_x=1;

            if (seed_y < 1) 
                seed_y=1;

            if (seed_x >= arena->arenaTile_x - 1) 
                seed_x=(arena->arenaTile_x - 2);

            if (seed_y >= arena->arenaTile_y - 1) 
                seed_y=(arena->arenaTile_y - 2);

        }
    }
}

void setMarker(arena* arena)
{
    for (int i=0; i<arena->arenaTile_x; i++)
        for (int j=0; j<arena->arenaTile_y; j++)
            if (isValidPosition(i, j, arena) && (arena->map[i][j] != WALL) && (arena->map[i][j] != OBSTACLE))
                if(getRandomNum(0, 99) < MARKER_PROBE)
                    arena->map[i][j] = MARKER; 
}

void generateRandomArena(arena* arena, int gameMode)
{
    setArena(arena);
    setWall(arena);
    if (gameMode == 1)
        setRandomObstacle(arena);
    else
        setWallChunkObstacle(arena);
    setMarker(arena);
    getMarkerNum(arena);
}


//flood fill
void markConnectivity(int x, int y, const arena* arena, int connectedTileMap[MAX_ARENA_ROWS][MAX_ARENA_COLS])
{
    if (!isValidPosition(x, y, arena) )
        return;
    if(connectedTileMap[x][y] == 1)
        return;
    if (arena->map[x][y] == WALL || arena->map[x][y] == OBSTACLE)
        return;

    connectedTileMap[x][y] = 1;

    markConnectivity(x+1, y, arena, connectedTileMap);
    markConnectivity(x-1, y, arena, connectedTileMap);
    markConnectivity(x, y+1, arena, connectedTileMap);
    markConnectivity(x, y-1, arena, connectedTileMap);
}
    
int isGoodMap(arena* arena)
{
    int connectedTileMap[MAX_ARENA_ROWS][MAX_ARENA_COLS] = {{0}};
    int start_x = -1, start_y = -1;
    
    for (int i=0; i<(arena->arenaTile_x); i++) 
    {
        for (int j=0; j<(arena->arenaTile_y); j++) 
        {
            if (arena->map[i][j] == MARKER) 
            {
                start_x=i; 
                start_y=j; 
                break;
            }
        }
        if (start_x != -1) break;
    }
    if (start_x == -1) 
        return 0; 

    markConnectivity(start_x, start_y, arena, connectedTileMap);

    //fill the gaps between walls and obstacles
    
    for (int i=0; i<(arena->arenaTile_x); i++) 
        for (int j=0; j <(arena->arenaTile_y); j++) 
            if (arena->map[i][j] == EMPTY) 
                if (connectedTileMap[i][j] == 0) 
                    arena->map[i][j] = OBSTACLE;

    for (int i=0; i<(arena->arenaTile_x); i++) 
    {
        for (int j=0; j<(arena->arenaTile_y); j++) 
        {
            if (arena->map[i][j] == MARKER)
                if (connectedTileMap[i][j] == 0)
                    return 0; 

            if (connectedTileMap[i][j] == CONNECTED && arena->map[i][j]!=MARKER) 
            {
                arena->map[i][j] = CONNECTED_TILE;
            }
        }
    }
    return 1;
}

void generateGoodArena(arena* arena, int gameMode)
{   
    do 
    {
        generateRandomArena(arena, gameMode);
    }
    while (!isGoodMap(arena));

}