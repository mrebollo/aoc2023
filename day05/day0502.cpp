/*
advent of code day 5 part 1
calculate nearest location for seeds
*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void transform(list<double> &seed, list<double> &next, double src, double dst, double size){
    auto it = seed.begin();
    while(it != seed.end()){
        double dist = *it - src;
        if(dist >= 0 && dist < size){
            next.push_back(dst + dist);
            auto prev = it++;
            seed.erase(prev);
        }
        else
            it++;
    }
}


int main() {
    list<double> seed, next;

    fstream inputf;
    string line;    
    inputf.open("adventofcode.com_2023_day_5_input.txt");
    //inputf.open("input.txt");
    // get seeds
    getline(inputf, line);
    
    char *tok = strtok(&line[0], ":");
    while((tok = strtok(NULL, " ")) != NULL)
        seed.push_back(atof(tok));  

    while(getline(inputf, line)){
        if(line.length() == 0){
            // jumps over transform heading
            getline(inputf, line);
            cout << line << endl;
            // move to seed the updated positions
            for(auto it = next.begin(); it != next.end(); it++)
                seed.push_back(*it);
            next.clear();
            continue;
        }
        // process next transformation  block
        double dst = atof(strtok(&line[0], " "));
        double src = atof(strtok(NULL, " "));
        double size = atol(strtok(NULL, " "));
        transform(seed, next, src, dst, size);
/*
        for(auto it = seed.begin(); it != seed.end(); it++)
            cout << *it << " ";
        for(auto it = next.begin(); it != next.end(); it++)
            cout << *it << " ";
        cout << endl;
*/
    }
    // print result
    seed = next;
    double min = *seed.begin();
    for(auto it = seed.begin(); it != seed.end(); it++){
        cout << fixed << *it << " ";
        if(*it < min)
            min = *it;
    }
    cout << fixed << endl << "min: " << min << endl;
    inputf.close();
    return 0;
}