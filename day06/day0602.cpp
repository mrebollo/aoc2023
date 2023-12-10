/*
advent of code day 6 part 2
possible ways to superate distances
read line as an unique integer
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

double possibilities(double time, double dist){
    double wins = 0;
    for(double hold = 0; hold <= time; hold++){
        double remaining_time = time - hold;
        double travel_dist = remaining_time * hold;
        if(travel_dist > dist){
            //cout << "hold " << hold << " -> move " << travel_dist << " > dist " << dist << endl;
            wins++;
        }
    }
    return wins;
}


double extract_value(fstream &inputf){
    string line;
    double value;
    getline(inputf, line);
    //remove label
    line.erase(0, line.find(':')+1);
    //remove white spaces
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    value = atof(&line[0]);
    return value;
}


int main() {
    double time, dist;
    fstream inputf;
    string line;    

    inputf.open("adventofcode.com_2023_day_6_input.txt");
    //inputf.open("input.txt");
    time = extract_value(inputf);
    dist = extract_value(inputf);
    inputf.close();
    
    double wins = possibilities(time, dist);
    cout << fixed << "total wins: " << wins << endl;  
    return 0;
}