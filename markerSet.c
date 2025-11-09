#include "markerSet.h"
#include "arenaSet.h"


void clearMarker(const int x, const int y, arena* arena)
{
    arena->map[x][y] = EMPTY;
}

void addMarker(const int x, const int y, arena* arena)
{
    arena->map[x][y] = MARKER;
}