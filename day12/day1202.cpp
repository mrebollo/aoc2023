/*
advent of code day 12 part 1
resolver línas de nonogramas (picross)
dada una línea parcial y la cantidad de bloques
determinar cuántas combinaciones posibles hay
expandir 5 copias separadas por un ?
partir de la version (b) optimizada
¿se puede calcular extrapolando? probar con dos copias solo
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

inline int sum(vector<string> v, int from){
    int s = 0; 
    for(int i = from; i < v.size(); i++) s+=v[i].length(); 
    return s;
}

void expand(string &nonogram, string &clue, int n) {
    while(--n > 0) {
        nonogram += "?" + nonogram;
        clue += "," + clue;
    }
}
void generateSolution(string model, vector<string> &blocks, int i, string nonogram, vector<string> &sol);
vector<string> parseClue(string clue);
string repeat(char c, int n);
void solutions(string nonogram, string clue, vector<string> &sol);
string str2regex(string str);


string repeat(char c, int n) {
    string s;
    s.reserve(n);
    while(n--) s += c;
    return s;
}


vector<string> parseClue(string clue) {
    vector<string> blocks;
    string blk;
    char *tok = strtok(&clue[0], ", ");
    do{
        blk = repeat('#', atoi(tok));
        blocks.push_back(blk);
    }while((tok = strtok(NULL, ", ")) != NULL);
    return blocks;
}


void generateSolution(string model, vector<string> &blocks, int i, string nonogram, vector<string> &sol) {
    int n = nonogram.length();
    int pending = sum(blocks,i) + blocks.size() - i - 1;
    // utiliza una expresion regular para validar la solución parcial 
    regex rule(str2regex(model.substr(0, n)));
    if(regex_match(nonogram, rule) == 0 || n + pending > model.length())
        return;
    if( n == model.length() && i == blocks.size()){
        //cout << nonogram << endl;
        sol.push_back(nonogram);
        return;
    }
    if(i < blocks.size() && nonogram.back() != '#' && model[n] != '.')
        generateSolution(model, blocks, i+1, nonogram+blocks[i], sol);
    if(model[n] != '#')
        generateSolution(model, blocks, i, nonogram+".", sol);
}


void solutions(string nonogram, string clue, vector<string> &sol) {
    vector<string> blocks = parseClue(clue);
    sol.clear();
    generateSolution(nonogram, blocks, 0, "", sol);
}


string str2regex(string str) {
    string regex;
    // ejemplo: ???.### -> \.\.\..### variante [.#][.#][.#].###
    // alternativa: usar regex_replace()
    for(char c: str) 
        switch(c) {
            case '.': regex += "\\.";break;
            case '#': regex += "#"; break;
            case '?': regex += "."; break;
        }
    return regex;
}

vector<int> process(string filename, int prod) {
    vector<int> arr;
    vector<string> sol;
    string line;
    ifstream inputf(filename);
    while(getline(inputf, line)) {
        //obtener la línea y la pista
        istringstream iss(line);
        string nonogram, clue;
        iss >> nonogram >> clue;
        cout << nonogram << " - " << clue << endl;
        expand(nonogram, clue, prod);
        //obtener todas las soluciones posibles
        solutions(nonogram, clue, sol);
        cout << "** arrangements: " << sol.size() << endl;
        arr.push_back(sol.size());
    }
    return arr;
}

int main() {
    //string filename = "input.txt";
    string filename = "adventofcode.com_2023_day_12_input.txt";
    unsigned long long total = 0;
    vector<int> arr = process(filename, 1);
    vector<int> arr2 = process(filename, 2);
    for(int i = 0; i < arr.size(); i++) {
        cout << arr[i] << "\t" << arr2[i];
        int factor = arr2[i] / arr[i];
        cout << "\t x" << factor;
        unsigned long long est = arr[i] * factor * factor * factor * factor;
        cout << setprecision(30) << "\t -> (5) " << est;
        total += est;
        cout << setprecision(30) << "\t TOTAL: " << total << endl;
    }
    cout << setprecision(30) << "total: " << total << endl;
    return 0;
}
