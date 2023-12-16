/*
    advent of code 2023
    day 14, part 2
    move rocks north, west, south, east cyclicly and calculate the load
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define TEST 1
#ifdef TEST
#define N 10
#else
#define N 100
#endif



void load_from_file(char grid[N][N], string filename) {
    string line;
    fstream inputf;

    int i = 0;
    inputf.open(filename);
    while(getline(inputf, line)) {
        for(int j = 0; j < line.size(); j++) {
            grid[i][j] = line[j];
        }
        i++;
    }
    inputf.close();
}

void print(char grid[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            cout << grid[i][j];
        cout << endl;
    }
    cout << '\7' << endl;
}


void tiltup(char grid[N][N]) {
    int moves;
    // repite hasta que no haya movimientos
    do{
        moves = 0;
        // mueve las rocas una posición hacia arriba
        for(int i = 1; i < N; i++)
            for(int j = 0; j < N; j++)
                if(grid[i][j] == 'O' && grid[i-1][j] == '.'){
                    grid[i-1][j] = grid[i][j];
                    grid[i][j] = '.';
                    moves++;
                }
    }while(moves > 0);
}

void tiltdown(char grid[N][N]) {
    int moves;
    // repite hasta que no haya movimientos
    do{
        moves = 0;
        // mueve las rocas una posición hacia arriba
        for(int i = N-2; i >= 0; i--)
            for(int j = 0; j < N; j++)
                if(grid[i][j] == 'O' && grid[i+1][j] == '.'){
                    grid[i+1][j] = grid[i][j];
                    grid[i][j] = '.';
                    moves++;
                }
    }while(moves > 0);
}

void tiltleft(char grid[N][N]) {
    int moves;
    // repite hasta que no haya movimientos
    do{
        moves = 0;
        // mueve las rocas una posición hacia arriba
        for(int i = 0; i < N; i++)
            for(int j = 1; j < N; j++)
                if(grid[i][j] == 'O' && grid[i][j-1] == '.'){
                    grid[i][j-1] = grid[i][j];
                    grid[i][j] = '.';
                    moves++;
                }
    }while(moves > 0);
}

void tiltright(char grid[N][N]) {
    int moves;
    // repite hasta que no haya movimientos
    do{
        moves = 0;
        // mueve las rocas una posición hacia arriba
        for(int i = 0; i < N; i++)
            for(int j = N-2; j >= 0; j--)
                if(grid[i][j] == 'O' && grid[i][j+1] == '.'){
                    grid[i][j+1] = grid[i][j];
                    grid[i][j] = '.';
                    moves++;
                }
    }while(moves > 0);
}



int get_load(char grid[N][N]) {
    int load = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(grid[i][j] == 'O')
                load += N - i;
    return load;
}

void duplicate(char grid[N][N], char start[N][N]) {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            start[i][j] = grid[i][j];
}

bool equal(char grid[N][N], char start[N][N]) {
    bool equal = true;
    for(int i = 0; i < N && equal; i++)
        for(int j = 0; j < N && equal; j++)
            if(grid[i][j] != start[i][j])
                equal = false;
    return equal;
}


int main() {
    fstream inputf;
    string line;
    char grid[N][N], start[N][N];

#ifdef TEST
    load_from_file(grid, "input.txt");
#else
    load_from_file(grid, "adventofcode.com_2023_day_14_input.txt");
#endif
    print(grid);
    tiltup(grid);
    tiltleft(grid);
    tiltdown(grid);
    tiltright(grid);
    duplicate(grid, start);
    for(int cycle = 1; cycle < 1000000000; cycle++) {
        if (cycle % 1000000 == 0)
            cout << "*" << flush;
        if (cycle % 10000000 == 0)
            cout << "|" << flush;
        tiltup(grid);
        tiltleft(grid);
        tiltdown(grid);
        tiltright(grid);
        if (equal(grid, start))
        {
            cout << endl << "coincidence at cycle: " << cycle << endl;
            break;
        }
        
    }
    int load = get_load(grid);
    cout << endl << "load: " << load << endl;
    return 0;
}
