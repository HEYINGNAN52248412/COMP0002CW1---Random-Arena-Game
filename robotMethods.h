#ifndef ROBOT_METHODS
#define ROBOT_METHODS

#include "robotSet.h"


int canMoveForward(const robot* robot, const arena* arena);
int atMarker(const robot* robot, const arena*arena);
void forward(robot* robot, const arena* arena);
void left(robot* robot);
void right(robot* robot);
void pickUpMarker(robot* robot, arena* arena);
void dropMarker(robot* robot, arena* arena);
int markerCount(const robot* robot);

#endif