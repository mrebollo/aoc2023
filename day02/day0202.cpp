/*
advent of code day 2 part 1
valid games with red, blue, green cubes
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void update(int mincubes[], int game[]){
    if(mincubes['r'] < game['r'])
        mincubes['r'] = game['r'];
    if(mincubes['g'] < game['g'])
        mincubes['g'] = game['g'];
    if(mincubes['b'] < game['b'])   
        mincubes['b'] = game['b'];
}


int power(int mincubes[]){
    return mincubes['r'] * mincubes['g'] * mincubes['b'];
}   


int main()
{

    //abrir fichero input.txt
    ifstream inputf;

    //leer linea a linea
    string line; 
    int total = 0, current_game;
    //inputf.open("input.txt");
    inputf.open("adventofcode.com_2023_day_2_input.txt");
    while(getline(inputf, line))
    {
        // cubes in the game
        int mincubes[128] = {0};
        // extrae elementos de la línea
        char *gameptr = NULL, *blockptr = NULL;
        char *tok = strtok_r(&line[0], " ", &gameptr);
        tok = strtok_r(NULL, ":", &gameptr);
        current_game = atoi(tok);
#ifdef _DEBUG
        cout << "Game " << current_game << endl;
#endif
        tok = strtok_r(NULL, ";", &gameptr);
        while(tok != NULL)
        {
            int game[128] =  {0};
#ifdef _DEBUG
            cout << "analying " << tok << endl;
#endif
            //extraction of blocks
            char *btok = strtok_r(tok, " ", &blockptr);
            while(btok != NULL)
            {
                //number
                int num_blocks = atoi(btok);
                btok = strtok_r(NULL, ",", &blockptr);
                //color
                game[btok[0]] += num_blocks;
                btok = strtok_r(NULL, " ", &blockptr);
            }
            tok = strtok_r(NULL, ";", &gameptr);
            update(mincubes, game);
        }
#ifdef _DEBUG
        cout << "mincubes: " << mincubes['r'] << " red - ";
        cout << mincubes['g'] << " green - ";
        cout << mincubes['b'] << " bue" << endl;
#endif
        int gamepower = power(mincubes);
        total += gamepower;
#ifdef _DEBUG
        cout << "game power: " << gamepower << " -> total: " << total << endl;
#endif
    }
    cout << "Total global: " << total << endl;
    //cerrar fichero
    inputf.close();
    return 0;
}