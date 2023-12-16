/*
advent of code day 16 part 1
obtain cell energy with ray tracing
*/

#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;
//#define TEST 1
#ifdef TEST
#define N 10
#else
#define N 110
#endif

enum direction {up, down, lef, rig};


void load_from_file(array<string, N> &grid, string filename) {
    fstream inputf(filename);
    int i = 0;
    while(getline(inputf, grid[i++]))
        ;
    inputf.close();
}

void print(array<string, N> &grid) {
    for(int i = 0; i < N; i++) 
        cout << grid[i] << endl;
}

void print(int E[][N][4]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++){
            int energy = 0;
            for(int k = 0; k < 4; k++)
                energy += E[i][j][k];
            cout << (energy > 0 ? '#' : '.');
        }
        cout << endl;
    }
}

//TODO si tengo tiempo, automatizar los casos para no hacerlos explícitos
void trace(array<string, N> &grid, int i, int j, direction dir, int *steps, int E[][N][4]){
    if(i < 0 || i >= N || j < 0 || j >= N)
        return;
    // ha entrado en un bucle: cortar el camino
    if(E[i][j][dir] > 0)
        return;
    E[i][j][dir]++;
    if(grid[i][j] == '/' && dir == rig)
        trace(grid, i-1, j, up, steps, E);
    else if(grid[i][j] == '/' && dir == lef)
        trace(grid, i+1, j, down, steps, E);
    else if(grid[i][j] == '/' && dir == up)
        trace(grid, i, j+1, rig, steps, E);
    else if(grid[i][j] == '/' && dir == down)
        trace(grid, i, j-1, lef, steps, E);
    // ojo: hay que poner '\\' porque '\' es un caracter escapado
    else if(grid[i][j] == '\\' && dir == rig)
        trace(grid, i+1, j, down, steps, E);
    else if(grid[i][j] == '\\' && dir == lef)
        trace(grid, i-1, j, up, steps, E);
    else if(grid[i][j] == '\\' && dir == up)
        trace(grid, i, j-1, lef, steps, E);
    else if(grid[i][j] == '\\' && dir == down)
        trace(grid, i, j+1, rig, steps, E);
    else if(grid[i][j] == '-' && (dir == up || dir == down)){
        trace(grid, i, j+1, rig, steps, E);
        trace(grid, i, j-1, lef, steps, E);
    }
    else if(grid[i][j] == '|' && (dir == lef || dir == rig)){
        trace(grid, i+1, j, down, steps, E);
        trace(grid, i-1, j, up, steps, E);
    }
    // en cualqueir otro caso, continua en la misma direccion
    else
        switch(dir){
            case up: trace(grid, i-1, j, dir, steps, E); break;
            case down: trace(grid, i+1, j, dir, steps, E); break;
            case lef: trace(grid, i, j-1, dir, steps, E); break;
            case rig: trace(grid, i, j+1, dir, steps, E); break;
        }
}

int count_energized(int E[][N][4]){
    int energy = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
            int cell_energy = 0;
            for(int k = 0; k < 4; k++)
                cell_energy += E[i][j][k];
            energy += cell_energy > 0 ? 1 : 0;
        }
    return energy;
}


int main(){
    array<string, N> grid;
    // uso similar a la función de memoria de PD
    int E[N][N][4] = {0};
#ifdef TEST
    load_from_file(grid, "input.txt");
    print(grid);
#else
    load_from_file(grid, "adventofcode.com_2023_day_16_input.txt");
#endif
    int steps = 0;
    trace(grid, 0, 0, rig, &steps, E);
#ifdef TEST
    print(E);
#endif
    int energy = count_energized(E);
    cout << "energy: " << energy << endl;
    return 0;
}