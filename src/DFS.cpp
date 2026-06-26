#include "headers/DFS.h"
#include "headers/puzzle.h"
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

bool limitDepth = false;
int maxDepth = 1000;

struct NodeDFS {
    string state;
    int depth;
};

void dfs(const string& s) {
    inicial = s;
    parent.clear();

    auto startTime = chrono::high_resolution_clock::now();

    stack<NodeDFS> stk;
    unordered_set<string> visited;
    unordered_set<string> inStack;

    stk.push({s, 0});
    inStack.insert(s);

    int visitados = 0;

    while (!stk.empty()) {

        NodeDFS current = stk.top();
        stk.pop();

        inStack.erase(current.state);

        if (visited.count(current.state)) continue;

        visited.insert(current.state);
        visitados++;

        if (isGoal(current.state)) {
            auto endTime = chrono::high_resolution_clock::now();

            double ms = chrono::duration<double, milli>(endTime - startTime).count();

            showPath2(current.state, inicial, current.depth);

            cout << "\nObjetivo encontrado!";
            cout << "\nEm movimentos:   " << current.depth;
            cout << "\nNos visitados:   " << visitados;
            cout << "\nTempo:           " << ms << " ms\n";

            return;
        }

        for (const string& next : generateMoves(current.state)) {

            if (visited.count(next)) continue;
            if (inStack.count(next)) continue;

            if (limitDepth && current.depth + 1 > maxDepth)
                continue;

            parent[next] = current.state;

            stk.push({next, current.depth + 1});
            inStack.insert(next);
        }
    }

    cout << "\nBusca em Profundidade (DFS) concluida.\n\n";
    printState(s);
    cout << "Esse estado inicial nao possui solucao.\n";
}