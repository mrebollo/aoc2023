/*
advent of code day 16 part 2
obtain cell energy with ray tracing
start at any cell on edges
get the maximum energy configuration
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
struct config{
    int i;
    int j;
    direction dir;
    int energy;
};


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
void trace(array<string, N> &grid, int i, int j, direction dir, int E[][N][4]){
    if(i < 0 || i >= N || j < 0 || j >= N)
        return;
    // ha entrado en un bucle: cortar el camino
    if(E[i][j][dir] > 0)
        return;
    E[i][j][dir]++;
    if(grid[i][j] == '/' && dir == rig)
        trace(grid, i-1, j, up, E);
    else if(grid[i][j] == '/' && dir == lef)
        trace(grid, i+1, j, down, E);
    else if(grid[i][j] == '/' && dir == up)
        trace(grid, i, j+1, rig, E);
    else if(grid[i][j] == '/' && dir == down)
        trace(grid, i, j-1, lef, E);
    // ojo: hay que poner '\\' porque '\' es un caracter escapado
    else if(grid[i][j] == '\\' && dir == rig)
        trace(grid, i+1, j, down, E);
    else if(grid[i][j] == '\\' && dir == lef)
        trace(grid, i-1, j, up, E);
    else if(grid[i][j] == '\\' && dir == up)
        trace(grid, i, j-1, lef, E);
    else if(grid[i][j] == '\\' && dir == down)
        trace(grid, i, j+1, rig, E);
    else if(grid[i][j] == '-' && (dir == up || dir == down)){
        trace(grid, i, j+1, rig, E);
        trace(grid, i, j-1, lef, E);
    }
    else if(grid[i][j] == '|' && (dir == lef || dir == rig)){
        trace(grid, i+1, j, down, E);
        trace(grid, i-1, j, up, E);
    }
    // en cualqueir otro caso, continua en la misma direccion
    else
        switch(dir){
            case up: trace(grid, i-1, j, dir, E); break;
            case down: trace(grid, i+1, j, dir, E); break;
            case lef: trace(grid, i, j-1, dir, E); break;
            case rig: trace(grid, i, j+1, dir, E); break;
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

config best_config(array<string, N> &grid){
    config best;
    best.energy = 0;
    for(int i = 0; i < N; i++){
        int E[N][N][4] = {0};
        trace(grid, i, 0, rig, E);
        int energy = count_energized(E);
        if(energy > best.energy){
            best.energy = energy;
            best.i = i;
            best.j = 0;
            best.dir = rig;
        }
    }
    for(int i = 0; i < N; i++){
        int E[N][N][4] = {0};
        trace(grid, i, N-1, lef, E);
        int energy = count_energized(E);
        if(energy > best.energy){
            best.energy = energy;
            best.i = i;
            best.j = 0;
            best.dir = lef;
        }
    }
    for(int j = 0; j < N; j++){
        int E[N][N][4] = {0};
        trace(grid, 0, j, down, E);
        int energy = count_energized(E);
        if(energy > best.energy){
            best.energy = energy;
            best.i = 0;
            best.j = j;
            best.dir = down;
        }
    }
    for(int j = 0; j < N; j++){
        int E[N][N][4] = {0};
        trace(grid, N-1, j, up, E);
        int energy = count_energized(E);
        if(energy > best.energy){
            best.energy = energy;
            best.i = 0;
            best.j = j;
            best.dir = up;
        }
    }
    return best;
}

int main(){
    array<string, N> grid;
#ifdef TEST
    load_from_file(grid, "input.txt");
    print(grid);
#else
    load_from_file(grid, "adventofcode.com_2023_day_16_input.txt");
#endif
    config conf = best_config(grid);
#ifdef TEST
    int E[N][N][4] = {0};
    trace(grid, conf.i, conf.j, conf.dir, E);
    int energy = count_energized(E);
    print(E);
#endif
    cout << "energy: " << conf.energy << endl;
    return 0;
}