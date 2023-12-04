/*
advent of code day 4 part 1
check numbers in a scrastchcard
*/

#include <iostream>
#include <fstream>
#include <string>

#define WIN 10 // 5
#define NUM 25 // 8
using namespace std;


int check_numbers(int winners[], int numbers[])
{ 
    // truco: 0.5 * 2 = 1 para la primera coincidencia
    // el resto, multiplicar por 2 -> 2, 4, 8...
    float card_value = 0.5;
    for(int i = 0; i < WIN; i++){
        for(int j = 0; j < NUM; j++){
            if(winners[i] == numbers[j]){
                card_value *= 2;
            }
        }
    }
    return card_value;
}
int main()
{
    // variables
    int winners[WIN], numbers[NUM];
    int card_value = 0, total = 0;
    ifstream inputf;
    string line; 
    
    //inputf.open("input.txt");
    inputf.open("adventofcode.com_2023_day_4_input.txt");
    while(getline(inputf, line))
    {
        // lee los numeros ganadores
        char *tok = strtok(&line[0], ":");
        for(int i = 0; i < WIN; i++){
            tok = strtok(NULL, " ");
            winners[i] = atoi(tok);
            cout << winners[i] << " ";
        }
        // ignora la barra vertical 
        tok = strtok(NULL, " ");
        cout << "| ";
        // lee los numeros del carton
        for(int i = 0; i < NUM; i++){
            tok = strtok(NULL, " ");
            numbers[i] = atoi(tok);
            cout << numbers[i] << " ";
        }
        cout << endl;
        card_value = check_numbers(winners, numbers);
        cout << "card value: " << card_value << endl;
        total += card_value;
    }
    cout << "total: " << total << endl;
    return 0;
}