#include "headers/puzzle.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

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
        cout << "Profundidade: " << depth << "\n";
        printState(s);
        return;
    }
    
    showPath(parent[s], ini, depth - 1);
    cout << "Profundidade: " << depth << "\n";
    printState(s);
}

void showPath2(const string& s, const string& ini, int depth) {
    vector<string> caminho;
    string atual = s;
    int iteracao = 0;
    int tamanhoVet = atual.size();
    clock_t inicio = clock();



    while (atual != ini) {

        caminho.push_back(atual);
        atual = parent.at(atual);
        iteracao++;
    }

    
    while ((double)(clock() - inicio) / CLOCKS_PER_SEC < 20.0) {
    }

    iteracao == 0;
    caminho.push_back(ini);
    for (int i = (int)caminho.size() - 1; i >= 0; i--) {
        cout << "Profundidade: " << depth - i << "\n";
        printState(caminho[i]);
    }
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
