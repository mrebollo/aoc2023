/*
advent of code day 17 part 1
path with minimum heat loss
move at most three blocks away
turn 90 deg left or right 
estrategia: recorrido en anchura
*/

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <set>

using namespace std;
#define TEST 1
#ifdef TEST
#define N 4 // 13
#else
#define N 141
#endif

enum direction {up, lef, down, rig};
char sign[4] =  {'^', '<', 'v', '>'};
int tab = 0;
struct node{
    int i, j;
    direction dir;
    int step;
    int loss;
};
}
/*
inline int loss_at(int i, int j, int E[][N][4]) {
    int energy = INT_MAX;
    for(int k = 0; k < 4; k++)
        energy = min(E[i][j][k], energy);
    return energy;
}
*/


inline int min(int a, int b, int c) {return min(a, min(b, c));}   

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

void print(int E[][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            //cout << loss_at(i, j, E) << " ";
            cout << E[i][j] << " ";
        cout << endl;
    }
}

void print(set<pair<int, int> > visited) {
    for(auto it = visited.begin(); it != visited.end(); it++)
        cout << "(" << it->first << ", " << it->second << ") ";
    cout << endl;
}

inline direction turnleft(direction dir) {
    return (direction)((dir + 1) % 4);
}

inline direction turnright(direction dir) {
    return (direction)((dir + 3) % 4);
}

struct node next(struct node &current, direction dir) {
    struct node next = current;
    if(current.dir == up || dir == up)
        next.step++;
    else
        next.step = 0;
    next.dir = dir;
    switch(dir) {
        case up: next.i--; break;
        case down: next.i++; break;
        case lef: next.j--; break;
        case rig: next.j++; break;
    }
    return next;
}

int loss(array<array<int ,N>, N > &grid, int i, int j, direction dir, int step, set<pair<int, int> > visited, int E[][N]){
    queue<struct node> nodelist;
    struct node current = {i, j, dir, step, 0};
    nodelist.push_back(current);
    while(!nodelist.empty()){
        current = nodelist.front();
        nodelist.pop();
        if(current.i < 0 || current.i >= N || current.j < 0 || current.j >= N || (visited.find(make_pair(current.i,current.j)) != visited.end()))
            continue;
        if(current.i == N-1 && current.j == N-1){
            E[i][j] = current.loss;
            return current.loss;
        }
        visited.insert(make_pair(current.i, current.j));
        // go ahead 1, 2 or 3 steps
        int straight, nexti, nextj;
        if(current.step < 3){
            nexti = current.i, nextj = current.j;
            next(current, dir);
            straight = loss(grid, nexti, nextj, dir, ++step, visited, E);
        }
        // turn left
        direction left90 = turnleft(dir);
        nexti = current.i; nextj = current.j;
        next(current, left90);
        int left = loss(grid, nexti, nextj, left90, 0, visited, E);
        // turn right
        direction right90 = turnright(dir);
        nexti = current.i; nextj = current.j;
        next(current, right90);
        int right = loss(grid, nexti, nextj, right90, 0, visited, E);
        current.loss = grid[current.i][current.j] + min(straight, left, right);
        nodelist.push_back(current);
    }
    tab++;
    printf("%*sloss(i: %d, j: %d, dir: %c, step: %d)", tab ,"",  i, j, sign[dir], step);  
    if(i < 0 || i >= N || j < 0 || j >= N || (visited.find(make_pair(i,j)) != visited.end())){
        cout << " -> out" << endl;
        tab--;
        return INT_MAX;
    }
    if(i == N-1 && j == N-1){
        cout << endl;
        print(visited);
        tab--;
        return grid[i][j];
    }
    visited.insert(make_pair(i, j));
    cout << endl;
    // go ahead 1, 2 or 3 steps
    int straight, nexti, nextj;
    if(step < 3){
        nexti = i, nextj = j;
        next(dir, nexti, nextj);
        straight = loss(grid, nexti, nextj, dir, ++step, visited, E);
    }
    // turn left
    direction left90 = turnleft(dir);
    nexti = i; nextj = j;
    next(left90, nexti, nextj);
    int left = loss(grid, nexti, nextj, left90, 0, visited, E);
    // turn right
    direction right90 = turnright(dir);
    nexti = i; nextj = j;
    next(right90, nexti, nextj);
    int right = loss(grid, nexti, nextj, right90, 0, visited, E);
    E[i][j] = grid[i][j] + min(straight, left, right);
    tab--;
    return E[i][j];
}


int main(){
    array<array<int, N> , N> grid;
    // uso similar a la función de memoria de PD
    int E[N][N] = {0};
    set<pair<int, int> > visited;
#ifdef TEST
    load_from_file(grid, "input4.txt");
#else
    load_from_file(grid, "adventofcode.com_2023_day_17_input.txt");
#endif
    loss(grid, 0, 0, rig, 0, visited, E);
#ifdef TEST
    print(grid);
    print(E);
#endif
    int heatloss = E[0][0]; //loss_at(N-1, N-1, E);
    cout << "loss: " << heatloss << endl;
    return 0;
}