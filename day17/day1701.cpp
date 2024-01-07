/*
advent of code day 17 part 1
path with minimum heat loss
move at most three blocks away
turn 90 deg left or right 
variation of dijiskstra algorithm
version sin restricciones
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
#define N 9
#else
#define N 141
#endif
struct cell{
    int i, j;
    int heat;
    cell(int i, int j, int heat): i(i), j(j), heat(heat) {}
};

bool operator<(const cell& a, const cell& b)
{
    if (a.heat == b.heat) {
        if (a.i != b.i)
            return (a.i < b.i);
        else
            return (a.j < b.j);
    }
    return (a.heat < b.heat);
}

bool isinside(int i, int j)
{
    return (i >= 0 && i < N && j >= 0 && j < N);
}

inline int min(int a, int b, int c) {return min(a, min(b, c));}   

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
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            cout << setw(2) << grid[i][j];
        cout << endl;
    }
}


void print(set<pair<int, int> > visited) {
    for(auto it = visited.begin(); it != visited.end(); it++)
        cout << "(" << it->first << ", " << it->second << ") ";
    cout << endl;
}

// version normal, incluir luego los tres pasos rectos seguidos
int shortestpath(array<array<int ,N>, N> &grid, int i, int j){
    //int dist[N][N];
    array<array<int ,N>, N> dist;
    array<array<char ,N>, N> moves;
    // initializing distance array by INT_MAX
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            dist[i][j] = INT_MAX;
            moves[i][j] = ' ';
        }
    // direction arrays for simplification of getting neighbour
    // [0] left, [1] down, [2] right, [3] up
    int dx[] = { -1, 0, 1, 0 }; 
    int dy[] = { 0, 1, 0, -1 };
    char simb[] = {'<', 'v', '>', '^'};
 
    // start at (0,0) with 0 initial distance
    set<cell> st;
    st.insert(cell(0, 0, 0));
    dist[0][0] = grid[0][0];

    while(!st.empty()){
        // get the cell with minimum distance
        cell k = *st.begin();
        st.erase(st.begin());

        // go to all the four adjacent cells
        for (int i = 0; i < 4; i++) {
            int x = k.i + dx[i];
            int y = k.j + dy[i];
            // if not inside boundary, ignore them
            if (!isinside(x, y))
                continue;
            // if distance from current cell is smaller, then update distance of neighbour cell
            if (dist[x][y] > dist[k.i][k.j] + grid[x][y]) {
                // if cell is already there in set, then remove its previous entry
                if (dist[x][y] != INT_MAX){
                    st.erase(st.find(cell(x, y, dist[x][y])));
                }
                // update the distance and insert new updated cell in set
                dist[x][y] = dist[k.i][k.j] + grid[x][y];
                st.insert(cell(x, y, dist[x][y]));
            }
        }
    }
    // uncomment below code to print distance
    // of each cell from (0, 0)
#ifdef TEST
    // show the path
    int row = N - 1, col = N - 1;
    while(row != 0 || col != 0){
        int min = dist[row][col], dir;
        for(int i = 0; i < 4; i++)
            if(isinside(row + dx[i], col + dy[i]) && dist[row + dx[i]][col + dy[i]] < min){
                min = dist[row + dx[i]][col + dy[i]];
                dir = i;
            }
        row += dx[dir];
        col += dy[dir];
        moves[row][col] = '*';;
    }
    for (int i = 0; i < N; i++, cout << endl)
        for (int j = 0; j < N; j++)
            cout << moves[i][j];
    for (int i = 0; i < N; i++, cout << endl)
        for (int j = 0; j < N; j++)
            cout << dist[i][j] << " ";
#endif
    // dis[row - 1][col - 1] will represent final
    // distance of bottom right cell from top left cell
    return dist[N - 1][N - 1];
}



int main(){
    array<array<int, N> , N> grid;
#ifdef TEST
    load_from_file(grid, "input9.txt");
    print(grid);
#else
    load_from_file(grid, "adventofcode.com_2023_day_17_input.txt");
#endif
    int d = shortestpath(grid, 0, 0);
    cout << "shortest path: " << d << endl;
    return 0;
}