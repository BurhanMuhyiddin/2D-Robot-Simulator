#include "astar.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "dijekstra.h"

extern int initialX, initialY, goalX, goalY, gridX, gridY;
extern int INF;
extern int** map_;
extern int** costMap_;
extern int** parent;
int** h;
int** f;
int** g;

void astarInit()
{
    map_ = new int*[gridY];
    costMap_ = new int*[gridY];
    parent = new int*[gridY];
    h = new int*[gridY];
    f = new int*[gridY];
    g = new int*[gridY];

    for(int i = 0; i < gridX; i++)
    {
        map_[i] = new int[gridX];
        costMap_[i] = new int[gridX];
        parent[i] = new int[gridX];
        h[i] = new int[gridX];
        f[i] = new int[gridX];
        g[i] = new int[gridX];
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
            parent[i][j] = 0;
            h[i][j] = astarCalculateDistance(j,i);
            f[i][j] = INF;
            g[i][j] = INF;
        }
    }
    map_[initialY][initialX] = 5;
    map_[goalY][goalX] = 6;
    g[initialY][initialX] = 0;
    f[initialY][initialX] = h[initialY][initialX];
}

void astarDebug()
{

}

void astarCalculate()
{
    while(1)
    {
        int *min_node = findMin(f, gridY, gridX);
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
                int t = g[min_y][min_x] + abs(costMap_[min_y][min_x] - costMap_[min_y][min_x-1]);
                if(t < g[min_y][min_x-1])
                {
                    g[min_y][min_x-1] = t;
                    f[min_y][min_x-1] = g[min_y][min_x-1] + h[min_y][min_x-1];
                    parent[min_y][min_x-1] = encryptIndex(min_y, min_x);
                }
            }
        }

        if(min_y != 1)
        {
            if(map_[min_y-1][min_x] != 2 && map_[min_y-1][min_x] != 3 && map_[min_y-1][min_x] != 5)
            {
                int t = g[min_y][min_x] + abs(costMap_[min_y][min_x] - costMap_[min_y-1][min_x]);
                if(t < g[min_y-1][min_x])
                {
                    g[min_y-1][min_x] = t;
                    f[min_y-1][min_x] = g[min_y-1][min_x] + h[min_y-1][min_x];
                    parent[min_y-1][min_x] = encryptIndex(min_y, min_x);
                }
            }
        }

        if(min_x != gridX-2)
        {
            if(map_[min_y][min_x+1] != 2 && map_[min_y][min_x+1] != 3 && map_[min_y][min_x+1] != 5)
            {
                int t = g[min_y][min_x] + abs(costMap_[min_y][min_x] - costMap_[min_y][min_x+1]);
                if(t < g[min_y][min_x+1])
                {
                    g[min_y][min_x+1] = t;
                    f[min_y][min_x+1] = g[min_y][min_x+1] + h[min_y][min_x+1];
                    parent[min_y][min_x+1] = encryptIndex(min_y, min_x);
                }
            }
        }

        if(min_y != gridY-2)
        {
            if(map_[min_y+1][min_x] != 2 && map_[min_y+1][min_x] != 3 && map_[min_y+1][min_x] != 5)
            {
                int t = g[min_y][min_x] + abs(costMap_[min_y][min_x] - costMap_[min_y+1][min_x]);
                if(t < g[min_y+1][min_x])
                {
                    g[min_y+1][min_x] = t;
                    f[min_y+1][min_x] = g[min_y+1][min_x] + h[min_y+1][min_x];
                    parent[min_y+1][min_x] = encryptIndex(min_y, min_x);
                }
            }
        }
        f[min_y][min_x] = INF;
    }
}

int astarCalculateDistance(int x, int y)
{
    return abs(x - goalX) + abs(y - goalY);
}

void astarFreeParameters()
{
    delete[] map_;
    delete[] costMap_;
    delete[] parent;
    delete[] h;
    delete[] g;
    delete[] f;
}

