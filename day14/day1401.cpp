#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define N 10


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


int get_load(char grid[N][N]) {
    int load = 0;
    return load;
}

int main() {
    fstream inputf;
    string line;
    char grid[N][N];

    load_from_file(grid, "input.txt");
    //load_from_file(grid, "adventofcode.com_2023_day_14_input.txt");
    print(grid);
    tiltup(grid);
    cout << "--" << endl;
    print(grid);
    int load = get_load(grid);
    cout << "load: " << load << endl;
    return 0;
}
