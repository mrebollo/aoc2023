/*
advent of code day 6 part 1
possible ways to supèrate distances
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int possibilities(int time, int dist){
    int wins = 0;
    for(int hold = 0; hold <= time; hold++){
        int remaining_time = time - hold;
        int travel_dist = remaining_time * hold;
        if(travel_dist > dist){
            //cout << "hold " << hold << " -> move " << travel_dist << " > dist " << dist << endl;
            wins++;
        }
    }
    return wins;
}


int main() {
    vector<int> time, dist;
    fstream inputf;
    string line;    

    inputf.open("adventofcode.com_2023_day_6_input.txt");
    //inputf.open("input.txt");

    // get times
    getline(inputf, line);
    char *tok = strtok(&line[0], ":");
    while((tok = strtok(NULL, " ")) != NULL)
        time.push_back(atoi(tok));
    // get distances
    getline(inputf, line);
    tok = strtok(&line[0], ":");
    while((tok = strtok(NULL, " ")) != NULL)
        dist.push_back(atoi(tok));

    int prod = 1;
    for(int i = 0; i < time.size(); i++){
        int wins = possibilities(time[i], dist[i]);
        prod *= wins;
        cout << "time: " << time[i] << " - dist: " << dist[i] << " - wins: " << wins << endl;
    }
    cout << "total wins: " << prod << endl;  
    return 0;
}