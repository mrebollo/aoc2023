/*
advent of code day 23 part 1
longest path in la laberyth
find all paths to ensure keep the longest
dead ends return -infty
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;
int inline max(int a, int b) {return (a > b) ? a : b;}
int dr[4] = {-1, 0, 1, 0}; //up, right, down, left
int dc[4] = {0, 1, 0, -1};
char force[4] = {'^', '>', 'v', '<'};
char barrier[4] = {'v', '<', '^', '>'};

class Laberynth{
    private:    
        vector<string> map;
        size_t size;

    public:
        Laberynth(string filename);
        void print();
        int solve();
    private:
        void findEntryPoint(int &row, int &col);
        int visitCell(int row, int col, int steps);
};

Laberynth::Laberynth(string filename) {
    fstream inputf(filename);
    string line;
    while(getline(inputf, line)){
        map.push_back(line);
    }
    inputf.close();
    size = map.size();
}

void Laberynth::findEntryPoint(int &row, int &col) {
    row = 0;
    col = map[0].find('.');
    map[row][col] = 'O';
}

void Laberynth::print() {
    //simlifica la salida para que se vea mejor
    for(int i = 0; i < size; i++) {
        //cout << map[i] << endl;
        for(int j = 0; j < size; j++)
            if( map[i][j] == 'O')
                cout << 'o';
            else if (map[i][j] == '#')
                cout << '.';
            else if (map[i][j] == '.')
                cout << ' ';
            else
                cout << map[i][j];
        cout << endl;
    }
}

int Laberynth::solve(){
    int startRow, startCol;
    findEntryPoint(startRow, startCol);
    cout << "start: " << startRow << ", " << startCol << endl;
    int len = visitCell(startRow+1, startCol, 1);
    cout << "longest path: " << len << endl;
    return 0;
}

int Laberynth::visitCell(int row, int col, int steps) {
    if (row == size - 1) {
        print();
        cout << "exit in " << steps << " steps" << endl;
        return steps;
    }
    // mark cell as visited and save original value
    char savedtile = map[row][col];
    map[row][col] = 'O';
    int dist[4] = {0};
    for(int i = 0; i < 4; i++){
        int r = row + dr[i];
        int c = col + dc[i];
        //only valid neighbors (reduce calls)
        if(map[r][c] != '#' && map[r][c] != 'O' && map[r][c] != barrier[i])
            dist[i] = visitCell(r, c, steps+1);
    }
    //restore cell
    map[row][col] = savedtile;
    return max(max(dist[0], dist[1]), max(dist[2], dist[3]));
}

int main() {
    Laberynth lab("input.txt");
    //Laberynth lab("adventofcode.com_2023_day_23_input.txt");
    //lab.print();
    lab.solve();
    return 0;
}

