#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

#define TEST 1

using namespace std;

struct solution{
    int idx;
    int len;
};

inline solution max(solution a, solution b){
    return a.len > b.len ? a : b;
}


/* 
    encontrar el palíndromo más largo usando programación dinámica 
    siempre es de longitud par
*/
set<int> findvertical(string line, int i, int j){
    set<int> mirrorpos;
    int len = 0;
    if (i >= j)
        return mirrorpos;
    int begin = i, end = j;
    while(end > begin && line[begin] == line[end]){
        len += 2;
        begin++;
        end--;
    }
    if (begin > end && len > 0 && (i == 0 || j == line.size()-1))
        mirrorpos.insert(end);
    
    set<int> set1 = findvertical(line, i, j-1);
    set<int> set2 = findvertical(line, i+1, j);
    mirrorpos.insert(set1.begin(), set1.end());
    mirrorpos.insert(set2.begin(), set2.end());

    return mirrorpos;
}


/* igual que vertical, con cadenas completas */ 
set<int> findhorizontal(vector<string> row, int i, int j){
    set<int> mirrorpos;
    int len = 0;
    // si los limites estan al reves o la cadena es impar
    if ( i >= j  )
        return mirrorpos;
    int begin = i, end = j;
    while(end > begin && row[begin] == row[end]){
        len += 2;
        begin++;
        end--;
    }
    if (begin > end && len > 0 && (i == 0 || j == row.size()-1))
        mirrorpos.insert(end);
    //else 
    //    return max(findhorizontal(row, i+1, j), findhorizontal(row, i, j-1));
    set<int> set1 = findhorizontal(row, i, j-1);
    set<int> set2 = findhorizontal(row, i+1, j);
    mirrorpos.insert(set1.begin(), set1.end());
    mirrorpos.insert(set2.begin(), set2.end());

    return mirrorpos;
}


vector<string> transpose(vector<string> row){
    int nrow = row.size();
    int ncol = row[0].size();
    vector<string> col = vector<string>(ncol, string(nrow, ' '));
    for(int i = 0; i < row.size(); i++)
        for(int j = 0; j < row[i].size(); j++)
            col[j][i] = row[i][j];
    return col;
}


int countdiff(string line1, string line2){
    int i, diff = 0;
    for(i = 0; i < line1.size() && diff < 2; i++){
        if (line1[i] != line2[i])
            diff++;
    }
    return (diff == 1? diff : -1);
}


int lookformirror(vector<string> row){
    //elimina el espejo original y busca el siguiente
    set<int> orig = findhorizontal(row, 0, row.size()-1);
    for(int i = 0; i < row.size(); i++)
        for(int j = i+1; j < row.size(); j++){
            //look for lines with only one difference
            int smudge = countdiff(row[i], row[j]);
            if (smudge > 0){
                //sustituye una de las lineas para forzar la simetria
                string aux = row[i];
                row[i] = row[j];
                //busca si hay espejos en la nueva configuracion
                set<int> sol = findhorizontal(row, 0, row.size()-1);
                //elimina el espejo original (tiene que ser distinto)
                sol.erase(*orig.begin());
                //restaura la linea original
                row[i] = aux;
                if(sol.size() > 0){
                    cout << "--" << endl;
                    cout << setw(2) << i+1 << ": " << row[i] << endl;
                    cout << setw(2) << j+1 << ": " << row[j] << endl;
                    cout << "-> mirror: " << *sol.begin() + 1 << endl;
                    return *sol.begin() + 1;
                }
            }
        }
    // si no nay ninguno nuevo, devuelve el original
    // nunca deberia llegar aqui
    return 0;//orig.empty() ? 0 : *orig.begin() + 1;
}


int main() {
    fstream inputf;
    string line;

    //inputf.open("input.txt");
    inputf.open("adventofcode.com_2023_day_13_input.txt");
    vector<string> row;
    int total = 0, nlin = 1;
    while(getline(inputf, line)) {
        if(line.empty()){
            int mirrorat = lookformirror(row);
            total += mirrorat * 100;
            if(mirrorat == 0){
                mirrorat = lookformirror(transpose(row));
                total += mirrorat;
            }
            row.clear();
            nlin = 1;
            cout << "total: " << total << endl;
            cout << "---" << endl;
            continue;
        }
        // check all posible mirros per line
        row.push_back(line);
#ifdef TEST
        cout << setw(2) << nlin++ << ": " << line << endl;  
#endif
    }
    cout << "** total: " << total << endl;
    inputf.close();
    return 0;
} 