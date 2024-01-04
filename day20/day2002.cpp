/*
    adventofcode.com/2023/day/20
    --- Day 20: Firewall Rules ---
    Part 2
    What is the fewest number of button presses 
    required to deliver a single low pulse to the module named rx?
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

#define BROADCAST 'b'
#define FLIP '%'
#define CONJ '&'
#define low false
#define high true

inline string totext(bool signal) {return signal ? "-high" : "-low";}

struct gate{
    string label;
    vector<string> in;
    vector<bool> inmem;
    vector<string> out;
    char type;
    bool state; // false = low, true = high
};

struct pulse{
    bool signal;
    string from, to;
    pulse(bool signal, string from, string to): signal(signal), from(from), to(to) {}
};

class Circuit{
    private:
        vector<gate> gates;
        size_t num_gates;
        queue<pulse> q;
    public:
        Circuit();
        void loadCircuit(string filename);
        void printCircuit();
        bool pressAndFound(string label);
        
    private:
        int idx(string label);
        string& leftTrim(string& str);
        void addGate(gate g);
        gate* getGate(string label);
        void doBroadcast(gate *g, pulse p);
        void doFlip(gate *g, pulse p);
        void doConj(gate *g, pulse p);
        bool lowPulseSent(string label);
        void sendPulse(pulse p);
};

Circuit::Circuit(){
    num_gates = 26*26 + 26;
    gates.resize(num_gates);
}

int Circuit::idx(string label){
    if (label == "broadcaster")
        return 0;
    int id = label[0] - 'a' + 1;
    if (label.size() == 2)
        id += (label[1] - 'a')*26 + 1;
    return id;
}

string& Circuit::leftTrim(string& str) {
  str.erase(0, str.find_first_not_of(' '));
  return str;
}

void Circuit::addGate(gate g){
    int i = idx(g.label);
    //copiarlo para no machacar las estradas (in)
    gates[i].label = g.label;
    gates[i].type = g.type;
    gates[i].out = g.out;

}

gate* Circuit::getGate(string label){
    return &gates[idx(label)];
}   

void Circuit::loadCircuit(string filename){
    ifstream file(filename);
    string line;
    while(getline(file, line)){
        istringstream iss(line);
        gate g;
        getline(iss, g.label , ' ');
        g.type= g.label[0];
        if (g.type != BROADCAST)
            g.label.erase(0,1);
        string aux;
        getline(iss, aux, ' ');
        while(getline(iss, aux, ',')){
            g.out.push_back(leftTrim(aux));
            // add input to output gate (just for conj, unused for rest)
            getGate(aux)->in.push_back(g.label);
            getGate(aux)->inmem.push_back(low);
        }
        addGate(g);
    }
}

void Circuit::printCircuit(){
    for(int i = 0; i < num_gates; i++){
        if(gates[i].label == "")
            continue;    
        if(gates[i].type == CONJ){
            for(int j = 0; j < gates[i].inmem.size(); j++)
                cout << gates[i].in[j] << " ";
            cout << "-> ";
        }
        cout << gates[i].type << gates[i].label << " -> ";
        for(int j = 0; j < gates[i].out.size(); j++){
            cout << gates[i].out[j] << " ";
        }
        
        cout << endl;
    }
}

void Circuit::sendPulse(pulse p){
    q.push(p);
    //cout << p.from << " " << totext(p.signal) << " -> " << p.to << endl;
}

void Circuit::doBroadcast(gate *g, pulse p){
    for(int i = 0; i < g->out.size(); i++){
        sendPulse(pulse(p.signal, p.to, g->out[i]));
    }

}

void Circuit::doFlip(gate *g, pulse p){
    // if high pulse do nothing
    if(p.signal == high)
        return;
    // if low pulse, flip state and send it to all outputs
    g->state = !g->state;
    for(int i = 0; i < g->out.size(); i++)
        sendPulse(pulse(g->state, p.to, g->out[i]));
}

void Circuit::doConj(gate *g, pulse p){
    // busca el indice de la entrada (sacarlo a una función)
    int inid;
    for(inid = 0; inid < g->in.size(); inid++)
        if(g->in[inid] == p.from)
            break;
    g->inmem[inid] = p.signal;
    g->state = low;
    for(int i = 0; i < g->inmem.size(); i++)   
        if(g->inmem[i] == low){
            g->state = high;
            break;
        }
    for(int i = 0; i < g->out.size(); i++)
        sendPulse(pulse(g->state, p.to, g->out[i]));
}


bool Circuit::lowPulseSent(string label){
    while(!q.empty()){
        pulse p = q.front();
        if(p.signal == low && p.to == label)
            return true;
        q.pop();
        gate *g = getGate(p.to);
        // refactor: switch(g.type) -> g.do(p) y herencia de gates
        switch(g->type){
            case BROADCAST: doBroadcast(g, p); break;
            case FLIP: doFlip(g, p); break;
            case CONJ:  doConj(g, p); break;
        }
    }
    return false;
}


bool Circuit::pressAndFound(string label) {
    //cout << "button -low -> broadcaster" << endl;
    // no tengo ganas de implementar el boton por separado
    q.push(pulse(low, "broadcaster", "broadcaster"));
    return lowPulseSent(label);
    //cout << "** low pulses: " << pulses.first << " - high pulses: " << pulses.second << endl;
}


pair<int,int> operator+(const pair<int,int> &a, const pair<int,int> &b) {   
    return make_pair(a.first + b.first, a.second + b.second);                                    
} 


int main(){
    Circuit c;
    pair<int, int> pulses, total=make_pair(0,0);
    //c.loadCircuit("input.txt");
    //c.loadCircuit("input2.txt");
    c.loadCircuit("adventofcode.com_2023_day_20_input.txt");
    c.printCircuit();
    int pressed = 1;
    while(!c.pressAndFound("zp")){
        pressed++;
        if(pressed % 1000 == 0)
            cout << "*" << flush;
    }
    cout << endl << "button pressed " << pressed << " times" << endl;
    return 0;
}