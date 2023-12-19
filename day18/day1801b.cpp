/*
Advent  of code 2023
Day 18, part 1
Dig following the path and remove interior points
Version 2: calculate area from the contour
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

inline void next(int &i, int &j, char dir, int len) {
    switch (dir) {
        case 'U': i-=len; break;
        case 'L': j-=len; break;
        case 'D': i+=len; break;
        case 'R': j+=len; break;
    }
}

int main () {
    ifstream inputf("input.txt");
    //ifstream inputf("adventofcode.com_2023_day_18_input.txt");
    vector<pair<int, int> > contour;
    string line, color;
    char dir;
    int len, i = 0, j = 0;
    long int perim = 0;
    while(getline(inputf, line)) {
        istringstream iss(line);
        iss >> dir >> len >> color;
        next(i, j, dir, len);
        cout << i << " " << j << ": " << len << endl;
        contour.push_back(make_pair(i, j));
        perim += len;
    }
    inputf.close();
/*
    for(auto p : contour) {
        cout << p.first << " " << p.second << endl;
    }
*/
    // Calculate area using trapezoid formula
    // adapted from https://stackoverflow.com/questions/64597031/how-to-get-area-inside-a-contour
    long int area = 0;
    int last = contour.size() - 1;
    for( int i = 0; i < last; i++){
        int ai = -(contour[i].first - contour[i+1].first) * (contour[i].second + contour[i+1].second) / 2;
        cout << "(" << contour[i].first << ", " << contour[i].second << ") -> ";
        cout << "(" << contour[i+1].first << ", " << contour[i+1].second << ") ";
        cout << "ai: " << ai << endl;
        area += ai;
    }
    cout << "close the loop" << endl;
    area -= (contour[last].first - contour[0].first) * (contour[last].second + contour[0].second) / 2;
    cout << "(" << contour[last].first << ", " << contour[last].second << ") -> ";
    cout << "(" << contour[0].first << ", " << contour[0].second << ") ";
    int ai = -(contour[last].first - contour[0].first) * (contour[last].second + contour[0].second) / 2;
    cout << "ai: " << ai << endl;
    cout << "Perimeter: " << perim << endl;
    cout << "Area interior: " << area << endl;
    cout << "Total area: " << area + perim << endl;

    return 0;
}