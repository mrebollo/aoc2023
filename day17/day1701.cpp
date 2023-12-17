/*
advent of code day 17 part 1
path with minimum heat loss
move at most three blocks away
turn 90 deg left or right 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;
//#define TEST 1
#ifdef TEST
#define N 13
#else
#define N 141
#endif

enum direction {up, down, lef, rig};

inline int loss_at(int i, int j, int E[][N][4]) {
    int energy = 0;
    for(int k = 0; k < 4; k++)
        energy += E[i][j][k];
    return energy;
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
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            cout << grid[i][j];
        cout << endl;
    }
}

void print(int E[][N][4]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            cout << loss_at(i, j, E) << " ";
        cout << endl;
    }
}

//TODO si tengo tiempo, automatizar los casos para no hacerlos explícitos
void loss(array<array<int ,N>, N > &grid, int i, int j, direction dir, int E[][N][4]){
 /*
    if(i < 0 || i >= N || j < 0 || j >= N)
        return;
    // ha entrado en un bucle: cortar el camino
    if(E[i][j][dir] > 0)
        return;
    E[i][j][dir]++;
    if(grid[i][j] == '/' && dir == rig)
        loss(grid, i-1, j, up, E);
    else if(grid[i][j] == '/' && dir == lef)
        loss(grid, i+1, j, down, E);
    else if(grid[i][j] == '/' && dir == up)
        loss(grid, i, j+1, rig, E);
    else if(grid[i][j] == '/' && dir == down)
        loss(grid, i, j-1, lef, E);
    // ojo: hay que poner '\\' porque '\' es un caracter escapado
    else if(grid[i][j] == '\\' && dir == rig)
        loss(grid, i+1, j, down, E);
    else if(grid[i][j] == '\\' && dir == lef)
        loss(grid, i-1, j, up, E);
    else if(grid[i][j] == '\\' && dir == up)
        loss(grid, i, j-1, lef, E);
    else if(grid[i][j] == '\\' && dir == down)
        loss(grid, i, j+1, rig, E);
    else if(grid[i][j] == '-' && (dir == up || dir == down)){
        loss(grid, i, j+1, rig, E);
        loss(grid, i, j-1, lef, E);
    }
    else if(grid[i][j] == '|' && (dir == lef || dir == rig)){
        loss(grid, i+1, j, down, E);
        loss(grid, i-1, j, up, E);
    }
    // en cualqueir otro caso, continua en la misma direccion
    else
        switch(dir){
            case up: loss(grid, i-1, j, dir, E); break;
            case down: loss(grid, i+1, j, dir, E); break;
            case lef: loss(grid, i, j-1, dir, E); break;
            case rig: loss(grid, i, j+1, dir, E); break;
        }
    */

}


int main(){
    array<array<int, N> , N> grid;
    // uso similar a la función de memoria de PD
    int E[N][N][4] = {0};
#ifdef TEST
    load_from_file(grid, "input.txt");
    print(grid);
#else
    load_from_file(grid, "adventofcode.com_2023_day_17_input.txt");
#endif
    //loss(grid, 0, 0, rig, E);
#ifdef TEST
    //print(E);
#endif
    int heatloss = loss_at(N-1, N-1, E);
    cout << "loss: " << heatloss << endl;
    return 0;
}