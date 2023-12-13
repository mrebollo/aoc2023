#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


void print(vector<int> numbers){
    for (int it: numbers)
        cout << it << " ";
    cout << endl;
}


vector<int> load_from_string(string line){
    vector<int> numbers;
    stringstream ss(line);
    int number;
    while (ss >> number)
        numbers.push_back(number);
    return numbers;
}

vector<int> load_from_string_reverse(string line){
    vector<int> numbers;
    stringstream ss(line);
    int number;
    while (ss >> number)
        numbers.insert(numbers.begin(), number);
    return numbers;
}

//usando tail recursion
void diff(vector<int> numbers, int *prediction){
    print(numbers);
    *prediction += numbers.back();
    if (numbers.back() == 0)
        return;
    vector<int> result;
    for (int i = 1; i < numbers.size(); i++)
        result.push_back(numbers[i] - numbers[i-1]);
    cout << " -> " << *prediction << endl;
    diff(result, prediction);
}

int differences(vector<int> numbers){
    print(numbers);
    if (numbers[0] == numbers.back())
        return numbers[0];
    vector<int> result;
    for (int i = 1; i < numbers.size(); i++)
        result.push_back(numbers[i] - numbers[i-1]);
    return numbers.back() + differences(result);
}


int main() {
    fstream inputf;
    string line;

    //inputf.open("input.txt");
    inputf.open("adventofcode.com_2023_day_9_input.txt");
    vector<int> numbers;
    int total_pred = 0;
    while(getline(inputf, line)) {
        int prediction = 0;
        numbers = load_from_string_reverse(line);
        prediction = differences(numbers);
        total_pred += prediction;
        cout << "Prediction: " << prediction << " - Total: " << total_pred << endl;
        cout << "--" << endl;
    }
    inputf.close();
    cout << fixed << "Total prediction: " << total_pred << endl;
    return 0;
}