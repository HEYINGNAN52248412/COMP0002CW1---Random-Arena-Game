# UCL COMP0002 C Coursework

This program will generate random pathfinding puzzles and present the process animation using a drawing software.

The robot will start from a randomly safe position within a randomly sized arena and stop once it has collected all the randomly placed markers.

You can freely choose the generation mode of the obstacles, either randomly or in the form of edge chunks.

The program can be successfully compiled and run on a Linux System.


## Complication and running the program:

To complie:
```
gcc -o Arena main.c graphics.c arenaSet.c arenaDisplay.c robotSet.c robotMethods.c robotDisplay.c alogrithm.c markerSet.c -lm
```
To run in stage5 mode (default):
```
./Arena 1 | java -jar drawapp-4.5.jar
```
To run in stage4 mode (more random obstacles):
```
./Arena 0 | java -jar drawapp-4.5.jar
```

## Essential Files:

### Core:
- `main.c`:  
The main entry point. It handles command-line arguments `gameMode`, initializes the random seed `srand`, and starts the game by calling `generateGoodArena` and`gameStart`.

### Arena Logic:
- `arenaSet.c`:  The "engine" of the arena. It handles the robust generation and validation of the map, including all `set...` functions for walls, obstacles, and markers.

- `markerSet.c`:     Utility functions to modify the map state when a marker is picked up (clearMarker) or dropped (addMarker).

- `arenaDisplay.c`:  Handles all static drawing. It is called once at the start to draw the `drawGrids`, `displayWalls`, `displayObstacles` and `displayMarkers`.

### Robot Logic:
- `robotSet.c`:  Defines the `robot` struct and generate it on the arena.

- `robotMethods.c`:
Defines the robot's actions and senses.

- `robotDisplay.c`:
Handles all dynamic drawing of the robot (as a triangle) for each frame of the animation.

### Brain:
- `alogrithm.c`:Contains primary pathfinding algorithm, a randomized backtracking algorithm and a control algorithm.


## Features:
- `High Randomness`: The following items are all randomly generated, with substantial variation in each run:

    - The number of tiles in rows and columns.

    - Irregular obstacle "clumps" generated using a "Drunkard's Walk" algorithm `setWallChunkObstacle`.

    - The number and position of obstacles and markers.

    - The start position and orientation of the robot, which is guaranteed to be on a "safe," reachable tile.

- `Advanced Algorithms`: The robot uses a full `Depth-First Search (DFS)` algorithm `search` to explore the map, using a footPrint 2D-array as its memory. It also uses a Randomized Backtracking algorithm `randomMove` to escape dead ends and U-shaped obstacle traps.

- `Robust Map Validation`: Before the game starts, the program runs a "Flood Fill" algorithm `isGoodMap` to validate that all markers are reachable and not isolated by obstacles. Invalid maps are automatically discarded and regenerated until a playable map is created `generateGoodArena`.