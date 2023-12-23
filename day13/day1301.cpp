#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

//#define TEST 1

using namespace std;
struct solution {
    int len, idx;
};

inline solution max(solution a, solution b) { return (a.len > b.len)? a : b; }


/* 
    encontrar el palíndromo más largo usando programación dinámica 
    siempre es de longitud par
*/
solution findvertical(string line, int i, int j){
    int len = 0;
    if ( i >= j)
        return {0, -1};
    int begin = i, end = j;
    while(end > begin && line[begin++] == line[end--])
        len += 2;
    if (begin > end)
        return {len, end};
    else 
        return max(findvertical(line, i+1, j), findvertical(line, i, j-1));
   
}


/* igual que vertical, con cadenas completas */ 
solution findhorizontal(vector<string> row, int i, int j){
    int len = 0;
    if ( i >= j)
        return {0, -1};
    int begin = i, end = j;
    while(end > begin && row[begin++] == row[end--])
        len += 2;
    if (begin > end)
        return {len, end};
    else 
        return max(findhorizontal(row, i+1, j), findhorizontal(row, i, j-1));
}


int main() {
    fstream inputf;
    string line;

    //inputf.open("input.txt");
    inputf.open("adventofcode.com_2023_day_13_input.txt");
    int total_pred = 0;
    vector<string> row;
    solution reflexions;
    set<int> mirrorpos;
    int total = 0;
    while(getline(inputf, line)) {
        
        // 2. busca el espejo entre filas cuando acaba el patron
        if(line.empty()){
            if(mirrorpos.size() == 1){
                total += reflexions.idx + 1;
#ifdef TEST
                cout << "vertical mirror at: " << reflexions.idx + 1 << endl;
#else  
                cout << reflexions.idx + 1 << ",\t total : " << total << endl;
#endif
            }
            else{
                reflexions = findhorizontal(row, 0, row.size()-1);
                total += 100 * (reflexions.idx + 1);
#ifdef TEST
                cout << "horizontal mirror at: " << reflexions.idx + 1 << endl;
                cout << "size: " << reflexions.len << endl;
#else   
                cout << reflexions.idx + 1 << " x 100, total : " << total << endl;
#endif
            }
#ifdef TEST
            cout << "--" << endl;
#endif

            row.clear();
            mirrorpos.clear();
            continue;
        }
        row.push_back(line);
        // 1. busca el espejo entre columnas en cada fila
        // existe si esta en la misma posicion en todas las filas
        // insertar el centro en un conjunto: 
        // si al final solo tiene un elementop, hay espejo
        reflexions = findvertical(line, 0, line.size()-1);
        mirrorpos.insert(reflexions.idx);
#ifdef TEST
        cout << line;
        cout << " - vertical size: " << reflexions.len;
        cout << " - center: " << reflexions.idx << endl;
#endif
    }
    cout << "** total: " << total << endl;
    inputf.close();
    return 0;
} 