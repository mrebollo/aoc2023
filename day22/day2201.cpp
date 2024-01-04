/**
 advent of code 2023 day 22 part 1
 tetris 3d. calcular borrado seguro
 **/


#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

using namespace std;

struct block{
    int id;
    int x1, y1, z1;
    int x2, y2, z2;
    block(int id, int x1, int y1, int z1, int x2, int y2, int z2): 
        id(id), x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2) {}
    bool operator()(const block &a, const block &b){
        if (a.z1 == b.z1)
            if (a.z2 == b.z2)
                if (a.x1 == b.x1)
                    return (a.y1 < b.y1);
                else
                    return (a.x1 < b.x1);
            else
                return (a.z2 < b.z2);
        else
            return (a.z1 < b.z1);
    }
};

bool operator<(const block &a, const block &b){
    if (a.z1 == b.z1)
        if (a.z2 == b.z2)
            if (a.x1 == b.x1)
                return (a.y1 < b.y1);
            else
                return (a.x1 < b.x1);
        else
            return (a.z2 < b.z2);
    else
        return (a.z1 < b.z1);
}


void insertblock(vector<vector<vector<int> > > &mat, block b){
    for(int i = b.x1; i <= b.x2; i++)
        for(int j = b.y1; j <= b.y2; j++)
            for(int k = b.z1; k <= b.z2; k++)
                mat[i][j][k] = b.id;
}


void removeblock(vector<vector<vector<int> > > &mat, block b){
    for(int i = b.x1; i <= b.x2; i++)
        for(int j = b.y1; j <= b.y2; j++)
            for(int k = b.z1; k <= b.z2; k++)
                mat[i][j][k] = 0;
}


bool isstable(vector<vector<vector<int> > > &mat, set<block> &board, int level){
    //para cada nivel entre zmin y zmax, 
    //comprobar que ninguna pieza esté sin apoyar
    //=> por debajo algún elemento es != 0
    //no funciona equal_range() ??
    for(auto it = board.begin(); it != board.end(); it++){
        if (it->z1 == level+1){
            //check if any element below is != 0
            for(int i = it->x1; i <= it->x2; i++)
                for(int j = it->y1; j <= it->y2; j++)
                    if (mat[i][j][level] != 0)
                        return true;
        }
    }
    return false;
}


int safeblocks(vector<vector<vector<int> > > &mat, set<block> &board){
    int count = 0;
    for(auto b: board){
        removeblock(mat, b);
        bool stable = isstable(mat, board, b.z2);
        insertblock(mat, b);
        if (stable) {
            cout << "block " << b.id << " is safe" << endl;
            count++;
        }
    }
    return count;
}

 
set<block> loadboard(string filename, int &x, int &y, int &z){
    fstream inputf(filename);
    string line;
    int i = 1;
    set<block> board;
    x = 0; y = 0; z = 0;
    int x1, y1, z1, x2, y2, z2;
    while(getline(inputf, line)){
        sscanf(line.c_str(), "%d,%d,%d~%d,%d,%d", &x1, &y1, &z1, &x2, &y2, &z2);
        board.insert(block(i++, x1, y1, z1, x2, y2, z2));
        if (x2 >= x) x = x2 + 1;
        if (y2 >= y) y = y2 + 1;
        if (z2 >= z) z = z2 + 1;
    }
    inputf.close();
    return board;
}


void loadmatrix(vector<vector<vector<int> > > &mat, set<block> &board){
    //TODO throw blocks until they are stacked
    for(auto b: board)
        insertblock(mat, b);
}


void printboard(set<block> &board){
    for(auto b: board){
        cout << "(" << b.x1 << "," << b.y1 << "," << b.z1 << ") - ";
        cout << "(" << b.x2 << "," << b.y2 << "," << b.z2 << ")" << endl;
    }
}

void printslides(vector<vector<vector<int> > > &mat, int dimx, int dimy, int dimz){
    for(int k = 0; k < dimz; k++){
        cout << "z = " << k << endl;
        for(int i = 0; i < dimx; i++, cout << endl)
            for(int j = 0; j < dimy; j++)
                cout << setw(3) << mat[i][j][k] << " ";
    }
}


int main(){
    int dimx, dimy, dimz;
    set<block> board = loadboard("input.txt", dimx, dimy, dimz);
    printboard(board);
    vector<vector<vector<int> > > matrix(dimx, vector<vector<int> >(dimy, vector<int>(dimz, 0)));
    loadmatrix(matrix, board);
    printslides(matrix, dimx, dimy, dimz);
    int safe = safeblocks(matrix, board);
    cout << "safe blocks: " << safe << endl;
    return 0;
}