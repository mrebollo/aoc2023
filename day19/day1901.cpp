/*
advent of code day 19 part 1
process worklow sabed on set of rules
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

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
        rule *ruleset[26*26*26];
    public:
        HashTable();
        int idx(string key);
        void addrule(string label, string r);
        int process(string line);
        void print();
};


HashTable::HashTable(){
    this->size = 26*26*26;
    // add termination nodes to accept or reject
    for(int i = 0; i < size; i++)
        ruleset[i] = new rule("", "0=0", NULL, NULL);
    ruleset[idx("A")]->label = "A";
    ruleset[idx("R")]->label = "R";
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


void HashTable::addrule(string label, string r){
    int ruleid = idx(label);
    rule *cur = ruleset[ruleid];
    istringstream iss(r);
    //proceso la primera condición
    string token, cond, ift, iff;
    getline(iss, token, ',');
    istringstream issin(token);
    getline(issin, cond, ':');
    getline(issin, ift, ',');
    cur->cond = condition(cond);
    cur->iftrue = ruleset[idx(ift)];
    while(getline(iss, token, ',')){
        if(token.size() < 4) { // last false option has a label
            int leaf = idx(token);
            cur->iffalse = ruleset[leaf];
            break;
        }
        istringstream issin(token);
        getline(issin, cond, ':');
        getline(issin, ift, ',');
        int h = idx(ift);
        cur->iffalse = new rule("",cond, ruleset[h], NULL);
        cur = cur->iffalse;
    }
    ruleset[ruleid]->label = label;
}


int HashTable::process(string line) {
    //elimina los paréntesis
    istringstream iss(line.substr(1, line.size()-2));
    string token;
    int parts[128], sum = 0;
    //lee las piezas de cada categoria
    while(getline(iss, token, ',')){
        int cat = token[0];
        parts[cat] = stoi(token.substr(2));
        sum += parts[cat];
    }
    //procesa el 
    cout << line << ": " << flush;
    rule *cur = ruleset[idx("in")];
    while(cur->label != "A" && cur->label != "R"){
        cout << cur->label << " -> " << flush;
        if(cur->cond.op == '<')
            if(parts[cur->cond.cat] < cur->cond.value)
                cur  = cur->iftrue;
            else
                cur = cur->iffalse;
        else //(cur->cond.op == '>')
            if(parts[cur->cond.cat] > cur->cond.value)
                cur  = cur->iftrue;
            else
                cur = cur->iffalse;
    }
    if(cur->label == "A"){
        cout << "-> A accepted (" << sum << ")" << endl;
        return sum;
    }
    else
        cout << "-> R rejected" << endl;
    return 0;
}


void HashTable::print(){ 
    for (rule *r: ruleset) 
        if (r->label != "") {
            cout << r->label << ": ";
            while(r->iffalse){
                cout << r->cond.cat << r->cond.op << r->cond.value << " : ";
                cout << r->iftrue->label << ", "; 
                r = r->iffalse;
            }
            cout << r->label << endl;
        }
}

  
int main(){
    HashTable rules;
    fstream inputf;
    string label, newrule, line;
    //inputf.open("input.txt");
    inputf.open("adventofcode.com_2023_day_19_input.txt");
    // read rules
    while (getline(inputf, line) && line.size() > 0){
        istringstream iss(line);
        getline(iss, label, '{');
        getline(iss, newrule, '}');
        rules.addrule(label, newrule);
    }
    //read workflow (PENDING)

    int total = 0;
     while (getline(inputf, line))
        total += rules.process(line);
    inputf.close();
    cout << "Total: " << total << endl;
    //rules.print();

    return 0;
}