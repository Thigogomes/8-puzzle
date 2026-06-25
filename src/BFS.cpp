#include "headers/BFS.h"
#include "headers/puzzle.h"
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

struct NodeBFS {
    string state;
    int depth;
};

void bfs(const string& s){
    inicial = s;
    auto startTime = chrono::high_resolution_clock::now();
    queue<NodeBFS> q;
    unordered_set<string> visited;
     int visitados = 0;

    q.push({s, 0});
    visited.insert(s);

    while(!q.empty()){
        NodeBFS current = q.front();
        q.pop();
        visitados++;

        if(isGoal(current.state)){
            auto endTime = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double, milli>(endTime - startTime).count();

            cout << "\nObjetivo encontrado!";
            cout << "\nEm movimentos: " << current.depth << endl;
            cout << "\nTempo de execução: " << ms << " ms" << endl;
            cout << "\nNos visitados:   \n" << visitados;

            //showPath(current.state, inicial, current.depth);
            return;
        }

        for(const string& next : generateMoves(current.state)){
            if(visited.find(next) == visited.end()){
                visited.insert(next);
                parent[next] = current.state;
                q.push({next, current.depth + 1});
            }
        }
    }

    cout << "\nBusca em Largura (BFS) concluída.\n\n";
    printState(s);
    cout << "\nEsse estado inicial não possui solução.\n" << endl;
}