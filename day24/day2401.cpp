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
        long int pos[3], vel[3];
        int dim;
    public:
        Stone(long int px, long int py, long int pz, 
              long int vx, long int vy, long int vz);
        void move();
        void print();
        //pendiente = (y2-y1)/(x2-x1) = vy/vx
        inline float m() {return (float)vel[y] / vel[x]; }
        // recta que pasa por (0,0) y (x,y) es (y - y0) = m(x - x0)
        inline float n() {return pos[y] - m() * pos[x]; }
        friend ostream& operator<<(ostream& os, const Stone& s);
};  

Stone::Stone(long int px, long int py, long int pz, 
             long int vx, long int vy, long int vz){
    pos[x] = px; pos[y] = py; pos[z] = pz;
    vel[x] = vx; vel[y] = vy; vel[z] = vz;
    dim = DIM;
}

void Stone::move(){
    for(int i = 0; i < dim; i++){
        pos[i] += vel[i];
    }
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
    int px, py, pz, vx, vy, vz;
    while(getline(file, line)){
        sscanf(line.c_str(), "%d, %d, %d @ %d, %d, %d", 
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
    inline bool inside(float point[], int area[]){
        for(int i = 0; i < DIM; i++)
            if(point[i] < area[0] || point[i] > area[1])
                return false;
        return true;
    }


bool collision(Stone a, Stone b, int area[]){
    bool collision = false;
    cout << "Hailstone A: " << a << endl;
    cout << "Hailstone B: " << b << endl;
    if(a.m() != b.m()){
        float col[DIM];
        col[x] = (b.n() - a.n()) / (a.m() - b.m());
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

int countCollisions(vector<Stone> stones, int area[]){
    int collisions = 0;
    for(int i = 0; i < stones.size(); i++){
        for(int j = i + 1; j < stones.size(); j++){
            collisions += collision(stones[i], stones[j], area);
        }
    }
    return collisions;
}


int main(){
    vector<Stone> stones = loadFile("input.txt");
    print(stones);
    int area[] = {7,27};
    int numcol = countCollisions(stones, area); 
    cout << "Number of collisions: " << numcol << endl;
    return 0;
}