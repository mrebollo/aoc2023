/*
    Advent of Code 2023
    Day 11: shortest paths between galaxies, part 1
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define N 10
using namespace std;
char space[N][N];

void load_file(string filename){
    ifstream f;
    int i = 0, j = 0;
    char c;
    int galaxy = 0;
    f.open(filename);
    while (f >> c) {
        space[i][(j++) % N] = c;
        if (j % N == 0)
            i++;
    }   
    f.close();
}


void print_map(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            cout << space[i][j];
        cout << endl;
    }
}


char** expanse(char space[][N]){
    return NULL;
}


vector<int> shortest_path(char **map){
    vector<int> pathlen;
    return pathlen;
}


int main(){

    vector<int> pathlen;
    load_file("input.txt");
    print_map();
    char **expanded = expanse(space);
    //print_map(expanded);
    pathlen = shortest_path(expanded);
    int total = 0;
    for(int it: pathlen)
        total += it;
    return 0;
}   