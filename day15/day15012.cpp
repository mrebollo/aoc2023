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
        //TODO: incluir la focal length
        struct node{
            string key;
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
        void print();


};

//TODO modificar para incluir focal length
HashTable::node::node(string key, node *next){
    this->key = key;
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

//TODO separar lens label y focal length
int HashTable::hash(string key){
    int h = 0;
    for(int i = 0; key[i] != '=' && key[i] != '-'; i++)
        h = (h + key[i]) * 17 % size;
    return h;
}

//TODO identificar operacion: 
// - para eliminar lens que exista
// = para añadir lens o modificar focal length (si ya existe)
void HashTable::insert(string key){
    int hval = hash(key);
    node *n = new node(key,NULL);
    if(table[hval] == NULL)
        table[hval] = n;
    else{
        node *p = table[hval];
        while(p->next != NULL)
            p = p->next;
        p->next = n;
    }
}

void HashTable::print(){
    for(int i = 0; i < size; i++){
        node *p = table[i];
        //evita imprimir celdas vacias
        if(table[i] != NULL){
            cout << i << ": ";
            do{
                cout << p->key << " ";
                p = p->next;
            }while(p != NULL);
            cout << endl;
        }
    }
}


int main(){
    HashTable box(256);
    fstream inputf;
    string token;
    inputf.open("input.txt");
    //inputf.open("adventofcode.com_2023_day_15_input.txt");
    int total = 0;
    while (getline(inputf, token, ','))
    {
        box.insert(token);
    }
    box.print();
    return 0;
}