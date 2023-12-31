/*
advent of code day 12 part 1
resolver línas de nonogramas (picross)
dada una línea parcial y la cantidad de bloques
determinar cuántas combinaciones posibles hay
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

int coincidences(string nonogram, vector<string> &sol);
void generateSolution(int n, vector<int> &blocks, int i, string nonogram, vector<string> &sol);
vector<int> parseClue(string clue);
string repeat(char c, int n);
vector<string> solutions(string nonogram, string clue);
string str2regex(string str);


string repeat(char c, int n) {
    string s;
    s.reserve(n);
    while(n--) s += c;
    return s;
}


vector<int> parseClue(string clue) {
    vector<int> blocks;
    char *tok = strtok(&clue[0], ", ");
    do{
        blocks.push_back(atoi(tok));
    }while((tok = strtok(NULL, ", ")) != NULL);
    return blocks;
}


void generateSolution(int n, vector<int> &blocks, int i, string nonogram, vector<string> &sol) {
    int len = nonogram.length();
    if(nonogram.length() > n)
        return;
    if(nonogram.length() == n && i == blocks.size()) {
        cout << nonogram << endl;
        sol.push_back(nonogram);
        return;
    }
    string blk = repeat('#', blocks[i]);
    if(i < blocks.size() && nonogram.back() != '#') 
        generateSolution(n, blocks, i+i, nonogram+blk, sol);
    generateSolution(n, blocks, i, nonogram+".", sol);
}


vector<string> solutions(string nonogram, string clue) {
    vector<string> sol;
    vector<int> blocks = parseClue(clue);
    generateSolution(nonogram.length(), blocks, 0, "", sol);
    return sol;
}


string str2regex(string str) {
    string regex;
    for(char c: str) 
        switch(c) {
            case '.': regex += "\\.";break;
            case '#': regex += "#"; break;
            case '?': regex += "."; break;
        }
    return regex;
}


int coincidences(string nonogram, vector<string> &sol) {
    int arrange = 0;
    string strrule = str2regex(nonogram);
    regex rule(str2regex(nonogram));
    for(string sequence: sol){
        int match = regex_match(sequence, rule);
        arrange += match;
        if (match)
            cout << sequence << endl;
    }
    return arrange;
}


int main() {
    fstream inputf("input.txt");
    //fstream inputf("adventofcode.com_2023_day_12_input.txt");
    int total = 0;
    string line;
    while(getline(inputf, line)) {
        //obtener la línea y la pista
        istringstream iss(line);
        string nonogram, clue;
        iss >> nonogram >> clue;
        cout << nonogram << " - " << clue << endl;

        //obtener todas las soluciones posibles
        vector<string> sol = solutions(nonogram, clue);

        //contar cuantas coinciden con el template
        int arrange = coincidences(nonogram, sol);
        cout << "** arrangements: " << arrange << endl;
        total += arrange;
    }
    cout << endl << "total: " << total << endl;
    inputf.close();
    return 0;
}
