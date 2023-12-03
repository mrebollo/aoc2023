/*
advent of code 2023 
day 3 part 1
sum numbers that ara adjacent to a symbol
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define ROW 140 + 2
#define COL 140 + 2

char scheme[ROW][COL];


int issymbol(char c)
{
    return !isdigit(c) && c != '.';
}


void load_scheme(const char *filename){
    ifstream file(filename);
    string line;
    int i = 0;
    while (getline(file, line))
    {   
        scheme[i][0] = '.';
        scheme[i][COL-1] = '.';
        for (int j = 0; j < line.length(); j++)
            scheme[i+1][j+1] = line[j];
        i++;
    }
    // rellena el marco alrederor del esquema
    for (int j = 0; j < COL; j++)
    {
        scheme[0][j] = '.';
        scheme[ROW-1][j] = '.';
    }
}


int is_part_number(int row, int *col) {
    int part = 0;
    //prev column
    if(issymbol(scheme[row-1][*col-1]) || issymbol(scheme[row][*col-1]) || issymbol(scheme[row+1][*col-1]))
        part = 1;
    //prev and next rows
    while(isdigit(scheme[row][*col])){
        if(issymbol(scheme[row-1][*col]) || issymbol(scheme[row+1][*col]))
            part = 1;
        (*col)++;
    }
    //next column
    if(issymbol(scheme[row-1][*col]) || issymbol(scheme[row][*col]) || issymbol(scheme[row+1][*col]))
        part = 1;
    // tengo que recorrer hasta el final para que salte el número entero
    return part;
}


int sum_from_line(int row) {
    int value, sum = 0;
    for (int j = 1; j < COL-1; j++) {
        if (isdigit(scheme[row][j])){
            value = atoi(&scheme[row][j]);    
            if(is_part_number(row, &j)){
                cout << value << endl;
                sum += value;
            }
        }
    }
    return sum;
}


int main()
{
    int total = 0;

    //load_scheme("input.txt");
    load_scheme("adventofcode.com_2023_day_3_input.txt");
    for (int i = 1; i < ROW-1; i++){
        total += sum_from_line(i);
        cout << "---" << endl;
    }

    cout << total << std::endl;
    return 0;
}