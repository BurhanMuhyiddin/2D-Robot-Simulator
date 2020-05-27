#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "robot.h"

using namespace std;

int gridX, gridY;
int goalX = 5, goalY = 10;
int robotX = 20, robotY = 20;
int WINDOW_W = 500, WINDOW_H = 500;
int** map_;
int** costMap_;
int** distanceFromStart;
int* parentX;
int* parentY;

vector< vector <int> > barrierCoordinates;
vector< vector <int> > optimalPath;

/***************

1 - clear
2 - obstacle
3 - visited
5 - start
6 - destination

****************/

void initGrid(int x, int y)
{
    gridX = x;
    gridY = y;

    map_ = new int*[gridY];
    costMap_ = new int*[gridY];
    distanceFromStart = new int*[gridY];
    parentX = new int[gridX];
    parentY = new int[gridY];
    for(int i = 0; i < gridX; i++)
    {
        map_[i] = new int[gridX];
        costMap_[i] = new int[gridX];
        distanceFromStart[i] = new int[gridX];
    }

    for(int i = 0; i < gridY; i++)
    {
        parentY[i] = -1;
    }

    for(int i = 0; i < gridX; i++)
    {
        parentX[i] = -1;
    }

    for(int i = 0; i < gridY; i++)
    {
        for(int j = 0; j < gridX; j++)
        {
            map_[i][j] = 1;
            costMap_[i][j] = abs(robotX - j) + abs(robotY - i);
            distanceFromStart[i][j] = INF;
        }
    }
    map_[robotY][robotX] = 5;
    map_[goalY][goalX] = 6;
    distanceFromStart[robotY][robotX] = 0;
    /*for(int i = 0; i < gridY; i++)
    {
        for(int j = 0; j < gridX; j++)
        {
            cout << distanceFromStart[i][j] << " ";
        }
        cout << endl;
    }*/
}

void drawGrid()
{
    for(int x = 0; x < gridX; x++)
    {
        for(int y = 0; y < gridY; y++)
        {
            unit(x, y);
        }
    }
}

void unit(int x, int y)
{
    if(x == 0 || y == 0 || x == gridX-1 || y == gridY-1)
    {
        glLineWidth(3.0);
        glColor3f(1.0, 0.0, 0.0);
    }else
    {
        glLineWidth(1.0);
        glColor3f(1.0, 1.0, 1.0);
    }

    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x+1, y);
        glVertex2f(x+1, y+1);
        glVertex2f(x, y+1);
    glEnd();
}

void drawBarrier(int x, int y)
{
    int nX = mapValues(x, 0, WINDOW_W ,0, gridX);
    int nY = mapValues(y, 0, WINDOW_H ,0, gridY);
    nY = (gridY - 1) - nY;

    if((nX != 0 && nY != 0) && (nX != gridX - 1 && nY != gridY - 1))
    {
        vector<int> temp;
        temp.push_back(nX);
        temp.push_back(nY);

        barrierCoordinates.push_back(temp);
    }

    glColor3f(1.0, 0.0, 0.0);
    for(int i = 0; i < barrierCoordinates.size(); i++)
    {
        glRecti(barrierCoordinates[i][0], barrierCoordinates[i][1],
                barrierCoordinates[i][0]+1, barrierCoordinates[i][1]+1);
    }
}

void drawGoalPosition(int x, int y)
{
    //int nX = mapValues(x, 0, WINDOW_W ,0, gridX);
    //int nY = mapValues(y, 0, WINDOW_H ,0, gridY);
    //nY = (gridY - 1) - nY;

    int nX = x;
    int nY = y;

    glColor3f(0.0, 1.0, 0.0);
    glRecti(nX, nY, nX+1, nY+1);
}

void drawRobot()
{
    glColor3f(0.0, 0.0, 1.0);
    glRecti(robotX, robotY, robotX+1, robotY+1);
    //robotX++;
    //if(robotX == gridX - 1)     robotX = 1;
    //if(robotY == gridY - 1)     robotY = 1;
}

int mapValues(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void clearBarriers()
{
    barrierCoordinates.clear();
}

/*void visualizePath()
{
    if()
}*/
