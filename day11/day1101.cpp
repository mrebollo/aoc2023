/*
    Advent of Code 2023
    Day 11: shortest paths between galaxies, part 1
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define N 140
using namespace std;
char space[N][N];

struct coord{
    int i;
    int j;
};


vector<coord> load_file(string filename){
    vector<coord> galaxies;
    coord gcoor;
    ifstream f;
    int i = 0, j = 0;
    char c;
    f.open(filename);
    while (f >> c) {
        if(c == '#') {
            gcoor.i = i;
            gcoor.j = j;
            galaxies.push_back(gcoor);
        }
        space[i][j++] = c;
        if (j == N){
            i++;
            j = 0;
        }
    }
    f.close();
    return galaxies;
}


void print_map(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            cout << space[i][j];
        cout << endl;
    }
}


void expanse_rows(vector<coord> &galaxies){
    // expanse rows
    cout << "rows without galaxies: ";
    int i, j;
    for (i = N-1; i >=0; i--){
        for (j = 0; j < N; j++)
            if (space[i][j] == '#')
                break;
        if (j == N) // no galaxies -> add 1 to galaxy rows 
        {
            cout << i << " ";
            for (int k = 0; k < galaxies.size(); k++)
                if (galaxies[k].i > i) (galaxies[k].i)++;
        }
    }
    cout << endl;
}


void expanse_cols(vector<coord> &galaxies){
    // expanse cols
    cout << "cols without galaxies: ";
    int i, j;
    for (j = N-1; j >= 0; j--){
        for (i = 0; i < N; i++)
            if (space[i][j] == '#')
                break;
        if (i == N) // no galaxies -> add 1 to galaxy cols 
        {
            cout << j << " ";
            for (int k = 0; k < galaxies.size(); k++)
                if (galaxies[k].j > j) (galaxies[k].j)++;
        }
    }
    cout << endl;
}


void expanse(vector<coord> &galaxies){
    expanse_rows(galaxies);
    expanse_cols(galaxies);
}


vector<int> shortest_path(vector<coord> galaxies){
    vector<int> pathlen;
    for(int i = 0; i < galaxies.size(); i++)
        for(int j = i + 1; j < galaxies.size(); j++)    
            pathlen.push_back(abs(galaxies[i].i - galaxies[j].i) + abs(galaxies[i].j - galaxies[j].j));
    return pathlen;
}


void print_expanded(vector<coord> galaxies){
    int ng = galaxies.size();
    int k = 0;
    for(int i = 0; i < N+ng; i++){
        for(int j = 0; j < N+ng; j++){
            if(i == galaxies[k].i && j == galaxies[k].j){
                cout << "#";
                k++;
            }
            else cout << ".";
        }
        cout << endl;
    }
}


int main(){
    vector<int> pathlen;
    vector<coord> galaxies;
    //galaxies = load_file("input.txt");
    galaxies = load_file("adventofcode.com_2023_day_11_input.txt");
    print_map();
    expanse(galaxies);
    print_expanded(galaxies);
    pathlen = shortest_path(galaxies);
    int total = 0;
    for(int it: pathlen){
        cout << it << " ";
        total += it;
    }
    cout << endl << "Total: " << total << endl;
    return 0;
}   