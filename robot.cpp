#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "robot.h"
#include <algorithm>
#include "myAlgorithms.h"

using namespace std;

int gridX, gridY;
int initialX = 0, initialY = 0;
int goalX = 35, goalY = 35;
int robotX = 3, robotY = 3;
int WINDOW_W = 500, WINDOW_H = 500;
bool isFull = false;
int** map_;
int** costMap_;
int** distanceFromStart;
int** parent;

int counter = 0;

extern int INF;

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

    initialX = robotX;
    initialY = robotY;
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
        map_[barrierCoordinates[i][1]][barrierCoordinates[i][0]] = 2;
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

    nX = initialX;
    nY = initialY;

    glColor3f(0.0, 1.0, 1.0);
    glRecti(nX, nY, nX+1, nY+1);
}

void drawRobot()
{
    glColor3f(0.0, 0.0, 1.0);

    robotX = optimalPath[counter][0];
    robotY = optimalPath[counter][1];

    if(optimalPath.size() == 0)     counter = 0;
    else if(counter != optimalPath.size()-1)      counter++;

    glRecti(robotX, robotY, robotX+1, robotY+1);
}

int mapValues(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void clearBarriers()
{
    barrierCoordinates.clear();
}

void visualizePath()
{
    glColor3f(1.0, 1.0, 0.0);
    int node = parent[goalY][goalX];

    optimalPath.clear();
    isFull = false;

    while(node != 0)
    {
        int* decryptedNodeIndex = decryptIndex(node);
        int x = decryptedNodeIndex[1];
        int y = decryptedNodeIndex[0];

        if(!isFull)
        {
            vector<int> tmp;
            tmp.push_back(x);
            tmp.push_back(y);
            optimalPath.push_back(tmp);
        }

        node = parent[y][x];

        if(node != 0)
        {
            glRecti(x, y, x+1, y+1);
        }
    }
    if(!isFull)
    {
        reverse(optimalPath.begin(), optimalPath.end());
        vector<int> tmp;
        tmp.push_back(goalX);
        tmp.push_back(goalY);
        optimalPath.push_back(tmp);
    }
    isFull = true;
}
