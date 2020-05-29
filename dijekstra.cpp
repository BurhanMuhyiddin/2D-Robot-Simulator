#include "dijekstra.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "myAlgorithms.h"

using namespace std;

// !!!Warning: change initialX and initialY to startX and startY, because as robot moves the coordinates will change

int INF = 999999;

extern int initialX, initialY, goalX, goalY, gridX, gridY;
extern int** map_;
extern int** costMap_;
extern int** distanceFromStart;
extern int** parent;
extern vector< vector <int> > optimalPath;

void dijkstraInit()
{
    map_ = new int*[gridY];
    costMap_ = new int*[gridY];
    distanceFromStart = new int*[gridY];
    parent = new int*[gridY];

    for(int i = 0; i < gridX; i++)
    {
        map_[i] = new int[gridX];
        costMap_[i] = new int[gridX];
        distanceFromStart[i] = new int[gridX];
        parent[i] = new int[gridX];
    }

    for(int i = 0; i < gridY; i++)
    {
        for(int j = 0; j < gridX; j++)
        {
            if(i == (gridY-1) || j == (gridX-1) || i == 0 || j == 0)
                map_[i][j] = 2;
            else
                map_[i][j] = 1;
            costMap_[i][j] = abs(initialX - j) + abs(initialY - i);
            distanceFromStart[i][j] = INF;
            parent[i][j] = 0;
        }
    }
    map_[initialY][initialX] = 5;
    map_[goalY][goalX] = 6;
    distanceFromStart[initialY][initialX] = 0;
}

void dijkstra_debug()
{

}

void calculateDijkstra()
{
    while(1)
    {
        int *min_node = findMin(distanceFromStart, gridY, gridX);
        int min_x = min_node[2];
        int min_y = min_node[1];
        int min_node_val = min_node[0];

        if((min_x == goalX && min_y == goalY) || (min_node_val == INF))
        {
            break;
        }

        if(min_x != initialX || min_y != initialY)
        {
            map_[min_y][min_x] = 3;
        }

        if(min_x != 1)
        {
            if(map_[min_y][min_x-1] != 2 && map_[min_y][min_x-1] != 3 && map_[min_y][min_x-1] != 5)
            {
                int t = distanceFromStart[min_y][min_x] + costMap_[min_y][min_x-1];
                if(t < distanceFromStart[min_y][min_x-1])
                {
                    distanceFromStart[min_y][min_x-1] = t;
                    parent[min_y][min_x-1] = encryptIndex(min_y, min_x);
                }
            }
        }

        if(min_y != 1)
        {
            if(map_[min_y-1][min_x] != 2 && map_[min_y-1][min_x] != 3 && map_[min_y-1][min_x] != 5)
            {
                int t = distanceFromStart[min_y][min_x] + costMap_[min_y-1][min_x];
                if(t < distanceFromStart[min_y-1][min_x])
                {
                    distanceFromStart[min_y-1][min_x] = t;
                    parent[min_y-1][min_x] = encryptIndex(min_y, min_x);
                }
            }
        }

        if(min_x != gridX-2)
        {
            if(map_[min_y][min_x+1] != 2 && map_[min_y][min_x+1] != 3 && map_[min_y][min_x+1] != 5)
            {
                int t = distanceFromStart[min_y][min_x] + costMap_[min_y][min_x+1];
                if(t < distanceFromStart[min_y][min_x+1])
                {
                    distanceFromStart[min_y][min_x+1] = t;
                    parent[min_y][min_x+1] = encryptIndex(min_y, min_x);
                }
            }
        }

        if(min_y != gridY-2)
        {
            if(map_[min_y+1][min_x] != 2 && map_[min_y+1][min_x] != 3 && map_[min_y+1][min_x] != 5)
            {
                int t = distanceFromStart[min_y][min_x] + costMap_[min_y+1][min_x];
                if(t < distanceFromStart[min_y+1][min_x])
                {
                    distanceFromStart[min_y+1][min_x] = t;
                    parent[min_y+1][min_x] = encryptIndex(min_y, min_x);
                }
            }
        }
        distanceFromStart[min_y][min_x] = INF;
    }
}

void dijkstraFreeParameters()
{
    delete[] map_;
    delete[] costMap_;
    delete[] distanceFromStart;
    delete[] parent;
}
