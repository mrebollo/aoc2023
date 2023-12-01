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
        for (int i = 0; i < line.length(); i++)
            if (isdigit(line[i])){
                    first = line[i] - '0';
                    break;
            }
        for (int i = line.length()-1; i >= 0; i--)
            if (isdigit(line[i])){
                    last = line[i] - '0';
                    break;
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