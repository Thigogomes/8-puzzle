#include "headers/aEstrela.h"
#include "headers/puzzle.h"
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <chrono>

using namespace std;

int goalRow(char tile){ return (tile - '0') / 3; }
int goalCol(char tile){ return (tile - '0') % 3; }

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
            if(goalRow(tile) == row)
                tiles.push_back(tile - '0');
        }
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
            if(goalCol(tile) == col)
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

struct NodeAS {
    string state;
    int g;
    int h;
    int f() const { return g + h; }

    bool operator>(const NodeAS& other) const {
        return f() > other.f();
    }
};

void aStarLinearConflict(const string& s){
    auto startTime = chrono::high_resolution_clock::now();

    parent.clear();

    priority_queue<NodeAS, vector<NodeAS>, greater<NodeAS>> pq;
    unordered_map<string, int> gScore;
    int visitados = 0;

    pq.push({s, 0, h3_linearConflict(s)});
    gScore[s] = 0;

    while(!pq.empty()){
        NodeAS current = pq.top();
        pq.pop();

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

        for(const string& next : generateMoves(current.state)){
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