extern int gridX;
extern int INF;

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

int* decryptIndex(int encryptedIndex)
{
    static int index[] = {0, 0}; // row, col
    index[1] = (encryptedIndex - (encryptedIndex%gridX))/gridX;
    index[0] = encryptedIndex - index[1]*gridX;

    return index;
}

