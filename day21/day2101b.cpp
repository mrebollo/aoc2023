/*
Advent of code 2023
Day 21 part 1
find positions after n steps away from start position
strategy: A^n gives positions after n steps, A = adjacency matrix
problem: A is too large to store in memory (size^4)
alternative: calculate positions by iterations (BFS) -> do not scale
alternative2: take advantadge from simmetries:
state 1 = {S}
state 2 = neig{S}
state 3 = {S} + neig(neig{S}} = prev(s2) + next(s2)
state 4 = prev(s3) + next(s3) = neig{S} + neig{neig{neig{S}}}
state 5 = {S} (each 2) + neig(neig{S}} + neig{neig{neig{neig{S}}}}
- van alternando estados pares e impares
- los nuevos estados crecen hacia afuera
- marcar nodos visitados para evitar expandirlos
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>


using namespace std;
struct coord { int i, j, it; };
vector<vector<int> > visited;
vector<string> grid;
int nnz = 0;

// read input file
void load_grid(string filename) {
    ifstream inputf(filename);
    string line;
    while (getline(inputf, line)) 
        grid.push_back(line);
    int size = grid.size();
    visited = vector<vector<int> >(size, vector<int>(size, 0));
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++){
            visited[i][j] = grid[i][j] == '#' ? -1 : 0;
            if(grid[i][j] != '#') nnz++;
        }
    inputf.close();
    cout << "Grid loaded" << endl;
    cout << "Size: " << size << endl;
    cout << "NNZ: " << nnz << endl;
}

// locate start position
coord find_start() {
    int size = grid.size();
    for (int i=0; i<size; i++) 
        for (int j=0; j<size; j++) 
            if (grid[i][j] == 'S'){
                grid[i][j] = '.';
                return {i, j, 1};
            }
    //just in case
    return {-1, -1, 1};
}


void print_grid() {
    for (auto row : grid) {
            cout << row;
        cout << endl;
    }
}


// walk through grid
int walk(coord start, int steps) {
    int size = grid.size();
    queue<coord> positions;
    coord cur = start;
    do{
            visited[cur.i][cur.j] = cur.it;
            // check u, d, l, r positions
            if(cur.i > 0 && grid[cur.i-1][cur.j] == '.' && visited[cur.i-1][cur.j] == 0){
                visited[cur.i-1][cur.j] = cur.it+1;
                nnz--;
                coord next = {cur.i-1, cur.j, cur.it+1};
                positions.push(next);
            }
            if(cur.i < size-1 && grid[cur.i+1][cur.j] == '.' && visited[cur.i+1][cur.j] == 0) {
                visited[cur.i+1][cur.j] = cur.it+1;
                nnz--;
                coord next = {cur.i+1, cur.j, cur.it+1};
                positions.push(next);
            }
            if(cur.j > 0 && grid[cur.i][cur.j-1] == '.' && visited[cur.i][cur.j-1] == 0) {
                visited[cur.i][cur.j-1] = cur.it+1;
                nnz--;
                coord next = {cur.i, cur.j-1, cur.it+1};
                positions.push(next);
            }
            if(cur.j < size-1 && grid[cur.i][cur.j+1] == '.' && visited[cur.i][cur.j+1] == 0) {
                visited[cur.i][cur.j+1] = cur.it+1;
                nnz--;
                coord next = {cur.i, cur.j+1, cur.it+1};
                positions.push(next);
            }
           // get next position (BFS)
            if(!positions.empty()){
                cur = positions.front();
                positions.pop();
            }
    // condiciones redundantes: revisar porque si no están todas bucle infinito
    }while(cur.it <= steps && !positions.empty() && nnz > 0 );
}

int walked_away() {
    int size = grid.size();
    int walkedaway = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++){
            if(visited[i][j] % 2 == 1 && visited[i][j] > 0)
                walkedaway++;
        }
    }
    return walkedaway;
}


// main
int main() {
    // load input
    //load_grid("input.txt");
    //print_grid();
    load_grid("adventofcode.com_2023_day_21_input.txt");
    int size = grid.size();
    int steps = size < 20 ? 6 : 64;
    coord start = find_start();
    walk(start, steps);
    int pos = walked_away();
    cout << "Positions: " << pos << endl;
    return 0;
}