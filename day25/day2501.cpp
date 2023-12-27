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
        void contractMatrix(vector<vector<int> > &M, int &size1, int &size2);
        void removeEdge(set<pair<int, int> > &remaining, int u, int v);
        void updateSubsets(set<int> &subsetA, set<int> &subsetB, int u, int v);
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

void Graph::updateSubsets(set<int> &subsetA, set<int> &subsetB, int u, int v){
    // update subsets
    if(subsetA.find(u) != subsetA.end()){
        subsetA.insert(v);
        subsetB.erase(v); // por si acaso
    }
    else if (subsetB.find(u) != subsetB.end()){
        subsetB.insert(v);
        subsetA.erase(v);
    }
    else if(subsetA.find(v) != subsetA.end()){
        subsetA.insert(u);
        subsetB.erase(u);
    }
    else if (subsetB.find(v) != subsetB.end()){
        subsetB.insert(u);
        subsetA.erase(u);
    }
    else if(subsetA.empty()){
        subsetA.insert(u);
        subsetA.insert(v);
    }  
    else{
        subsetB.insert(u);
        subsetB.insert(v);
    }
    //cout << "A: "; printSet(subsetA);
    //cout << "B: "; printSet(subsetB);
}

void Graph::printSet(set<int> &subset){
    for(auto &i : subset)
        cout << reverseHash(i) << " ";
    cout << endl;
}



void Graph::contractMatrix(vector<vector<int> > &M, int &size1, int &size2){
    int nnodes = size;
    set<pair<int, int> > remaining = edges;
    for(auto &edge : remaining) ;
            //cout << reverseHash(edge.first) << ", " << reverseHash(edge.second) << endl;
        //cout << " -> start contracting" << endl;
    set<int> subsetA, subsetB;
    while(nnodes > 2 ){
        //select random edge
        int sel, selneig;
        do{
            sel = rand() % size;
            selneig = rand() % size;
        }while(M[sel][selneig] == 0);
        contract(M, sel, selneig);
        removeEdge(remaining, sel, selneig);
        updateSubsets(subsetA, subsetB, map[sel], map[selneig]);
        nnodes--;
        //printAdj(M);
        //cout << "remaining: ";
        for(auto &edge : remaining) ;
            //cout << reverseHash(edge.first) << ", " << reverseHash(edge.second) << endl;
        //cout << endl;
    }
    // calculate min cut
    for(auto &edge : remaining){
        int u = edge.first;
        int v = edge.second;
        cout << "lst edge: " << reverseHash(u) << ", " << reverseHash(v) << endl; 
        // insert last node in subset
        if((subsetA.find(u) != subsetA.end() && subsetB.find(v) != subsetB.end()) ||
           (subsetA.find(v) != subsetA.end() && subsetB.find(u) != subsetB.end())){
            continue;
        }
        else if (subsetB.find(u) != subsetB.end() && subsetA.find(v) == subsetA.end()){
            subsetB.insert(v);
            cout << "inserting " << reverseHash(v) << " in B" << endl;
        }
        else if(subsetA.find(v) != subsetA.end() && subsetB.find(u) == subsetB.end()){
            subsetA.insert(u);
            cout << "inserting " << reverseHash(u) << " in A" << endl;
        }
        else if (subsetB.find(v) != subsetB.end() && subsetA.find(u) == subsetA.end()){
            subsetB.insert(u);  
            cout << "inserting " << reverseHash(u) << " in B" << endl;
        }
        else if(subsetA.empty()){
            subsetA.insert(u);
            subsetA.insert(v);
        }  
        else{
            subsetB.insert(u);
            subsetB.insert(v);
        }
        // si no está u, mirar donde le toca
        if(subsetA.find(u) != subsetA.end() && subsetB.find(v) == subsetB.end()){
            subsetB.insert(v);
            cout << "inserting " << reverseHash(v) << " in B" << endl;
        }
        else if (subsetB.find(u) != subsetB.end() && subsetA.find(v) == subsetA.end()){
            subsetA.insert(v);
            cout << "inserting " << reverseHash(v) << " in A" << endl;
        }
        else if(subsetA.find(v) != subsetA.end() && subsetB.find(u) == subsetB.end()){
            subsetB.insert(u);
            cout << "inserting " << reverseHash(u) << " in B" << endl;
        }
        else if (subsetB.find(v) != subsetB.end() && subsetA.find(u) == subsetA.end()){
            subsetA.insert(u);  
            cout << "inserting " << reverseHash(u) << " in A" << endl;
        }
        else if(subsetA.empty()){
            subsetA.insert(u);
            subsetA.insert(v);
        }  
        else{
            subsetB.insert(u);
            subsetB.insert(v);
        }

    }
    cout << "subsetA: "; printSet(subsetA);
    cout << "subsetB: "; printSet(subsetB);
    size1 = subsetA.size();
    size2 = subsetB.size();

}


void Graph::minCut(int &size1, int &size2){
    int n = nodes.size();
    int max1, max2, maxprod = 0;
    generateAdj();
    for (int  i = 0; i < n * n * log(n); i++){
        vector<vector<int> > M = adj;
        contractMatrix(M, size1, size2);
        if(size1 * size2 > maxprod){
            maxprod = size1 * size2;
            max1 = size1;
            max2 = size2;
            cout << "** new max: " << maxprod << endl;
        }
        cout << "--" << endl;
    }
    size1 = max1;
    size2 = max2;
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
    Graph G(N);
    srand(time(NULL));
    //G.mygraph();
    G.readInput("input.txt");
    //G.readInput("adventofcode.com_2023_day_25_input.txt");
    //G.print();
    int size1, size2;
    G.minCut(size1, size2);
    cout << "|C1| = " << size1 << ", |C2| = " << size2 << endl;
    cout << "prod: " << size1 * size2 << endl;
    return 0;
    
}
