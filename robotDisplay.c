#include "robotDisplay.h"

int robotVertexList_x[3];
int robotVertexList_y[3];

void drawRobot()
{
    foreground();
    setColour(blue);
    fillPolygon(3, robotVertexList_x, robotVertexList_y);
    setColour(red);
    setLineWidth(3);
    drawLine(robotVertexList_x[1], robotVertexList_y[1], robotVertexList_x[2], robotVertexList_y[2]);  
}

void displayRobot(const robot* robot, const arena* arena)
{
    int pixel_x = (robot->coordinate.grid_x); 
    int pixel_y = (robot->coordinate.grid_y);

    tileToPixel(&pixel_x, &pixel_y, arena);
    calculateRobotVertex(pixel_x, pixel_y, robot->direction, robot->radius, robotVertexList_x, robotVertexList_y);

    drawRobot();
}