/*
advent of code day 19 part 1
process worklow sabed on set of rules
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct condition{
    char cat;
    char op;
    int value;
    condition(){
        cat = ' ';
        op = ' ';
        value = 0;
    }
    condition(string s){
        cat = s[0];
        op = s[1];
        value = stoi(s.substr(2));
    }
};

struct rule{
    string label;
    condition cond;
    rule *iftrue;
    rule *iffalse;
    rule(){
        label = "";
        cond = condition();
        iftrue = NULL;
        iffalse = NULL;
    }
    rule(string label, string cond, rule *ift, rule *iff){
        this->label = label;
        this->cond = condition(cond);
        iftrue = ift;
        iffalse = iff;
    }
};

struct workflow{
    int x,w,a,s;
};
 
inline void str_tolower(string &s){
    for(int i = 0; i < s.size(); i++)
        s[i] = tolower(s[i]);
}

class HashTable{
    private:
        int size;
        rule* ruleset[26*26*26];
    public:
        HashTable();
        int idx(string key);
        void process(string label, string r);
        rule* addrule(istringstream *iss);
        void print();
};



HashTable::HashTable(){
    this->size = 26*26*26;
    // add termination nodes to accept or reject
    ruleset[idx("A")] = new rule("A", "0=0", NULL, NULL);
    ruleset[idx("R")] = new rule("R", "0=0", NULL, NULL);
}

int HashTable::idx(string key){
    int x = 1;
    str_tolower(key);
    int h = (key[0]-'a');
    for(int i = 1; i < key.size(); i++){
        x *= 26;
        h += (key[i]-'a') * x;
    }
    return h;
}


rule* HashTable::addrule(istringstream *iss){
    string token, cond, ift;
    rule *iftrue, *iffalse;
    getline(*iss, token, ',');
    if(token.size() < 4) { // last false option has a label
        int leaf = idx(token);
        return (rule*)&ruleset[leaf];
    }
    istringstream issin(token);
    getline(issin, cond, ':');
    getline(issin, ift, ',');
    int h = idx(ift);
    iftrue = (rule*)&ruleset[h];
    iffalse = addrule(iss);
    return new rule("", cond, iftrue, iffalse);
}

void HashTable::process(string label, string r){
    int ruleid = idx(label);
    istringstream iss(r);
    ruleset[ruleid] = addrule(&iss);
    ruleset[ruleid]->label = label;
}

void HashTable::print(){ 
    for (rule* r: ruleset) 
        if (r != NULL) {
            cout << r->label << " : ";
            cout << r->cond.cat << r->cond.op << r->cond.value << " -> ";
            if(r->iftrue && r->iffalse)    
                cout << r->iftrue->label << " - " << r->iffalse->label << endl;
            else
                cout << endl;
        }
}

  
int main(){
    HashTable rules;
    fstream inputf;
    string label, newrule;
    inputf.open("input.txt");
    // read rules
    while (getline(inputf, label, '{') && label != "\n"){
        getline(inputf, newrule, '}');
        rules.process(label, newrule);
        getline(inputf, label, '\n');
    }
    //read workflow (PENDING)
    inputf.close();
    rules.print();

    return 0;
}