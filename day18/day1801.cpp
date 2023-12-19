/*
Advent  of code 2023
Day 18, part 1
Dig following the path and remove interior points
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

using namespace std;

inline void next(int &i, int &j, char dir) {
    switch (dir) {
        case 'U': i--; break;
        case 'L': j--; break;
        case 'D': i++; break;
        case 'R': j++; break;
    }
}

// relleno recursivo de una figura a partir de un punto interior
void floodfill(int **grid, int N, int i, int j) {
    if (i < 0 || i >= N || j < 0 || j >= N) return;
    if (grid[i][j] == 1) return;
    grid[i][j] = 1;
    floodfill(grid, N, i-1, j);
    floodfill(grid, N, i+1, j);
    floodfill(grid, N, i, j-1);
    floodfill(grid, N, i, j+1);
}

int main () {
    //ifstream inputf("input.txt");
    ifstream inputf("adventofcode.com_2023_day_18_input.txt");
    set<pair<int, int> > cubes;
    string line, color;
    char dir;
    int len, i = 0, j = 0, min = INT_MAX, max = 0;
    cubes.insert(make_pair(i, j));
    while(getline(inputf, line)) {
        istringstream iss(line);
        iss >> dir >> len >> color;
        while(len--){
            next(i, j, dir);
            cubes.insert(make_pair(i, j));
            if(i > max) max = i;
            if(j > max) max = j;
            if(i < min) min = i;
            if(j < min) min = j;
        }
    }
    inputf.close();
    int N = max - min + 1;

    int **grid;
    grid = new int*[N];
    for (int i = 0; i < N; i++) {
        grid[i] = new int[N];
    }
    fill_n(*grid, N*N, 0);
    for (auto cube : cubes){
        int i = cube.first-min;
        int j = cube.second-min;
        //cout << i << " " << j << endl;
        grid[cube.first-min][cube.second-min] = 1;
    }
    ofstream pictf("grid.pbm");
    pictf << "P1" << endl;
    pictf << N << " " << N << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N-1; j++) {
            pictf << grid[i][j] << " ";
        }
        pictf << grid[i][N-1] << endl;
    }
    pictf.close();
    // asumo que el punto central es un punto interior
    floodfill(grid, N, N/2, N/2);

    int count = 0;
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) 
            if (grid[i][j] == 1) count++;
    cout << "Number of cubes: " << count << endl;

    for (int i = 0; i < N; i++) 
        delete[] grid[i];
    delete[] grid;
    return 0;
}