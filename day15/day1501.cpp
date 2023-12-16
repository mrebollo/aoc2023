/*
advent of code day 15 part 1
hash function for lenses
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int myhash(string s){
    int h = 0;
    for(int i = 0; i < s.size(); i++)
        h = (h + s[i]) * 17 % 256;
    return h;
}


int main(){
    fstream inputf;
    string token;
    //inputf.open("input.txt");
    inputf.open("adventofcode.com_2023_day_15_input.txt");
    int total = 0;
    while (getline(inputf, token, ','))
    {
        int hval = myhash(token);
        total += hval;
        cout << "token: " << token << " - hash: " << hval << endl;
    }
    cout << "total: " << total << endl;
    return 0;
}