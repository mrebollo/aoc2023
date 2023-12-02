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
    string num[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    inputf.open("adventofcode.com_2023_day_1_input.txt");
    while(getline(inputf, line))
    {
        //sumar valores ascii de cada linea
        int first = 999, last = -1, fpos = 999, lpos = -1;
        for (int i = 0; i < line.length(); i++)
            if (isdigit(line[i])){
                    first = line[i] - '0'; fpos = i;
                    break;
            }
        for (int i = line.length()-1; i >= 0; i--)
            if (isdigit(line[i])){
                    last = line[i] - '0'; lpos = i;
                    break;
            }
        //cout << "** numbers " << first << " " << last;
        //cout << "** positions " << fpos << " " << lpos << endl;
        int pos;
        for (int i = 0; i < 10; i++){
            pos = line.find(num[i]);
            if (pos >= 0){
                //cout << line << ":" << num[i] << " " << pos << endl;
                if( pos < fpos){
                    first = i;
                    fpos = pos;    
                }
            }
        }
        for (int i = 0; i < 10; i++){
            pos = line.rfind(num[i]);
            if (pos >= 0){
                //cout << line << ":" << num[i] << " " << pos << endl;
                if( pos > lpos){
                    last = i;
                    lpos = pos;    
                }
            }
        }
        int totalline = first * 10 + last;
        cout << totalline << endl;
        total += totalline;
    }
    cout << total << endl;
    //cerrar fichero
    inputf.close();
    return 0;
}