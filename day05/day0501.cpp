/*
advent of code day 5 part 1
calculate nearest location for seeds
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> transform(vector<int> seed, int src, int dst, int size){
    vector<int> next(seed.size());
    for(int i = 0; i < seed.size(); i++){
        int dist = seed[i] - src;
        if(dist >= 0 && dist < size)
            next[i] = dst + dist;
        else
            next[i] = seed[i];
    }
    return next;
}


int main() {
    vector<int> seed, prev;

    fstream inputf;
    string line;    
    //inputf.open("adventofcode.com_2023_day_5_input.txt");
    inputf.open("input.txt");
    // get seeds
    getline(inputf, line);
    
    char *tok = strtok(&line[0], ":");
    while((tok = strtok(NULL, " ")) != NULL)
        seed.push_back(atoi(tok));  

    while(getline(inputf, line)){
        if(line.length() == 0){
            // jumps over transform heading
            getline(inputf, line);
            cout << line << endl;
            continue;
        }
        // process next transformation  block
        int dst = atoi(strtok(&line[0], " "));
        int src = atoi(strtok(NULL, " "));
        int size = atoi(strtok(NULL, " "));
        seed = transform(seed, src, dst, size);
        for(int i = 0; i < seed.size(); i++)
            cout << seed[i] << " ";
        cout << endl;
    }
    // print result
    int min = seed[0];
    for(int i = 0; i < seed.size(); i++){
        cout << seed[i] << " ";
        if(seed[i] < min)
            min = seed[i];
    }
    cout << endl << "min: " << min << endl;
    inputf.close();
    return 0;
}