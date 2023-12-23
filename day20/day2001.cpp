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
    vector<string> in;
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
        void pressButton();
        
    private:
        int idx(string label);
        string& leftTrim(string& str);
                void addGate(gate g);
        gate* getGate(string label);
        void doBroadcast(gate *g, pulse p);
        void doFlip(gate *g, pulse p);
        void doConj(gate *g, pulse p);
        void processQueue();
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
    int i = idx(g.in[0]);
    gates[i] = g;
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
        string aux;
        getline(iss, aux , ' ');

        g.type = aux[0];
        if (g.type != BROADCAST)
            aux.erase(0,1);
        g.in.push_back(aux);
        getline(iss, aux, ' ');
        while(getline(iss, aux, ',')){
            g.out.push_back(leftTrim(aux));
        }
        addGate(g);
    }
}

void Circuit::printCircuit(){
    for(int i = 0; i < num_gates; i++){
        if(gates[i].in.size() == 0)
            continue;
        cout << gates[i].type << gates[i].in[0] << " -> ";
        for(int j = 0; j < gates[i].out.size(); j++){
            cout << gates[i].out[j] << " ";
        }
        cout << endl;
    }
}

void Circuit::sendPulse(pulse p){
    q.push(p);
    cout << p.from << " " << totext(p.signal) << " -> " << p.to << endl;
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
    // memory: update state to last received signal
    g->state = p.signal;
    bool memory = g->state;
    for(int i = 0; i < g->out.size(); i++)
        sendPulse(pulse(!memory, p.to, g->out[i]));
}


void Circuit::processQueue() {
    while(!q.empty()){
        pulse p = q.front();
        q.pop();
        gate *g = getGate(p.to);
        // refactor: switch(g.type) -> g.do(p) y herencia de gates
        switch(g->type){
            case BROADCAST: doBroadcast(g, p); break;
            case FLIP: doFlip(g, p); break;
            case CONJ:  doConj(g, p); break;
        }
    }
}


void Circuit::pressButton() {
    cout << "button -low -> broadcaster" << endl;
    // no tengo ganas de implementar el boton por separado
    q.push(pulse(low, "broadcaster", "broadcaster"));
    processQueue();
}

int main(){
    Circuit c;
    c.loadCircuit("input.txt");
    //c.loadCircuit("input2.txt");
    //c.loadCircuit("adventofcode.com_2023_day_20_input.txt");
    c.printCircuit();
    c.pressButton();
    return 0;
}