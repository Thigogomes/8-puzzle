#include "headers/puzzle.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string inicial;
unordered_map<string, string> parent;

bool isGoal(const string& s){
    return s == "012345678";
}

int findBlank(const string& s){
    return s.find('0');
}

void printState(const string& s){
    cout << "[";
    for(int i = 0; i < (int)s.size(); i++){
        cout << s[i];
        if((i+1) % 3 == 0){
            cout << "] \n" << ((i+1) < 8 ? "[" : "");
        }else{
            cout << " ";
        }
    }
    cout << endl;
}

void showPath(const string& s, const string& ini, int depth){
    if(s == ini){
        cout << "Estado inicial:\n";
        printState(s);
        return;
    }
    showPath(parent[s], ini, depth - 1);
    cout << "Profundidade: " << depth << "\n";
    printState(s);
}

vector<string> generateMoves(const string& s){
    vector<string> children;
    int blank = findBlank(s);

    if(blank > 2){
        string child = s; swap(child[blank], child[blank - 3]); children.push_back(child);
    }
    if(blank < 6){
        string child = s; swap(child[blank], child[blank + 3]); children.push_back(child);
    }
    if(blank % 3 != 0){
        string child = s; swap(child[blank], child[blank - 1]); children.push_back(child);
    }
    if(blank % 3 != 2){
        string child = s; swap(child[blank], child[blank + 1]); children.push_back(child);
    }
    return children;
}