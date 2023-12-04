/*
advent of code day 4 part 2
check numbers in a scrastchcard
you win as many copies as matches
result is the total number of cards

*/

#include <iostream>
#include <fstream>
#include <string>

#define WIN  10 // 5
#define NUM  25 // 8
using namespace std;


void check_numbers(int winners[], int numbers[], int copies[], int current_game)
{ 
    // cada coincidencia meda una carta más del game siguiente
    cout << "game: " << current_game << " - won: ";
    copies[current_game]++;
    int wongame = current_game + 1;
    for(int i = 0; i < WIN; i++){
        for(int j = 0; j < NUM; j++){
            if(winners[i] == numbers[j]){
                cout << wongame << " ";
                copies[wongame++] += copies[current_game];
            }
        }
    }
    cout << endl;
}


int count_cards(int copies[])
{
    int total = 0;
    for(int i = 0; i < 200; i++){
        total += copies[i];
    }
    return total;
}


int main()
{
    // variables
    int winners[WIN], numbers[NUM], copies[200] = {0};
    int card_value = 0, total = 0, gameid = 0;
    ifstream inputf;
    string line; 
    
    //inputf.open("input.txt");
    inputf.open("adventofcode.com_2023_day_4_input.txt");
    while(getline(inputf, line))
    {
        // lee los numeros ganadores
        gameid++;
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
        check_numbers(winners, numbers, copies, gameid);
    }
    total = count_cards(copies);
    cout << "total: " << total << endl;
    return 0;
}