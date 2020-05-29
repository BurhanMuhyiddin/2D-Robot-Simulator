#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

void initGrid(int, int);
void drawGrid();
void unit(int, int);
void drawBarrier(int, int);
int mapValues(int, int, int, int, int);
void clearBarriers();
void drawGoalPosition(int, int);
void drawRobot();
void dijkstra_debug();
void visualizePath();
int* decryptIndex(int);

#endif // ROBOT_H_INCLUDED
