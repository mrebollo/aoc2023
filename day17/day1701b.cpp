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
//#define TEST 1
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
// [0] -> right, [1] -> down, [2] -> left, [3] -> up
int dx[] = {0, 1, 0, -1}; 
int dy[] = {1, 0, -1, 0};
char simb[] = {'>', 'v', '<','^' };

// short by heat - dir- steps - i - j
bool operator<(const cell& a, const cell& b)
{
    if (a.heat == b.heat)
        if (a.dir == b.dir)
            if (a.steps == b.steps)
                if (a.i != b.i)
                    return (a.i < b.i);
                else
                    return (a.j < b.j);
            else
                return (a.steps < b.steps);
        else
            return (a.dir < b.dir);
    return (a.heat < b.heat);
}

inline bool isinside(int i, int j){
    return (i >= 0 && i < N && j >= 0 && j < N);
}


void load_from_file(array<array<int ,N>, N > &grid, string filename) {
    fstream inputf(filename);
    string line;
    int i = 0;
    while(getline(inputf, line) && i < N){
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

void print(int dist[][N][4][3]) {
    for(int s = 0; s < 3; s++, cout << endl << "---" << endl)
        for(int i = 0; i < N; i++, cout << endl)
            for(int j = 0; j < N; j++, cout << " ")
                for(int d = 0; d < 4; d++)
                    cout << setw(2) << (dist[i][j][d][s] == INT_MAX ? -1 : dist[i][j][d][s]) << "|";
}

void printmin(int dist[][N][4][3], array<array<int ,N>, N > &grid ) {
    for(int i = 0; i < N; i++, cout << endl)
        for(int j = 0; j < N; j++){
            int min = dist[i][j][0][0];
            for(int d = 0; d < 4; d++)
                for(int s = 0; s < 3; s++)
                    if (dist[i][j][d][s] < min)
                        min = dist[i][j][d][s];
            cout << setw(3) << min << " ";
        }
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

//samplepath: calcula una longitud de referencia sumando 1 aternativamente
// a la coordenada i o j (baja en escalera a [N,N])
int samplepath(array<array<int, N> , N> &grid){
    int len = 0, horiz = 1;
    int i = 0, j = 0;
    while(i != N-1 || j != N-1){
        len += grid[i][j];
        i += horiz;
        horiz = !horiz;
        j += horiz;
    }   
    return len + grid[N-1][N-1];
}


// restricción adicional: no se pueden dar más de tres pasos seguidos en la misma dirección
int shortestpath(array<array<int ,N>, N> &grid, int xini, int yini){    
    int dist[N][N][4][3];
    // initializing distance array by INT_MAX
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int d = 0; d < 4; d++)
                for (int s = 0; s < 3; s++)
                    dist[i][j][d][s] = INT_MAX;
    int ref = samplepath(grid);
    // start at (0,0) with 0 initial distance
    set<cell> st;
    st.insert(cell(xini, yini, grid[xini][yini], -1, 0));
    for (int d = 0; d < 4; d++)
        for(int s = 0; s < 3; s++)
            dist[0][0][d][s] = grid[0][0];

    while(!st.empty()){
        // get the cell with minimum distance
        cell k = *st.begin();
        //cout << "<<<"; print(k);
        st.erase(st.begin());
        if(dist[k.i][k.j][k.dir][k.steps] > ref) continue;
        // go to all the four adjacent cells
        for (int d = 0; d < 4; d++) {
            int x = k.i + dx[d];
            int y = k.j + dy[d];
            // if not inside boundary, ignore them. 
            // Avoid return back
            if (!isinside(x, y) || k.dir == (d + 2) % 4 || (k.dir == d && k.steps >= 3))
                continue;
            // if distance from current cell is smaller, then update distance of neighbour cell
            int steps = k.dir == d ? k.steps + 1 : 1;
            if (dist[x][y][d][steps] > dist[k.i][k.j][k.dir][k.steps] + grid[x][y]) {
                dist[x][y][d][steps] = dist[k.i][k.j][k.dir][k.steps] + grid[x][y];
                if (dist[x][y][d][steps] != INT_MAX){
                    auto todelete = st.find(cell(x, y, dist[x][y][d][steps], d, steps));   
                    if(todelete != st.end())
                        st.erase(todelete);
                } 
                cell child(x, y, dist[x][y][d][steps] , d, steps);
                st.insert(child);
                //cout << "  >>>"; print(child);
            }  
        }
    }
    // uncomment below code to print distance
    // of each cell from (0, 0)
#ifdef TEST
    print(grid);
    cout << "---" << endl;
    print(dist);
    printmin(dist, grid);
#endif
    // dis[row - 1][col - 1] will represent final
    // distance of bottom right cell from top left cell
    int min = dist[N - 1][N - 1][0][0];
    for (int d = 0; d < 4; d++)
        for(int s = 0; s < 3; s++)
        if (dist[N - 1][N - 1][d][s] < min)
            min = dist[N - 1][N - 1][d][s];
    return min;
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