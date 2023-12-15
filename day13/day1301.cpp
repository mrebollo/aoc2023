#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
inline int max(int a, int b) { return (a > b)? a : b; }

/* 
    encontrar el palíndromo más largo usando programación dinámica 
    siempre es de longitud par
*/
int findvertical(string line, int i, int j){
    int mirror_at = -1;
    if ( i >= j)
        return -INT_MAX;
    if(j - i == 1)
        return i;
    if (line[i] == line[j])
        mirror_at = findvertical(line, i+1, j-1);
    else
        mirror_at = max(findvertical(line, i+1, j), findvertical(line, i, j-1));
    return mirror_at;
}

/* igual que vertical, con cadenas completas */
int findhorizontal(vector<string> row, int i, int j){
    int mirror_at = -1;
    if ( i >= j)
        return -INT_MAX;
    if(j - i == 1)
        return i;
    if (row[i] == row[j])
        mirror_at = findhorizontal(row, i+1, j-1);
    else
        mirror_at = max(findhorizontal(row, i+1, j), findhorizontal(row, i, j-1));
    return mirror_at;
}


int main() {
    fstream inputf;
    string line;

    inputf.open("input.txt");
    //inputf.open("adventofcode.com_2023_day_13_input.txt");
    int total_pred = 0;
    vector<string> row;
    while(getline(inputf, line)) {
        // busca el espejo entre filas cuando acaba el patron
        if(line.empty()){
            int center = findhorizontal(row, 0, row.size()-1);
            cout << " - hor. center: " << center << endl;
            cout << "--" << endl;
            row.clear();
            continue;
        }
        row.push_back(line);
        // busca el espejo entre columnas en cada fila
        // existe si esta en la misma posicion en todas las filas (TODO)
        int center = findvertical(line, 0, line.size()-1);
        cout << line << " - vert. center: " << center << endl;

        //TODO: calcular el valor de cada patrón y acumularlos
    }
    inputf.close();
    return 0;
} 