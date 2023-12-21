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

// read input file
vector<string> load_grid(string filename) {
    vector<string> grid;
    ifstream inputf(filename);
    string line;
    while (getline(inputf, line)) {
        grid.push_back(line);
    }
    return grid;
}

// locate start position
coord find_start(vector<string> &grid) {
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


void print_grid(vector<string> grid) {
    for (auto row : grid) {
            cout << row;
        cout << endl;
    }
}

// count positions with 'O'
int count_positions(vector<string> grid) {
    int size = grid.size();
    int count = 0;
    for (int i=0; i<size; i++) 
        for (int j=0; j<size; j++) 
            if (grid[i][j] == 'O')
                count++;
    return count;
}


// walk through grid
int walk(vector<string> grid, coord start, int steps) {
    int size = grid.size();
    // etapa en la que se ha visitado el nodo
    // evita repeticiones
    // recuperar pares/impares para posicion final
    vector<vector<int> > visited = vector<vector<int> >(size, vector<int>(size, 0));
    queue<coord> positions;
    positions.push(start);
    vector<string> aux;
    coord cur;
    do{
            //cout << "Iteration: " << cur.it << " - " << positions.size() << endl;
            // get next position (BFS)
            cur = positions.front();
            positions.pop();
            visited[cur.i][cur.j] = cur.it;
            // check u, d, l, r positions
            if(cur.i > 0 && grid[cur.i-1][cur.j] == '.' && visited[cur.i-1][cur.j] == 0){
                coord next = {cur.i-1, cur.j, cur.it+1};
                positions.push(next);
                //aux[cur.i-1][cur.j] = 'O';
            }
            if(cur.i < size-1 && grid[cur.i+1][cur.j] == '.' && visited[cur.i+1][cur.j] == 0) {
                coord next = {cur.i+1, cur.j, cur.it+1};
                positions.push(next);
                //aux[cur.i+1][cur.j] = 'O';
            }
            if(cur.j > 0 && grid[cur.i][cur.j-1] == '.' && visited[cur.i][cur.j-1] == 0) {
                coord next = {cur.i, cur.j-1, cur.it+1};
                positions.push(next);
                //aux[cur.i][cur.j-1] = 'O';
            }
            if(cur.j < size-1 && grid[cur.i][cur.j+1] == '.' && visited[cur.i][cur.j+1] == 0) {
                coord next = {cur.i, cur.j+1, cur.it+1};
                positions.push(next);
                //aux[cur.i][cur.j+1] = 'O';
            }
        
    }while(cur.it <= steps+1);
    int walkedaway = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++){
            //printf("%2d ", visited[i][j]);
            if(visited[i][j] % 2 == 1 && visited[i][j] > 0)
                walkedaway++;
        }
        //printf("\n");
    }
    return walkedaway;
}

// main
int main() {
    // load input
    //vector<string> grid = load_grid("input.txt");
    vector<string> grid = load_grid("adventofcode.com_2023_day_21_input.txt");
    int size = grid.size();
    cout << "Size: " << size << endl;
    int steps = size < 20 ? 6 : 64;
    coord start = find_start(grid);
    int pos = walk(grid, start, steps);
    cout << "Positions: " << pos << endl;
    return 0;
}