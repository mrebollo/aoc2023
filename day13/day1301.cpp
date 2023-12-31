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
solution findhorizontal(vector<string> row, int i, int j){
    int len = 0;
    // si los limites estan al reves o la cadena es impar
    if ( i >= j  )
        return {-1, 0};
    int begin = i, end = j;
    while(end > begin && row[begin] == row[end]){
        len += 2;
        begin++;
        end--;
    }
    if (begin > end && len > 0 && (i == 0 || j == row.size()-1))
        return {end, len};
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
    set<int> mirrorpos;
    int total = 0, nlin = 1;
    cout << "    |    |    |    |" << endl;
    while(getline(inputf, line)) {
        if(line.empty()){
            if(mirrorpos.size() == 1){
                total += *mirrorpos.begin() + 1;
                cout << "vertical mirror at: " << *mirrorpos.begin() + 1 ;
                cout << ",\t total : " << total << endl;
            }
            else{
                solution hpos = findhorizontal(row, 0, row.size()-1);
                if(hpos.idx >= 0){
                    total += 100 * (hpos.idx  + 1);
                    cout << "horizontal mirror at: " << hpos.idx  + 1;
                    cout << " x 100, total : " << total << endl;
                }
            }
            row.clear();
            mirrorpos.clear();
            nlin = 1;
            cout << "---" << endl;
            cout << "    |    |    |    |" << endl;
            continue;
        }
        // check all posible mirros per line
        row.push_back(line);
        set<int> vpos = findvertical(line, 0, line.size()-1);
        // intersection with previous candidates
        if(row.size() == 1)
            mirrorpos.insert(vpos.begin(), vpos.end());
        else {
            set<int> tmp;
            set_intersection(mirrorpos.begin(), mirrorpos.end(), vpos.begin(), vpos.end(), inserter(tmp, tmp.begin()));
            mirrorpos = tmp;
        }
#ifdef TEST
        cout << setw(2) << nlin++ << ": " << line << " - center: ";
        for(auto it:vpos)
            cout << it << " ";
        cout << endl;   
#endif
    }
    cout << "** total: " << total << endl;
    inputf.close();
    return 0;
} 