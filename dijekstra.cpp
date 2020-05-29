#include "dijekstra.h"
#include <iostream>
#include <vector>

using namespace std;

// !!!Warning: change robotX and robotY to startX and startY, because as robot moves the coordinates will change

int INF = 999999;

extern int robotX, robotY, goalX, goalY, gridX, gridY;;
extern int** map_;
extern int** costMap_;
extern int** distanceFromStart;
extern int** parent;

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

        if(min_x != robotX || min_y != robotY)
        {
            map_[min_y][min_x] = 3;
        }

        if(min_x != 2)
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

        if(min_y != 2)
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

int* findMin(int** arr, int row, int col)
{
    int temp_min = INF;
    int min_x, min_y;
    static int res[3] = {0, 0, 0}; //val, y, x

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            int temp = arr[i][j];
            if(temp < temp_min)
            {
                temp_min = temp;
                min_y = i;
                min_x = j;
            }
        }
    }
    res[0] = temp_min;
    res[1] = min_y;
    res[2] = min_x;

    return res;
}

int encryptIndex(int row, int col)
{
    return row*1 + col*gridX;
}
