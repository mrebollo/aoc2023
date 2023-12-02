/*
advent of code day 2 part 2
valid games with red, blue, green cubes
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// cubes in the game
int cubes[128] = {['r'] = 12, ['g'] = 13, ['b'] = 14};

int valid(int game[]){
    return cubes['r'] >= game['r'] && cubes['g'] >= game['g'] && cubes['b'] >= game['b'];
}


int main()
{

    //abrir fichero input.txt
    ifstream inputf;

    //leer linea a linea
    string line; 
    int total = 0, current_game;
    inputf.open("adventofcode.com_2023_day_2_input.txt");
    while(getline(inputf, line))
    {
        int is_valid = 1;
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
            int game[128] =  {['r'] = 0, ['g'] = 0, ['b'] = 0};
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
            if(!valid(game)){
#ifdef _DEBUG
                cout << "...invalid set" << endl;
#endif
                is_valid = 0;
                continue;
            }
#ifdef _DEBUG
            cout << "...valid set" << endl;
#endif
        }
        if(is_valid)
            total += current_game;
#ifdef _DEBUG
        cout << "total: " << total << endl;
#endif
    }
    cout << "Total global: " << total << endl;
    //cerrar fichero
    inputf.close();
    return 0;
}