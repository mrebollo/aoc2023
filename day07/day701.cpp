#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct game{
    string cards;
    int bid;
};

struct node {
    game data;
    node* left;
    node* right;
};

int factor = 0, winnings = 0;

int ranking(char c){
    switch(c){
        case 'A': return 14;
        case 'K': return 13;
        case 'Q': return 12;
        case 'J': return 11;
        case 'T': return 10;
        default: return c - '0';
    }
}


int wins(game g1, game g2){
    set<char> g1set (g1.cards.begin(), g1.cards.end());
    set<char> g2set (g2.cards.begin(), g2.cards.end());
    // secuencia más corta -> mejor jugada (set(AAAAA) = {A})
    if(g1set.size() != g2set.size())
        return g1set.size() < g2set.size();
    else {
        // contar cartas de cada valor
        int max1 = 0, max2 = 0, c1, c2;
        for(auto it = g1set.begin(); it != g1set.end(); it++){
            c1 = count(g1.cards.begin(), g1.cards.end(), *it);
            if(c1 > max1) max1 = c1;
        }
        for(auto it = g2set.begin(); it != g2set.end(); it++){
            c2 = count(g2.cards.begin(), g2.cards.end(), *it);
            if(c2 > max2) max2 = c2;
        }
        // el máximo de los dos gana (4+1 > 3+2)
        if(max1 != max2)
            return max1 > max2;
        else{
            // el valor de la primera carta más alta gana (A > K)
            int i = 0;
            do{
                if(ranking(g1.cards[i]) != ranking(g2.cards[i]))
                    return ranking(g1.cards[i]) > ranking(g2.cards[i]); 
                i++; 
            }while(i < g1.cards.size());
            return 0;
        } 
    }
}

// inorder tree traversal
void show(node* root) {
    if (root != NULL) {
        show(root->left);
        cout << root->data.cards << " ";
        cout << root->data.bid << " ";
        cout << " x " << factor << " -> " << root->data.bid * factor << endl;
        winnings += root->data.bid * factor;
        factor--;
        show(root->right);
    }
}


void insert(node* &root, game data) {
    if (root == NULL) {
        root = new node;
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        factor++;
    }
    else if (wins(data, root->data)) {
        insert(root->left, data);
    }
    else {
        insert(root->right, data);
    }
}


int main() {
    fstream inputf;
    string line;
    node *ranktree = NULL;

    inputf.open("adventofcode.com_2023_day_7_input.txt");
    //inputf.open("input.txt");
    while (getline(inputf, line))
    {
        game hand;
        istringstream strm(line);
        strm >> hand.cards;
        strm >> hand.bid;
        insert(ranktree, hand);
    }
    inputf.close();
    show(ranktree);
    cout << "Total winnings: " << winnings << endl;
    return 0;
}