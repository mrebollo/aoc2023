/*
Advent  of code 2023
Day 18, part 2
Dig following the path and remove interior points
instructions in hexadecimal code
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

inline void next(int &i, int &j, int dir, int len) {
    switch (dir) {
        case '3': i-=len; break;
        case '2': j-=len; break;
        case '1': i+=len; break;
        case '0': j+=len; break;
    }
}

void extract(string color, char &dir, int &len){
    size_t pos = color.find("#");
    istringstream iss(color.substr(pos+1, 5));
    iss >> hex >> len;
    dir = color[7];
    cout << color << " = " << dir << " " << len << endl;
}

int main () {
    //ifstream inputf("sample.txt"); // AREA interna 44
    ifstream inputf("input.txt"); // AREA 952408144115
    //ifstream inputf("adventofcode.com_2023_day_18_input.txt");
    vector<pair<int, int> > contour;
    string line, color;
    int len, i = 0, j = 0;
    char dir;
    long int perim = 0;
    while(getline(inputf, line)) {
        istringstream iss(line);
        iss >> dir;
        iss >> len;
        iss >> color;
        extract(color, dir, len);
        next(i, j, dir, len);
        contour.push_back(make_pair(i, j));
        perim += len;
    }
    inputf.close();
    cout << "Perimeter: " << perim << endl;
    
    for(auto p : contour) {
        cout << p.first << " " << p.second << endl;
    }

    long int area = 0;
    int last = contour.size() - 1;
    for( int i = 0; i < last; i++){
        area -= (contour[i].first - contour[i+1].first) * (contour[i].second + contour[i+1].second) / 2;
    }
    area -= (contour[i].first - contour[last].first) * (contour[i].second + contour[last].second) / 2;

    cout << "Area interior: " << area << endl;
    cout << "Total area: " << area + perim << endl;
    return 0;
}