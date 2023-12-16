/*
advent of code day 15 part 2
hash table for lenses
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
 
class HashTable{
    private:
        struct node{
            string key;
            int focal;
            node *next;
            node(string key, node *next); //constructor
        };
        int size;
        node **table;
    public:
        HashTable(int size);
        ~HashTable();
        int hash(string key);
        void insert(string key);
        void remove(string key, int hval);
        void print();
        int focuspower();


};

HashTable::node::node(string key, node *next){
    if(key.back() == '-'){
        key.pop_back(); //-
        this->key = key;
        this->focal = -1;
    }
    else{
        this->focal = key.back() - '0';
        key.pop_back(); //number
        key.pop_back(); //=
        this->key = key;
    }
    this->next = next;
}


HashTable::HashTable(int size){
    this->size = size;
    table = new node*[size];
    for(int i = 0; i < size; i++)
        table[i] = NULL;
}

HashTable::~HashTable(){
    for(int i = 0; i < size; i++){
        node *p = table[i];
        while(p != NULL){
            node *prev = p;
            p = p->next;
            delete prev;
        }
    }
    delete[] table;
}

int HashTable::hash(string key){
    int h = 0;
    for(int i = 0; key[i] != '=' && key[i] != '-'; i++)
        h = (h + key[i]) * 17 % size;
    return h;
}

// TODO falla cuando la primera lente de la celda es '-'
void HashTable::insert(string key){
    int hval = hash(key);
    node *n = new node(key,NULL);
    if(table[hval] == NULL)
        table[hval] = n;
    else if (n->focal == -1){
        //la marca '-' elimina la lente (-1 en focal)
        remove(n->key, hval);
        return;
    }
    else{
        node *p = table[hval];
        while(p->next != NULL){
            // sustituye el valor focal si ya existe la lente
            if(p->key == n->key){
                p->focal = n->focal;
                return;
            }
            p = p->next;
        }
        // si no existe la lente, la agrega al final
        p->next = n;
    }
}

// TODO falla cuando es la primera lente de la celda
void HashTable::remove(string key, int hval){
    node *p = table[hval];
    node *prev = NULL;
    while(p != NULL && p->key != key){
        prev = p;
        p = p->next;
    }
    if(p == NULL)
        return;
    if(prev == NULL)
        table[hval] = p->next;
    else
        prev->next = p->next;
    delete p;
}

void HashTable::print(){
    for(int i = 0; i < size; i++){
        node *p = table[i];
        //evita imprimir celdas vacias
        if(table[i] != NULL){
            cout << "Box " << i << ": ";
            do{
                cout << "[" << p->key << " " << p->focal << "] ";
                p = p->next;
            }while(p != NULL);
            cout << endl;
        }
    }
}

int HashTable::focuspower(){
    int box, slot, power = 0;
    for(int i = 0; i < size; i++){
        box = i+1;
        slot = 1;
        node *p = table[i];
        if(table[i] != NULL){
            do{
                power += box * slot * p->focal;
                printf("%s: %d (box) * %d (slot) * %d (focal) = %d\n", p->key.c_str(), box, slot, p->focal, box * slot * p->focal);
                p = p->next;
                slot++;
            }while(p != NULL);
        }
    }
    return power;
}

int main(){
    HashTable box(256);
    fstream inputf;
    string token;
    //inputf.open("input.txt");
    inputf.open("adventofcode.com_2023_day_15_input.txt");
    int total = 0;
    while (getline(inputf, token, ','))
    {
        box.insert(token);
    }
    box.print();
    int power = box.focuspower();
    cout << "focus power: " << power << endl;
    return 0;
}