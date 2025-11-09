#ifndef ARENA_DISPLAY
#define ARENA_DISPLAY

#include "arenaSet.h"

void displayArena(const arena* arena);

void drawGrids(const arena* arena);

void drawWall(int x, int y);
void displayWalls(const arena* arena);

void drawObstacle(int x, int y);
void displayObstacles (const arena*arena);


void drawMarker(int x, int y);
void displayMarkers( const arena*arena);

#endif