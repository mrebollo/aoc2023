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
    int dx[] = { -1, 0, 1, 0 }; 
    int dy[] = { 0, 1, 0, -1 };
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


// restricción adicional: no se pueden dar más de tres pasos seguidos en la misma dirección
int shortestpath(array<array<int ,N>, N> &grid, int xini, int yini){
    array<array<int, N>, N> dist;
    // initializing distance array by INT_MAX
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dist[i][j] = INT_MAX;

    // start at (0,0) with 0 initial distance
    set<cell> st;
    st.insert(cell(xini, yini, grid[xini][yini], -1, 0));
    dist[0][0]= grid[0][0];

    while(!st.empty()){
        // get the cell with minimum distance
        cell k = *st.begin();
        cout << "<<<"; print(k);
        st.erase(st.begin());
        // go to all the four adjacent cells
        for (int d = 0; d < 4; d++) {
            int x = k.i + dx[d];
            int y = k.j + dy[d];
            // if not inside boundary, ignore them. 
            // Avoid return back and more than 3 steps in the same direction
            if (!isinside(x, y) || k.dir == (d + 2) % 4 || k.steps == 3)
                continue;
            // if distance from current cell is smaller, then update distance of neighbour cell
            if (dist[x][y] > dist[k.i][k.j] + grid[x][y]) {
                int steps = k.dir == d ? k.steps + 1 : 1;
                // update the distance and insert new updated cell in set
                if (dist[x][y] != INT_MAX)
                    st.erase(st.find(cell(x, y, dist[x][y], d, steps)));
                dist[x][y] = dist[k.i][k.j]  + grid[x][y];
                cell child(x, y, dist[x][y] , d, steps);
                st.insert(child);
                cout << "  >>>"; print(child);
            }  
        }
    }
    // uncomment below code to print distance
    // of each cell from (0, 0)
#ifdef TEST
    print(grid);
    print(dist);
    printMovement(dist);
#endif
    // dis[row - 1][col - 1] will represent final
    // distance of bottom right cell from top left cell
    return dist[N - 1][N - 1];
}



int main(){
    array<array<int, N> , N> grid;
#ifdef TEST
    load_from_file(grid, "input.txt");
#else
    load_from_file(grid, "adventofcode.com_2023_day_17_input.txt");
#endif
    int d = shortestpath(grid, 0, 0);
    cout << "shortest path: " << d << endl;
    return 0;
}