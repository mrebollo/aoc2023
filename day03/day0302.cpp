/*
advent of code 2023 
day 3 part 1
sum numbers that ara adjacent to a symbol
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define ROW 140 + 2 //12
#define COL 140 + 2 //12

char scheme[ROW][COL];
int prod[ROW][COL];
int is_gear[ROW][COL];


int isgear(char c)
{
    return c == '*';
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


void check_gear_part(int row, int *col, int value) {
    string sval = to_string(value);
    int len = sval.length();
    for( int i = row-1; i <=row+1; i++){
        for (int j = *col-1; j <= *col+len; j++){
            if (isgear(scheme[i][j])){
                is_gear[i][j]++;
                if(is_gear[i][j] < 3)
                    prod[i][j] *= value;
                *col += len; // esto es muy chapucero
                return;
            }
        }
    }
    *col += len;
}


void process_line(int row) {
    for (int j = 1; j < COL-1; j++) {
        if (isdigit(scheme[row][j])) {
            int value = atoi(&scheme[row][j]);    
            check_gear_part(row, &j, value);   
        }
    }
}


int main()
{
    int total = 0;
    // init product matrix to ones
    for (auto &row: prod)
        for (auto &pitem: row)
            pitem = 1;

    //load_scheme("input.txt");
    load_scheme("adventofcode.com_2023_day_3_input.txt");
    for (int i = 1; i < ROW-1; i++){
        process_line(i);
    }

    // retrieve products from gears
    for (int i = 1; i < ROW-1; i++){
        for(int j = 1; j < COL-1; j++){
            if (is_gear[i][j] == 2){
                total += prod[i][j];
            }
        }
    }
    cout << "sum of ratios: " << total << std::endl;
    return 0;
}