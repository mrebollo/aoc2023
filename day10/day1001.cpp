/*
    Advent of Code 2023
    Day 10: pipes max distance in loop, part 1
*/

#include <iostream>
#include <fstream>
#define N 5
inline int max(int a, int b) { return a > b ? a : b; }
using namespace std;

int dist[N][N];
char pipes[N][N];
int si, sj, loop = 0;

void load_file(string filename){
    ifstream f;
    int i = 0, j = 0;
    char c;
    f.open(filename);
    while (f >> c) {
        pipes[i][j] = c;
        if(c == 'S'){
            si = i;
            sj = j;
        }
        j++;
        if (j == N) {
            i++;
            j = 0;
        }
    }   
    f.close();
}

void print_pipes(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            cout << pipes[i][j];
        cout << endl;
    }
}

char identify(int i, int j){
    char *up, *down, *left, *right;
    up = j > 0 ?  &pipes[i-1][j] : NULL;
    down = j < N-1 ? &pipes[i+1][j] : NULL;
    left = i > 0 ? &pipes[i][j-1] : NULL;
    right = i < N-1 ? &pipes[i][j+1] : NULL;
    if(up && down && (*up == '|' || *up == 'F' || *up == '7') && (*down == '|' || *down == 'F' || *down == '7'))
        return '|';
    if(left && right && (*left == '-' || *left == 'F' || *left == 'J') && (*right == '-' || *right == 'F' || *right == 'J'))
        return '-';
    if(up && right && (*up == '|' || *up == 'F' || *up == '7') && (*right == '-' || *right == 'J' || *right == '7'))
        return 'L';
    if(up && left && (*up == '|' || *up == 'F' || *up == '7') && (*left == '-' || *left == 'L' || *left == 'F'))
        return 'J';
    if(down && right && (*down == '|' || *down == 'L' || *down == 'J') && (*right == '-' || *right == 'J' || *right == '7'))
        return 'F';
    if(down && left && (*down == '|' || *down == 'L' || *down == 'J') && (*left == '-' || *left == 'L' || *left == 'F'))
        return '7';
}


int longest_path(int i, int j){
    if (dist[i][j] != -1)
        return dist[i][j];
    if(i == si && j == sj && loop)
        return 0;
    loop = 1;
    if (pipes[i][j] == '|'){
        dist[i][j] = 1 + max(longest_path(i-1, j), longest_path(i+1, j));
    }
    if (pipes[i][j] == '-'){
        dist[i][j] = 1 + max(longest_path(i, j-1), longest_path(i, j+1));
    }
    if (pipes[i][j] == 'L'){
        dist[i][j] = 1 + max(longest_path(i-1, j), longest_path(i, j+1));
    }
    if (pipes[i][j] == 'J'){
        dist[i][j] = 1 + max(longest_path(i-1, j), longest_path(i, j-1));
    }
    if (pipes[i][j] == 'F'){
        dist[i][j] = 1 + max(longest_path(i+1, j), longest_path(i, j+1));
    }
    if (pipes[i][j] == '7'){
        dist[i][j] = 1 + max(longest_path(i+1, j), longest_path(i, j-1));
    }
    return dist[i][j];
}


int main()
{
    for (int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            dist[i][j] = -1;
    load_file("input11.txt");
    print_pipes();
    cout << "Start at (" << si << ", " << sj << ")" << endl;
    pipes[si][sj] = identify(si, sj);
    print_pipes();
    int maxdist = longest_path(si, sj);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            cout << dist[i][j];
        cout << endl;
    }
    cout << "Max distance: " << maxdist << endl;
    return 0;
}