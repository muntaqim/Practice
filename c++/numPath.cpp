#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <iomanip>

using namespace std;

/* This is a unnecesarily complicated solution.
 * Easier solution is to fill up all the bottom and
 * right most with 1s and then go row by row
 * to calculate left + down values
 *
 */ 

// namespace std have been included for this problem.

typedef pair<int,int> pos;

int curPaths(int **numWays, int row, int col, int rows, int cols)
{
    int sum = 0;
    if(row == rows - 1 && col == cols - 1)
        return 1;
    
    if (row != rows -1)
    {
        sum += numWays[row + 1][col];
    }
    if (col != cols -1)
    {
        sum += numWays[row][col + 1];
    }
    return sum;

}
// Add any helper functions(if needed) above.
int count_paths(int rows, int cols)
{
    int **numWays = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        numWays[i] = new int[cols];
        for (int j = 0; j < cols; j++)
                numWays[i][j] = 0;
    }
    queue<pos> p;
    p.emplace(pos(rows-1,cols-1));
    pos cur;
    while(!p.empty())
    {
        // look at next value in queue
        cur = p.front();
        if (numWays[cur.first][cur.second] == 0)
        {
            // look at neighbours
            numWays[cur.first][cur.second] = curPaths(numWays, cur.first, cur.second, rows, cols);

            //add it's children (right and up) to the array
            if (cur.first - 1 >= 0)
                p.emplace(pos(cur.first-1, cur.second));

            if (cur.second -1 >= 0)
                p.emplace(pos(cur.first,cur.second -1));
        }
        p.pop();
    }

    //print 2D array
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
            cout << setw(4) << numWays[x][y];

        cout << endl;
    }

    int returnValue = numWays[0][0];


    for (int i = 0; i < rows; i++)
        delete[] numWays[i];

    delete [] numWays;

    return returnValue;
}


int main()
{
    int numWays = count_paths(5,5);
    return 0;
}

