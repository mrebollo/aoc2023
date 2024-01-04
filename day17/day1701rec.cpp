/*
advent of code day 17 part 1
path with minimum heat loss
move at most three blocks away
turn 90 deg left or right 
variation of dijiskstra algorithm
version completa, incluye los tres pasos rectos seguidos
*/

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <set>
#include <array>

using namespace std;
#define TEST 1
#ifdef TEST
#define N 13
#else
#define N 141
#endif
struct cell{
    int i, j;
    int heat;
    int dir;
    int steps;
    cell(int i, int j, int heat, int dir, int steps): 
        i(i), j(j), heat(heat), dir(dir), steps(steps) {}
};
    // direction arrays for simplification of getting neighbour
    // [0] left, [1] down, [2] right, [3] up
    int dr[] = { -1, 0, 1, 0 }; 
    int dc[] = { 0, 1, 0, -1 };
    char simb[] = {'^','>', 'v', '<' };

bool operator<(const cell& a, const cell& b)
{
    if (a.heat == b.heat)
            if (a.i != b.i)
                return (a.i < b.i);
            else
                return (a.j < b.j);
    return (a.heat < b.heat);
}

inline bool isinside(int i, int j){
    return (i >= 0 && i < N && j >= 0 && j < N);
}


void load_from_file(array<array<int ,N>, N > &grid, string filename) {
    fstream inputf(filename);
    string line;
    int i = 0;
    while(getline(inputf, line)){
        for(int j = 0; j < N; j++)
            grid[i][j] = line[j] - '0';
        i++;
    }
    inputf.close();
}

void print(array<array<int ,N>, N > &grid) {
    for(int i = 0; i < N; i++, cout << endl)
        for(int j = 0; j < N; j++)
            cout << setw(3) << (grid[i][j] == INT_MAX ? -1 : grid[i][j]) << " ";
}


void print(cell k) {
#ifdef TEST
    cout << "(" << k.i << ", " << k.j << ") " << k.heat << " " << simb[k.dir] << " " << k.steps << endl;
#endif
}

void printMovement(array<array<int, N>, N> &dist) {
    array<array<char ,N>, N > moves;
    //init
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            moves[i][j] = '.';
    // from (N,N), go min (up, left)
    int row = N - 1, col = N - 1;
    while(row > 0 && col > 0){
        moves[row][col] = '*';
        if(dist[row - 1][col] < dist[row][col - 1])
            row--;
        else 
            col--;
    }
    moves[0][0] = '*';
    if(moves[0][1] > moves[1][0])
        moves[0][1] = '*';
    else
        moves[1][0] = '*';  
    // print
    for (int i = 0; i < N; i++, cout << endl)
        for (int j = 0; j < N; j++)
            cout << setw(3) << moves[i][j] << " ";
}


int shortestpath(array<array<int ,N>, N> &grid, int row, int col, int dir, int steps) {
    if (row == N - 1 && col == N - 1) {
        return grid[row][col];
    }
    // mark cell as visited and save original value
    int savedvalue = grid[row][col];
    grid[row][col] = 0;
    vector<int> dist;
    for(int i = 0; i < 4; i++){
        int r = row + dr[i];
        int c = col + dc[i];
        //only valid neighbors (reduce calls)
        if (isinside(r,c) && dir != (i + 2) % 4 && grid[r][c] > 0)
            if (dir != i)
                dist.push_back(grid[r][c] + shortestpath(grid, r, c, i, 1));
            else if(steps < 3)
                dist.push_back(grid[r][c] + shortestpath(grid, r, c, i, steps+1));
    }
    //restore cell
    grid[row][col] = savedvalue;
    if(dist.empty())
        return 999;
    int min = dist.front();
    for(int i = 1; i < dist.size(); i++)
        if(dist[i] < min)
            min = dist[i];
    return min;
}


int main(){
    array<array<int, N> , N> grid;
#ifdef TEST
    load_from_file(grid, "input.txt");
#else
    load_from_file(grid, "adventofcode.com_2023_day_17_input.txt");
#endif
    int d = shortestpath(grid, 0, 0, -1, 0);
    cout << "shortest path: " << d << endl;
    return 0;
}