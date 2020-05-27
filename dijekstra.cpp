#include "dijekstra.h"
#include <iostream>
#include <vector>

using namespace std;

// !!!Warning: change robotX and robotY to startX and startY, because as robot moves the coordinates will change

extern int robotX, robotY, goalX, goalY, gridX, gridY;;
extern int** map_;
extern int** costMap_;
extern int** distanceFromStart;
extern int* parentX;
extern int* parentY;
extern vector< vector <int> > optimalPath;

void dijkstra_debug()
{
    /*for(int i = 0; i < gridY; i++)
    {
        for(int j = 0; j < gridX; j++)
        {
            cout << distanceFromStart[i][j] << " ";
        }
        cout << endl;
    }*/
}

void calculateDijkstra()
{
    while(1)
    {
        int *min_node = findMin(distanceFromStart, gridY, gridX);
        int min_x = min_node[2];
        int min_y = min_node[1];
        int min_node_val = min_node[0];

        //cout << min_x << "  " << min_y << endl;

        if((min_x == goalX && min_y == goalY) || min_node_val == INF)
        {
            break;
        }

        if(min_x != robotX && min_y != robotY)
        {
            map_[min_y][min_x] = 3;
        }

        if(min_x != 2)
        {
            if(map_[min_y][min_x-1] != 2 && map_[min_y][min_x-1] != 3 && map_[min_y][min_x-1] != 5)
            {
                int t = (distanceFromStart[min_y][min_x] + costMap_[min_y][min_x-1]);
                if(t < distanceFromStart[min_y][min_x-1])
                {
                    distanceFromStart[min_y][min_x-1] = t;
                    // parent[gridY][gridX-1] = gridY, gridX;
                    //parentX[min_x-1] = min_x;
                    //parentY[min_y] = min_y;
                    vector<int> tmp;
                    tmp.push_back(min_x);
                    tmp.push_back(min_y);
                    optimalPath.push_back(tmp);
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
                    // parent[gridY-1][gridX] = gridY, gridX;
                    //parentX[min_x] = min_x;
                    //parentY[min_y-1] = min_y;
                    vector<int> tmp;
                    tmp.push_back(min_x);
                    tmp.push_back(min_y);
                    optimalPath.push_back(tmp);
                }
            }
        }

        if(min_x != gridX-1)
        {
            if(map_[min_y][min_x+1] != 2 && map_[min_y][min_x+1] != 3 && map_[min_y][min_x+1] != 5)
            {
                int t = distanceFromStart[min_y][min_x] + costMap_[min_y][min_x+1];
                if(t < distanceFromStart[min_y][min_x+1])
                {
                    distanceFromStart[min_y][min_x+1] = t;
                    // parent[gridY][gridX+1] = gridY, gridX;
                    //parentX[min_x+1] = min_x;
                    //parentY[min_y] = min_y;
                    vector<int> tmp;
                    tmp.push_back(min_x);
                    tmp.push_back(min_y);
                    optimalPath.push_back(tmp);
                }
            }
        }

        if(min_y != gridY-1)
        {
            if(map_[min_y+1][min_x] != 2 && map_[min_y+1][min_x] != 3 && map_[min_y+1][min_x] != 5)
            {
                int t = distanceFromStart[min_y][min_x] + costMap_[min_y+1][min_x];
                if(t < distanceFromStart[min_y+1][min_x])
                {
                    distanceFromStart[min_y+1][min_x] = t;
                    // parent[gridY+1][gridX] = gridY, gridX;
                    //parentX[min_x] = min_x;
                    //parentY[min_y+1] = min_y;
                    vector<int> tmp;
                    tmp.push_back(min_x);
                    tmp.push_back(min_y);
                    optimalPath.push_back(tmp);
                }
            }
        }
        distanceFromStart[min_y][min_x] = INF;
    }
}

int* findMin(int** arr, int row, int col)
{
    int temp_min = 999;
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
    //cout << temp_min << "   " << min_y << "    " << min_x << endl;
    res[0] = temp_min;
    res[1] = min_y;
    res[2] = min_x;

    return res;
}
