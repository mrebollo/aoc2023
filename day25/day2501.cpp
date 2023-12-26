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
        void addNode(string label);
        void addEdge(string v, string w);
        void minCut();
        void print();
        void printAdj();
        void readInput(string filename);
    private:
        int hash(string id);
        string reverseHash(int id);
        void generateAdj();
        void contract(vector<vector<int> > &M, int u, int v);
        vector<int> contractMatrix();
        int BFS(int s);
        int removeEdge(vector<int> &perm);
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
    }
    //printAdj();
}



// guardo en parent una de las compoentes conexas
int Graph::BFS(int s){
    int nnodes = adj.size();
    vector<bool> visited(nnodes, false);
    queue<int> q;
    int compsize = 1;
    q.push(s);
    visited[s] = true;
    cout << "BFS: ";
    while(!q.empty()){
        int u = q.front();
        q.pop();
        cout << reverseHash(map[u]) << " ";
        for(int v = 0; v < nnodes; v++){
            if(!visited[v] && adj[u][v] > 0){
                q.push(v);
                visited[v] = true;
                compsize++;
            }
        }
    }
    cout << endl << "size: " << compsize << endl;
    return compsize;
}


void Graph::contract(vector<vector<int> > &M, int sel, int selneig){
    int nnodes = M.size();
    // contract = sum in the matrix
    cout << "contracting " << sel << " and " << selneig << endl;
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

vector<int> Graph::contractMatrix(){
        vector<vector<int> > M = adj;
        vector<int> perm = map;
        for(int i = 0; i < perm.size(); i++) 
            perm[i] = i;
        while(perm.size() > 2){
            //shuffle using yates algorithm
            int j = rand() % (perm.size()-1);
            int sel = perm[j];
            perm[j] = perm.back();
            perm.pop_back();
            
            // selec random neighbor of sel
            vector<int> neigs;
            for(int i = 0; i < adj.size(); i++)
                if(M[sel][i] > 0) neigs.push_back(i);
            int randneig = rand() % neigs.size();
            int selneig = neigs[randneig];
            contract(M, sel, selneig);
            // remove selneig from perm
            for(int i = 0; i < perm.size(); i++)
                if(perm[i] == selneig){
                    perm[i] = perm.back();
                    perm.pop_back();
                    break;
                }
            //printAdj();     
        }
        return perm;
}

int Graph::removeEdge(vector<int> &perm){
    int u = map[perm[0]];
    int v = map[perm[1]];
    adj[perm[0]][perm[1]] = 0;
    adj[perm[1]][perm[0]] = 0;
    cout << "remove edge: " << reverseHash(u) << ", " << reverseHash(v) << endl;
    int comp1size = BFS(perm[0]);
    cout << "comp1size: " << comp1size << endl;
    cout << "comp2size: " << size - comp1size << endl;
    cout << "prod: " << comp1size * (size - comp1size) << endl;
    return comp1size;
}


inline void Graph::addNode(string label){
    int vid = hash(label);
    map[size++] = vid;
}

void Graph::addEdge(string v, string w){
    int vid = hash(v);
    int wid = hash(w);
    adj[vid][wid] = 1;
}

void Graph::print(){
    for(auto &i: nodes)
        cout << reverseHash(i) << " ";
    cout << endl;
    for(auto &i : edges)
        cout << reverseHash(i.first) << ", " << reverseHash(i.second) << endl;
}

void Graph::printAdj(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            cout << adj[i][j];
        cout << endl;
    }
}

void Graph::minCut(){
    generateAdj();
    int comp1size;
    do{
        vector<int> edge = contractMatrix();
        comp1size = removeEdge(edge);
    }while(comp1size == size);
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
            edges.insert(make_pair(hash(v), hash(u)));
        }
    }
}


int main(int argc, char **argv){
    Graph G(N);
    srand(time(NULL));
    G.readInput("input.txt");
    //G.readInput("adventofcode.com_2023_day_25_input.txt");
    //G.print();
    G.minCut();
    return 0;
    
}
/*
521676
524126
*/