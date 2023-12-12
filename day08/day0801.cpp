#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
    string label;
    node* left;
    node* right;
};
node nodelist[26*26*26];

int idx(string s){
    int x = 26;
    return (s[0]-'A') * x * x + (s[1]-'A') * x + (s[2]-'A');
}


void insert(string lab, string l, string r) {
    // mira si el nodo ya existe
    int i = idx(lab);
    nodelist[i].label = lab;
    nodelist[i].left = &nodelist[idx(l)];
    nodelist[i].right = &nodelist[idx(r)];
    nodelist[i].left->label = l;
    nodelist[i].right->label = r;
}


void print_graph() {
    int n = 26*26*26;
    for (int i = 0; i < n; i++) {
        if (nodelist[i].label != "") {
            cout << nodelist[i].label << " -> " << nodelist[i].left->label << " " << nodelist[i].right->label << endl;
        }
    }
}


int findZZZ(string sequence) {
    int n = 26*26*26;
    string label = "AAA";
    cout << "Sequence: " << label << " ";
    int i = 0,steps = 0;
    while (label != "ZZZ") {
        if (sequence[i] == 'L') {
            label = nodelist[idx(label)].left->label;
        } else {
            label = nodelist[idx(label)].right->label;
        }
        cout << label << " ";
        i = (i+1) % sequence.size();
        steps++;
    }
    cout << endl;
    return steps;
}


int main() {
    fstream inputf;
    string line;

    inputf.open("adventofcode.com_2023_day_8_input.txt");
    //inputf.open("input2.txt");
    string sequence;
    getline(inputf, sequence);
    //blank line
    getline(inputf, line);
    // load graph
    while (getline(inputf, line)){
        char *label = strtok(&line[0], " ");
        char *left = strtok(NULL, "(");
        left = strtok(NULL, ", ");
        char *right = strtok(NULL, " ");
        right[3] = '\0';
        insert(label, left, right);
    }
    inputf.close();
    print_graph();
    // cover graph
    int steps = findZZZ(sequence);
    cout << "Steps: " << steps << endl;
    return 0;
}
