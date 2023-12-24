#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
enum coord {x, y, z};

#define DIM 2

class Stone{
    private:
        double pos[3], vel[3];
        int dim;
    public:
        Stone(double px, double py, double pz, 
              double vx, double vy, double vz);
        //pendiente = (y2-y1)/(x2-x1) = vy/vx
        inline double m() {return (double)vel[y] / vel[x]; }
        // recta que pasa por (0,0) y (x,y) es (y - y0) = m(x - x0)
        inline double n() {return pos[y] - m() * pos[x]; }
        // check if point is before the stone
        inline bool before(double point[]) {return (point[x] < pos[x] && vel[x] > 0) ||  (point[x] > pos[x] && vel[x] < 0); }
        friend ostream& operator<<(ostream& os, const Stone& s);

};  

Stone::Stone(double px, double py, double pz, 
             double vx, double vy, double vz){
    pos[x] = px*1e-6; pos[y] = py*1e-6; pos[z] = pz*1e-6;
    vel[x] = vx*1e-6; vel[y] = vy*1e-6; vel[z] = vz*1e-6;
    dim = DIM;
}


ostream& operator<<(ostream& os, const Stone& s){
    os << s.pos[x] << ", " << s.pos[y] << ", " << s.pos[z] << " @ ";
    os << s.vel[x] << ", " << s.vel[y] << ", " << s.vel[z] ;
    return os;
}


vector<Stone> loadFile(string filename){
    vector<Stone> stones;
    ifstream file(filename);
    string line;
    double px, py, pz, vx, vy, vz;
    while(getline(file, line)){
        sscanf(line.c_str(), "%lf, %lf, %lf @ %lf, %lf, %lf", 
                             &px, &py, &pz, &vx, &vy, &vz);
        stones.push_back(Stone(px, py, pz, vx, vy, vz));
    }
    return stones;
}

void print(vector<Stone> stones){
    for(auto &s : stones){
        cout << s << endl;
    }
}

// stone inside area
bool inside(double point[], double area[]){
    for(int i = 0; i < DIM; i++)
        if(point[i] < area[0] || point[i] > area[1])
            return false;
    return true;
}




bool collision(Stone a, Stone b, double area[]){
    bool collision = false;
    //cout << "Hailstone A: " << a << endl;
    //cout << "Hailstone B: " << b << endl;
    if(a.m() != b.m()){
        double col[DIM];
        col[x] = (b.n() - a.n()) / (a.m() - b.m());
        if(a.before(col) || b.before(col)){
            cout << "Collision in the past (" << col[x] << ", " << col[y] << ")" << endl;
            return false;
        }
        col[y] = a.m() * col[x] + a.n();
        if (inside(col, area)){
            cout << " (*) Collision inside area (" << col[x] << ", " << col[y] << ")" << endl;
            collision = true;
        }
        else
            cout << "Collision outside area (" << col[x] << ", " << col[y] << ")" << endl;
    }
    else    
        cout << "Paths are parallel" << endl;
    return collision;
}

int countCollisions(vector<Stone> stones, double area[]){
    int collisions = 0;
    for(int i = 0; i < stones.size(); i++){
        for(int j = i + 1; j < stones.size(); j++){
            collisions += collision(stones[i], stones[j], area);
        }
    }
    return collisions;
}


int main(){
    //vector<Stone> stones = loadFile("input.txt");
    vector<Stone> stones = loadFile("adventofcode.com_2023_day_24_input.txt");
    //print(stones);
    //double area[] = {7*1e-6,27*1e-6};
    double area[2] = {200000000,400000000};
    int numcol = countCollisions(stones, area); 
    cout << "Number of collisions: " << numcol << endl;
    return 0;
}