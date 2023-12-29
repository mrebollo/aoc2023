/*
    advent of code 2023
    day 25 part 1
    discconnect wires to separate the network into two parts
    minimal edge-cut problem
    without terminal nodes (min degree = 2) -> Stoer-Wagner algorithm
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <cmath>


using namespace std;

#define N 13
//#define N 1246

struct data{
    string id;
    vector<int> adj;
    data(){id = "";}
};

class Graph{
    private:
        set<int> nodes;
        set<pair<int, int> > edges;
        vector<vector <int> > adj;
        vector<int> map;
        int size;
    public:
        Graph(int n);
        void minCut(int &size1, int &size2);
        void print();
        void printAdj(vector<vector<int> > &mat);
        void readInput(string filename);
        void mygraph();
    private:
        int hash(string id);
        string reverseHash(int id);
        void generateAdj();
        void contract(vector<vector<int> > &M, int u, int v);
        vector<int> contractMatrix(vector<vector<int> > &M);
        void removeEdge(set<pair<int, int> > &remaining, int u, int v);
        void printSet(set<int> &subset);

};  

Graph::Graph(int n){
    size = 0;
}

int Graph::hash(string id){
    int h = 0;
    int pow[3] = {26*26, 26, 1};
    for(int i=0; i<3; i++)
        h += (id[i] - 'a') * pow[i];
    return h;
}

string Graph::reverseHash(int id){
    string s = "";
    int pow[3] = {26*26, 26, 1};
    for(int i=0; i<3; i++){
        s += (id / pow[i]) + 'a';
        id %= pow[i];
    }
    return s;
}

void Graph::generateAdj(){
    size = nodes.size();
    map.resize(size);
    adj.resize(size);
    for(int i = 0; i < size; i++)
        adj[i].resize(size);
    int i = 0;
    for(auto &node : nodes)
        map[i++] = node;
    for(auto &edge : edges){
        int mi = 0, mj = 0;
        for(int j = 0; j < size; j++){
            if(map[j] == edge.first) mi = j;
            if(map[j] == edge.second) mj = j;
        }
        adj[mi][mj] = 1;
        adj[mj][mi] = 1;
    }
    //printAdj(adj);
}


void Graph::contract(vector<vector<int> > &M, int sel, int selneig){
    int nnodes = M.size();
    // contract = sum in the matrix
    //cout << "contracting " << selneig << " into " << sel;
    //cout << " " << reverseHash(map[sel]) << "/" << reverseHash(map[selneig]) << endl    ;
    for(int i = 0; i < nnodes; i++){
        M[sel][i] += M[selneig][i];
        M[i][sel] += M[i][selneig];
    }  
    // delete selneig
    for(int i = 0; i < nnodes; i++){
        M[selneig][i] = 0;
        M[i][selneig] = 0;
    }
    // delete self loops
    M[sel][sel] = 0;
}

void Graph::removeEdge(set<pair<int, int> > &remaining, int u, int v){
    //remove contracted edge
    remaining.erase(make_pair(map[u], map[v]));
    remaining.erase(make_pair(map[v], map[u]));
    // point all v edges to u
    auto edge = remaining.begin();
    while( edge != remaining.end()){
        auto current = edge++; //points to next, to avoid problem with last element erasing
        // it's not possible to modify a set-pair element
        if(current->first == map[v]){
            int aux = current->second;
            remaining.erase(current);
            //insert just if symmetric is not there
            if(remaining.find(make_pair(aux,map[u])) == remaining.end())
                remaining.insert(make_pair(map[u], aux));
            //cout << "end after remove: " << edge->first << ", " << edge->second << " nodes: " << remaining.size() << endl;
        }
        if(current->second == map[v]){
            int aux = current->first;
            remaining.erase(current);
            if(remaining.find(make_pair(map[u],aux)) == remaining.end())
                remaining.insert(make_pair(aux, map[u]));
        }
        //cout << "end after remove: " << edge->first << ", " << edge->second << " nodes: " << remaining.size()<< endl;
    }
}



vector<int> Graph::contractMatrix(vector<vector<int> > &M){
    int nnodes = size;
    vector<int> comp;
    set<pair<int, int> > remaining = edges;
    vector<int> compsize(nnodes, 1);
    while(nnodes > 2 ){
        //select random edge
        int randit = rand() % remaining.size();
        auto edge = remaining.begin();
        advance(edge, randit);
        int sel = edge->first;
        int selneig = edge->second;
        // hacer una función o mejorarlo
        for(int i = 0; i < map.size(); i++)
            if(map[i] == sel){
                sel = i;
                break;
            }
        for(int i = 0; i < map.size(); i++)
            if(map[i] == selneig){
                selneig = i;
                break;
            }
        contract(M, sel, selneig);
        compsize[sel] += compsize[selneig];
        compsize[selneig] = 0;
        removeEdge(remaining, sel, selneig);
        nnodes--;
    }
    //calculate mincut
    int mincut = 0;
    nnodes = size;
    for(int i = 0; i < nnodes; i++)
        for(int j = i; j < nnodes; j++)
            mincut += M[i][j];
    comp.push_back(mincut);
    for(int c: compsize )
        if( c > 0)
            comp.push_back(c);
    return comp;
}


void Graph::minCut(int &size1, int &size2){
    int n = nodes.size();
    vector<int> minc;
    minc.push_back(n);
    generateAdj();
    for (int  i = 0; i < n * n * log(n); i++){
        vector<vector<int> > M = adj;
        vector<int> comp = contractMatrix(M);
        //cout << "mincut: " << comp[0] << endl;
        if(comp[0] < minc[0] && comp[1]*comp[2] > minc[1]*minc[2]){
            minc = comp;
            cout << "[" << i << "] mincut: " << comp[0];
            cout << " |C1| = " << comp[1] << ", |C2| = " << comp[2] << endl;
        }
        //cout << "--" << endl;
    }   
    size1 = minc[1];
    size2 = minc[2];
}



void Graph::print(){
    for(auto &i: nodes)
        cout << reverseHash(i) << " ";
    cout << endl;
    for(auto &i : edges)
        cout << reverseHash(i.first) << ", " << reverseHash(i.second) << endl;
}

void Graph::printAdj(vector<vector<int> > &mat){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            cout << mat[i][j];
        cout << endl;
    }
}


// leer el fichero
void Graph::readInput(string filename){
    ifstream file(filename);
    string line, u, v;

    while(getline(file, line)){
        istringstream iss(line);
        getline(iss, u, ':');
        nodes.insert(hash(u));
        getline(iss, v, ' '); // skip space after ':
        while(getline(iss, v, ' ')){
            nodes.insert(hash(v));
            edges.insert(make_pair(hash(u), hash(v)));
        }
    }
}


void Graph::mygraph(){
    nodes.insert(hash("aaa"));
    nodes.insert(hash("bbb"));
    nodes.insert(hash("ccc"));
    nodes.insert(hash("ddd"));
    edges.insert(make_pair(hash("aaa"), hash("bbb")));
    edges.insert(make_pair(hash("aaa"), hash("ccc")));
    edges.insert(make_pair(hash("bbb"), hash("ccc")));
    edges.insert(make_pair(hash("ccc"), hash("ddd")));
}

int main(int argc, char **argv){
    Graph G(4);
    srand(time(NULL));
    //G.mygraph();
    //G.readInput("input.txt");
    G.readInput("adventofcode.com_2023_day_25_input.txt");
    //G.print();
    int size1, size2;
    G.minCut(size1, size2);
    cout << "|C1| = " << size1 << ", |C2| = " << size2 << endl;
    cout << "prod: " << size1 * size2 << endl;
    return 0;
    
}
