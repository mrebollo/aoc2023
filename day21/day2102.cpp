/*
Advent of code 2023
Day 21 part 2
find positions after n steps away from start position
variation: infinite grid, repeating pattern in mosaic
strategy: when you're out of the grid, launch a copy on the new grid
varying the start position (is the entry point in the grid)
- grid expands in four directions (not diagonal ones)
- do caltulate all possible evolutions from entry points (perimeter)?
  -> no, since multiple entry points at different times 
trick: expanded tiles flow goes inside from the borders
        border = prev border + 1
        diagonal border
generar patrones de flujo en las 4 direcciones + 4 esquinas (desde uno)
y sumar a los valores del perimetro de visitados en el grid original
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>


using namespace std;
struct coord { int i, j, it; };
vector<string> grid;

// read input file
void load_grid(string filename) {
    ifstream inputf(filename);
    string line;
    while (getline(inputf, line)) 
        grid.push_back(line);
    int size = grid.size();
    inputf.close();
    cout << "Grid loaded" << endl;
    cout << "Size: " << size << endl;
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
vector<vector<int> > walk_from(queue<coord> &positions) {
    int size = grid.size();
    int nnv = 0; // number of non visited
    vector<vector<int> > visited = vector<vector<int> >(size, vector<int>(size, 0));
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++){
            visited[i][j] = grid[i][j] == '#' ? -1 : 0;
            if(grid[i][j] != '#') nnv++;
        }
    queue<coord> initial = positions;
    while(!initial.empty()){
        coord sp = initial.front();
        initial.pop();
        visited[sp.i][sp.j] = sp.it;
    }
    coord cur = positions.front();
    positions.pop();
    do{
            visited[cur.i][cur.j] = cur.it;
            // check u, d, l, r positions
            if(cur.i > 0 && grid[cur.i-1][cur.j] == '.' && visited[cur.i-1][cur.j] == 0){
                visited[cur.i-1][cur.j] = cur.it+1;
                nnv--;
                coord next = {cur.i-1, cur.j, cur.it+1};
                positions.push(next);
            }
            if(cur.i < size-1 && grid[cur.i+1][cur.j] == '.' && visited[cur.i+1][cur.j] == 0) {
                visited[cur.i+1][cur.j] = cur.it+1;
                nnv--;
                coord next = {cur.i+1, cur.j, cur.it+1};
                positions.push(next);
            }
            if(cur.j > 0 && grid[cur.i][cur.j-1] == '.' && visited[cur.i][cur.j-1] == 0) {
                visited[cur.i][cur.j-1] = cur.it+1;
                nnv--;
                coord next = {cur.i, cur.j-1, cur.it+1};
                positions.push(next);
            }
            if(cur.j < size-1 && grid[cur.i][cur.j+1] == '.' && visited[cur.i][cur.j+1] == 0) {
                visited[cur.i][cur.j+1] = cur.it+1;
                nnv--;
                coord next = {cur.i, cur.j+1, cur.it+1};
                positions.push(next);
            }
            
           // get next position (BFS)
            if(!positions.empty()){
                cur = positions.front();
                positions.pop();
            }
    // condiciones redundantes: revisar porque si no están todas bucle infinito
    }while(!positions.empty() && nnv > 0 );
    return visited;
}

int walked_away(vector<vector<int> > visited) {
    int size = visited.size();
    int walkedaway = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++){
            printf("%2d ", visited[i][j]);
            if(visited[i][j] % 2 == 1 && visited[i][j] > 0)
                walkedaway++;
        }
        cout << endl;
    }
    return walkedaway;
}


// main
int main() {
    // load input
    load_grid("input.txt");
    //print_grid();
    //load_grid("adventofcode.com_2023_day_21_input.txt");
    int size = grid.size();
    int steps = size < 20 ? 20 : 64;
    coord start = find_start();
    //main grid
    queue<coord> positions;
    positions.push(start);
    vector<vector<int> > central = walk_from(positions);
    int pos = walked_away(central);
    cout << "Central Positions: " << pos << endl;

    //upper grid flows from bottom border
    positions = queue<coord>();
    for(int j = 0; j < size; j++){
        coord next = {size-1, j , 1};
        positions.push(next);
    }
    vector<vector<int> > north= walk_from(positions);
    pos = walked_away(north);
    cout << " North Positions: " << pos << endl;

    //lower grid flows from upper border
    positions = queue<coord>();
    for(int j = 0; j < size; j++){
        coord next = {0, j , 1};
        positions.push(next);
    }
    vector<vector<int> > south= walk_from(positions);
    pos = walked_away(south);
    cout << "South Positions: " << pos << endl;

    //left grid flows from right border
    positions = queue<coord>();
    for(int i = 0; i < size; i++){
        coord next = {i, size-1 , 1};
        positions.push(next);
    }
    vector<vector<int> > west= walk_from(positions);
    pos = walked_away(west);
    cout << " West Positions: " << pos << endl;

    //right grid flows from left border
    positions = queue<coord>();
    for(int i = 0; i < size; i++){
        coord next = {i, 0 , 1};
        positions.push(next);
    }
    vector<vector<int> > east= walk_from(positions);
    pos = walked_away(east);
    cout << " East Positions: " << pos << endl;

    // northwest grid flows from top right corner
    positions = queue<coord>();
    coord topright = {size-1, 0 , 1};
    positions.push(topright);
    vector<vector<int> > nw= walk_from(positions);
    pos = walked_away(nw);
    cout << "Northwest Positions: " << pos << endl;
    
    // northeast grid flows from top left corner
    positions = queue<coord>();
    coord topleft = {size-1, size-1 , 1};
    positions.push(topleft);
    vector<vector<int> > ne= walk_from(positions);
    pos = walked_away(ne);
    cout << "Northeast Positions: " << pos << endl;
    
    // southwest grid flows from bottom right corner
    positions = queue<coord>();
    coord botrig = {0, 0 , 1};
    positions.push(botrig);
    vector<vector<int> > sw= walk_from(positions);
    pos = walked_away(sw);
    cout << "Southwest Positions: " << pos << endl;

    // southeast grid flows from bottom left corner
    positions = queue<coord>();
    coord botleft = {0, size-1 , 1};
    positions.push(botleft);
    vector<vector<int> > se= walk_from(positions);
    pos = walked_away(se);
    cout << "Southeast Positions: " << pos << endl;

    /*
    Esquema de expansion
    2 1 2
    1 0 1
    2 1 2

    pasos totales / max 3x3 grid flow completo
    añadir la expansión hasta pasos totales % max 
    
    */

    return 0;
}