#include "headers/DFS.h"
#include "headers/puzzle.h"
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

struct NodeDFS {
    string state;
    double depth;
};

void dfs(const string& s){
    inicial = s;
    parent.clear();
    auto startTime = chrono::high_resolution_clock::now();

    stack<NodeDFS> stk;
    unordered_set<string> visited;
    int visitados = 0;

    stk.push({s, 0});

    while(!stk.empty()){
        NodeDFS current = stk.top();
        stk.pop();

        if(visited.count(current.state)) continue;
        visited.insert(current.state);
        visitados++;

        if(isGoal(current.state)){
            auto endTime = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double, milli>(endTime - startTime).count();

            //showPath2(current.state, inicial, current.depth);

            cout << "\nObjetivo encontrado!";
            cout << "\nEm movimentos:   " << current.depth;
            cout << "\nNos visitados:   " << visitados;
            cout << "\nTempo:           " << ms << " ms\n" << endl;

            return;
        }

        for(const string& next : generateMoves(current.state)){
            if(!visited.count(next)){
                parent[next] = current.state;
                stk.push({next, current.depth + 1});
            }
        }
    }

    cout << "\nBusca em Profundidade (DFS) concluida.\n\n";
    printState(s);
    cout << "Esse estado inicial nao possui solucao.\n" << endl;
}
