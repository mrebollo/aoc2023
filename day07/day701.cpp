#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

char values[13] = {'A','K','Q','J','T','9','8','7','6','5','4','3','2'};

struct game{
    string cards;
    int bid;
};

struct node {
    game data;
    node* left;
    node* right;
};


int compare(){
    return 0;
}


void show(node* root) {
    if (root != NULL) {
        show(root->left);
        cout << root->data.cards << " ";
        cout << root->data.bid << " " << endl;
        show(root->right);
    }
}
 
void insert(node* &root, game data) {
    if (root == NULL) {
        root = new node;
        root->data = data;
        root->left = NULL;
        root->right = NULL;
    }
    else if (data.bid < root->data.bid) {
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

    //inputf.open("adventofcode.com_2023_day_7_input.txt");
    inputf.open("input.txt");
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
    return 0;
}