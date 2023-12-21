/*
Advent of code 2023
Day 21 part 1
find positions after n steps away from start position
strategy: A^n gives positions after n steps, A = adjacency matrix
problem: A is too large to store in memory (size^4)
alternative: calculate positions by iterations
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>


using namespace std;
struct coord { int i, j; };

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
                return {i, j};
            }
    //just in case
    return {-1, -1};
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
    queue<coord> positions, nextit;
    positions.push(start);
    vector<string> aux;
    while(steps--) {
        cout << "Step: " << steps << " - " <<  positions.size() << endl;
        //aux = grid;
        while(positions.size() > 0) {
            // get next position (BFS)
            coord cur = positions.front();
            positions.pop();
            // check u, d, l, r positions
            if(cur.i > 0 && grid[cur.i-1][cur.j] == '.'){
                coord next = {cur.i-1, cur.j};
                nextit.push(next);
                //aux[cur.i-1][cur.j] = 'O';
            }
            if(cur.i < size-1 && grid[cur.i+1][cur.j] == '.') {
                coord next = {cur.i+1, cur.j};
                nextit.push(next);
                //aux[cur.i+1][cur.j] = 'O';
            }
            if(cur.j > 0 && grid[cur.i][cur.j-1] == '.') {
                coord next = {cur.i, cur.j-1};
                nextit.push(next);
                //aux[cur.i][cur.j-1] = 'O';
            }
            if(cur.j < size-1 && grid[cur.i][cur.j+1] == '.') {
                coord next = {cur.i, cur.j+1};
                nextit.push(next);
                //aux[cur.i][cur.j+1] = 'O';
            }
        }
        //print_grid(aux);
        //cout << "---" << endl;
        positions = nextit;
        nextit = queue<coord>();
    }
    return count_positions(aux);
}

// main
int main() {
    // load input
    //vector<string> grid = load_grid("input.txt");
    vector<string> grid = load_grid("adventofcode.com_2023_day_21_input.txt");
    int size = grid.size();
    int steps = size < 20 ? 6 : 64;
    coord start = find_start(grid);
    int pos = walk(grid, start, steps);
    cout << "Positions: " << pos << endl;
    return 0;
}