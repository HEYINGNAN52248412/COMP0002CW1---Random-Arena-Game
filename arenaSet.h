#ifndef ARENA_SET
#define ARENA_SET


#include "graphics.h"

#define WINDOW_SIZE 1500
#define TILE_SIZE 50
#define MAX_ARENA_COLS 50
#define MAX_ARENA_ROWS 50

#define MARKER_PROBE 10
#define OBSTACLE_PROBE 20

extern int markerNum;

typedef enum
{
    stadiumMode=0,
    randomMode=1,
    
}ArenaMode;

typedef enum
{
    NOTCONNECTED=0,
    CONNECTED=1,
}ConnectStatus;

typedef enum
{
    EMPTY=0,
    WALL=1,
    OBSTACLE=2,
    MARKER=3,
    CONNECTED_TILE=4,
}Type;

typedef struct arena
{
    int arenaTile_x;
    int arenaTile_y;
    int map[MAX_ARENA_COLS][MAX_ARENA_ROWS];
    int topLeftPixel_x;
    int topLeftPixel_y;
}arena;

//tools
void tileToPixel(int* ptr_x, int* ptr_y, const arena*arena);
void browseAndFindObj(int x[], int y[], int* numOfObject, const int target, const int maxSize, const arena*arena);
int getRandomNum(int min, int max);
void getMarkerNum(arena *arena);
int isValidPosition(int x, int y, const arena* arena);

//generate random good Arena
void setArena(arena* arena);
void setWall(arena* arena);
void setRandomObstacle(arena* arena);
void setWallChunkObstacle(arena* arena);
void setMarker(arena* arena);
void generateRandomArena(arena* arena, int gameMode);

void markConnectivity(int x, int y, const arena* arena, int validation_footprint[MAX_ARENA_ROWS][MAX_ARENA_COLS]);
int isGoodMap(arena* arena);
void generateGoodArena(arena* arena, int gameMod);

#endif