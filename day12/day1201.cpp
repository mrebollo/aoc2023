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

using namespace std;

vector<string> solutions(string nonogram, string clue) {
    vector<string> sol;
    //TODO obtener todas las soluciones posibles
    return sol;
}


int coincidences(string nonogram, vector<string> sol) {
    int arrange = 0;
    //TODO contar las coincidencias del nonograma con las soluciones
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

        //obtener todas las soluciones posibles
        vector<string> sol = solutions(nonogram, clue);

        //contar cuantas coinciden con el template
        int arrange = coincidences(nonogram, sol);
        cout << arrange << " arrangements: " << nonogram << " - " << clue << endl;
        total += arrange;
    }
    cout << "total: " << total << endl;
    inputf.close();
    return 0;
}