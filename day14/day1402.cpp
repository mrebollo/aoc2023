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

// para automatizar la compilación de las dos versiones: prueba y final
// comentar la siguiente línea para compilar la versión final 
//#define TEST 1
#ifdef TEST
#define N 10
#else
#define N 100
#endif

// estructura para almacenar todos los estados anteriores del grid
// tiene que ser una estructura para poder usar el vector<> de la STL
// hay que definir el constructor para poder copiar el grid
struct G{
    char gr[N][N];
    G(char grid[N][N]) {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                gr[i][j] = grid[i][j];
    }
};


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
        // mueve las rocas una posición hacia arriba (north)
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
        // mueve las rocas una posición hacia abajo (south)
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
        // mueve las rocas una posición hacia la izquierda (west)
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
        // mueve las rocas una posición hacia la derecha (east)
        for(int i = 0; i < N; i++)
            for(int j = N-2; j >= 0; j--)
                if(grid[i][j] == 'O' && grid[i][j+1] == '.'){
                    grid[i][j+1] = grid[i][j];
                    grid[i][j] = '.';
                    moves++;
                }
    }while(moves > 0);
}

// un ciclo es un movimiento completo north->west->south->east
void cycle(char grid[N][N]) {
    tiltup(grid);
    tiltleft(grid);
    tiltdown(grid);
    tiltright(grid);
}

// calcula sla carga sobre el muro norte (la suma de las distancias de las rocas al suelo)
int get_load(char grid[N][N]) {
    int load = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(grid[i][j] == 'O')
                load += N - i;
    return load;
}

// es más eficiente empezar por el final, por el orden de los tilt
// acaba haciendo south->east: las rocas se agrupan abajo a la derecha
bool equal(char grid[][N], char ref[][N]) {
    for(int i = N-1; i >= 0; i--)
        for(int j = N-1; j >= 0; j--)
            if(grid[i][j] != ref[i][j])
                return false;
    return true;
}

// comprueba si el grid actual ya se ha visto antes
int loopfound(char grid[N][N], vector<G> &history){
    for(int i = 0; i < history.size(); i++)
        if(equal(grid, history[i].gr))
            return i;
    return -1;
}

// imprime juntos dos grids para compararlos    
void printaside(char grid[N][N], char ref[N][N]) {
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            cout << grid[i][j];
        cout << "\t";
        for(int j = 0; j < N; j++)
            cout << ref[i][j];
        cout << endl;
    }
}


int main() {
    fstream inputf;
    string line;
    char grid[N][N];
    vector<G> history;

#ifdef TEST
    load_from_file(grid, "input.txt");
#else
    load_from_file(grid, "adventofcode.com_2023_day_14_input.txt");
#endif
    history.push_back(grid);
    int i = 0, duplicate;
    // busca el periodo: repite hasta que se repita un estado o llegue a 1000000000
    do{
        cycle(grid);
        duplicate = loopfound(grid, history);
        history.push_back(grid);
        i++;
    }while (duplicate < 0 && i < 1000000000);
    if (duplicate >= 0) {
        cout << endl << "coincidence at cycle: " << duplicate << endl;
#ifdef TEST
        cout << "current: "  << i << "\t\t previous: " << duplicate << endl;
        printaside(grid, history[duplicate].gr);
#endif
    }
    // calcula el periodo y el resto de ciclos
    int looplength = i - duplicate;
    int cycles = (1000000000 - duplicate) / (i - duplicate);
    int remaining = (1000000000 - duplicate) % (i - duplicate);
    cout << "found: "  << duplicate << endl;
    cout << " last: " << duplicate + cycles*looplength << endl;
    cout << " remains: " << remaining << endl;
    cout << " period: " << looplength << endl;
    cout << " cycles: " << cycles << endl;

    //itera el resto de veces desde el periodo hasta llegar a 1000000000
    if(remaining > 0)
        for(int i = 0; i < remaining; i++)
            cycle(grid);
    int load = get_load(grid);
    cout << endl << "load: " << load << endl;
    return 0;
}
