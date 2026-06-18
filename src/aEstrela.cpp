#include "headers/aEstrela.h"
#include "headers/puzzle.h"
#include "headers/heuristics.h"
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <chrono>

using namespace std;

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

void aStarManhattan(const string& s){
    auto startTime = chrono::high_resolution_clock::now();

    parent.clear();

    priority_queue<NodeAS, vector<NodeAS>, greater<NodeAS>> pq;
    unordered_map<string, int> gScore;
    int visitados = 0;

    pq.push({s, 0, h2_manhattan(s)});
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
                pq.push({next, newG, h2_manhattan(next)});
            }
        }
    }

    cout << "\nBusca A* (Manhattan) concluida.\n\n";
    printState(s);
    cout << "Esse estado inicial nao possui solucao.\n" << endl;
}