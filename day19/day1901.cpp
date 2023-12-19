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
 
inline string tolower(string s){
    for(auto& c: s) c = tolower(c);
    return s;
}

class HashTable{
    private:
        int size;
        rule* ruleset[26*26*26];
    public:
        HashTable();
        int hash(string key);
        void insert(string label, string r);
        void print();
};



HashTable::HashTable(){
    this->size = 26*26*26;
}

int HashTable::hash(string key){
    int x = 26;
    int h = (key[0]-'a') + (key[1]-'a') * x;
    if(key.size() > 2) h += (key[2]-'a') * x * x;
    return h;
}

void HashTable::insert(string label, string r){
    int ruleid = hash(label);
    istringstream iss(r);
    string token, cond, ift, iff;
    while(getline(iss, token, ',')){
        node->cond = condition(token);
        getline(iss, token, ':');      
        node->iftrue = &ruleset[hash(token)];
    }
    node->iffalse = &ruleset[hash(tolower(token))];
}

void HashTable::print(){ 
    for (rule r: ruleset) 
        if (r.label != "") 
            cout << r.label << " -> " << r.iftrue->label << " " << r.iffalse->label << endl;
}

  
int main(){
    HashTable rules;
    fstream inputf;
    string label, newrule;
    inputf.open("input.txt");
    // read rules
    while (getline(inputf, label, '{')){
        getline(inputf, newrule, '}');
        rules.insert(label, newrule);
    }
    //read workflow
    inputf.close();

    return 0;
}