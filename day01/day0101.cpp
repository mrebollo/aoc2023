/*
advent of code day 1
sum asscii values of input file lines
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    //abrir fichero input.txt
    ifstream inputf;

    //leer linea a linea
    int total = 0;
    string line; 
    inputf.open("adventofcode.com_2023_day_1_input.txt");
    while(getline(inputf, line))
    {
        //sumar valores ascii de cada linea
        int first = -1, last = -1;
        for (char c: line){ 
            if (isdigit(c)){
                last = c - '0';
                if (first == -1)
                    first = c - '0';
            }
        }
        int totalline = first * 10 + last;
        //cout << totalline << endl;
        total += totalline;
    }
    cout << total << endl;
    //cerrar fichero
    inputf.close();
    return 0;
}