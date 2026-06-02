#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

using namespace std;


vector<string> estadosPossiveis = {
    "123456780",
    "123456708",
    "123450786",
    "123405678",
    "103425678",
    "120453786",
    "125340678",
    "281043765",
    "724506831",
    "867254301"
};

string inicial;
unordered_map<string, string> parent;


bool isGoal(string s){
    return s == "012345678";
}

int findBlanck(string s){
    return s.find('0');
}

void printState(string s){
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

void showPath(string s, string ini, int depth){
    if(s == ini){
        cout << "Estado inicial:\n";
        printState(s);
        return;
    }
    showPath(parent[s], ini, depth - 1);
    cout << "Profundidade: " << depth << "\n";
    printState(s);
}

vector<string> generateMoves(string s){
    vector<string> children;
    int blanck = findBlanck(s);

    if(blanck > 2){                   // up
        string child = s; swap(child[blanck], child[blanck - 3]); children.push_back(child);
    }
    if(blanck < 6){                   // down
        string child = s; swap(child[blanck], child[blanck + 3]); children.push_back(child);
    }
    if(blanck % 3 != 0){             // left
        string child = s; swap(child[blanck], child[blanck - 1]); children.push_back(child);
    }
    if(blanck % 3 != 2){             // right
        string child = s; swap(child[blanck], child[blanck + 1]); children.push_back(child);
    }
    return children;
}

//Funções acima definar para uma classe comum utilitaria


int goalRow(char tile){ return (tile - '0') / 3; }
int goalCol(char tile){ return (tile - '0') % 3; }

// Base do conflito linear: distância de Manhattan
int manhattan(const string& s){
    int dist = 0;
    for(int i = 0; i < 9; i++){
        if(s[i] == '0') continue;
        int row = i / 3, col = i % 3;
        dist += abs(row - goalRow(s[i])) + abs(col - goalCol(s[i]));
    }
    return dist;
}

 
int conflictRow(const string& s){
    int conflicts = 0;
    for(int row = 0; row < 3; row++){
        vector<int> tiles;
        for(int col = 0; col < 3; col++){
            char tile = s[row * 3 + col];
            if(tile == '0') continue;
            if(goalRow(tile) == row)    // peça já está na linha certa
                tiles.push_back(tile - '0');
        }
        // Conta pares fora de ordem (inversões)
        for(int i = 0; i < (int)tiles.size(); i++)
            for(int j = i + 1; j < (int)tiles.size(); j++)
                if(tiles[i] > tiles[j])
                    conflicts++;
    }
    return conflicts;
}


int conflictCol(const string& s){
    int conflicts = 0;
    for(int col = 0; col < 3; col++){
        vector<int> tiles;
        for(int row = 0; row < 3; row++){
            char tile = s[row * 3 + col];
            if(tile == '0') continue;
            if(goalCol(tile) == col)    // peça já está na coluna certa
                tiles.push_back(tile - '0');
        }
        for(int i = 0; i < (int)tiles.size(); i++)
            for(int j = i + 1; j < (int)tiles.size(); j++)
                if(tiles[i] > tiles[j])
                    conflicts++;
    }
    return conflicts;
}

int h3_linearConflict(const string& s){
    return manhattan(s)
         + 2 * conflictRow(s)
         + 2 * conflictCol(s);
}



struct Node{
    string state;
    int g;      // custo real (movimentos feitos)
    int h;      // estimativa heurística (conflito linear)
    int f() const { return g + h; }

    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};



void astar(string s){
    auto startTime = chrono::high_resolution_clock::now();

    parent.clear();

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<string, int> gScore;
    int visitados = 0;

    pq.push({s, 0, h3_linearConflict(s)});
    gScore[s] = 0;

    while(!pq.empty()){
        Node current = pq.top();
        pq.pop();

        // Descarta se já tem caminho melhor para este estado
        if(current.g > gScore[current.state]) continue;

        visitados++;

        if(isGoal(current.state)){
            auto endTime = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double, milli>(endTime - startTime).count();

            cout << "\nObjetivo encontrado!";
            cout << "\nEm movimentos:   " << current.g;
            cout << "\nNos visitados:   " << visitados;
            cout << "\nTempo:           " << ms << " ms\n" << endl;

            showPath(current.state, inicial, current.g);
            return;
        }

        for(string next : generateMoves(current.state)){
            int newG = current.g + 1;
            if(gScore.find(next) == gScore.end() || newG < gScore[next]){
                gScore[next] = newG;
                parent[next] = current.state;
                pq.push({next, newG, h3_linearConflict(next)});
            }
        }
    }

    cout << "\nBusca A* (Conflito Linear) concluida.\n\n";
    printState(s);
    cout << "Esse estado inicial nao possui solucao.\n" << endl;
}


int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand(time(nullptr));
    inicial = estadosPossiveis[rand() % estadosPossiveis.size()];

    astar(inicial);
    return 0;
}