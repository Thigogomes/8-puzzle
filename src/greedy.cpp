#include "headers/puzzle.h"
#include "headers/heuristics.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;

struct NodeGreedy {
    string state;
    int h;
    int depth;
    bool operator>(const NodeGreedy& other) const {
        return h > other.h;
    }
};

void greedyLinearConflict(const string& s){
    auto startTime = chrono::high_resolution_clock::now();
    parent.clear();

    priority_queue<NodeGreedy, vector<NodeGreedy>, greater<NodeGreedy>> pq;
    unordered_map<string, bool> visited;
    int visitados = 0;

    pq.push({s, h3_linearConflict(s), 0});

    while(!pq.empty()){
        NodeGreedy current = pq.top();
        pq.pop();

        if(visited[current.state]) continue;
        visited[current.state] = true;
        visitados++;

        if(isGoal(current.state)){
            auto endTime = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double, milli>(endTime - startTime).count();

            showPath(current.state, inicial, current.depth);

            cout << "\nObjetivo encontrado!";
            cout << "\nEm movimentos:   " << current.depth;
            cout << "\nNos visitados:   " << visitados;
            cout << "\nTempo:           " << ms << " ms\n" << endl;

            return;
        }

        for(const string& next : generateMoves(current.state)){
            if(!visited[next]){
                parent[next] = current.state;
                pq.push({next, h3_linearConflict(next), current.depth + 1});
            }
        }
    }

    cout << "\nBusca Gulosa (Conflito Linear) concluida.\n\n";
    printState(s);
    cout << "Esse estado inicial nao possui solucao.\n" << endl;
}

void greedyManhattan(const string& s){
    auto startTime = chrono::high_resolution_clock::now();
    parent.clear();

    priority_queue<NodeGreedy, vector<NodeGreedy>, greater<NodeGreedy>> pq;
    unordered_map<string, bool> visited;
    int visitados = 0;

    pq.push({s, h2_manhattan(s), 0});

    while(!pq.empty()){
        NodeGreedy current = pq.top();
        pq.pop();

        if(visited[current.state]) continue;
        visited[current.state] = true;
        visitados++;

        if(isGoal(current.state)){
            auto endTime = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double, milli>(endTime - startTime).count();

            showPath(current.state, inicial, current.depth);

            cout << "\nObjetivo encontrado!";
            cout << "\nEm movimentos:   " << current.depth;
            cout << "\nNos visitados:   " << visitados;
            cout << "\nTempo:           " << ms << " ms\n" << endl;

            return;
        }

        for(const string& next : generateMoves(current.state)){
            if(!visited[next]){
                parent[next] = current.state;
                pq.push({next, h2_manhattan(next), current.depth + 1});
            }
        }
    }

    cout << "\nBusca Gulosa (Manhattan) concluida.\n\n";
    printState(s);
    cout << "Esse estado inicial nao possui solucao.\n" << endl;
}

void greedyHamming(const string& s){
    auto startTime = chrono::high_resolution_clock::now();
    parent.clear();

    priority_queue<NodeGreedy, vector<NodeGreedy>, greater<NodeGreedy>> pq;
    unordered_map<string, bool> visited;
    int visitados = 0;

    pq.push({s, h1_hamming(s), 0});

    while(!pq.empty()){
        NodeGreedy current = pq.top();
        pq.pop();

        if(visited[current.state]) continue;
        visited[current.state] = true;
        visitados++;

        if(isGoal(current.state)){
            auto endTime = chrono::high_resolution_clock::now();
            double ms = chrono::duration<double, milli>(endTime - startTime).count();
            
            showPath(current.state, inicial, current.depth);

            cout << "\nObjetivo encontrado!";
            cout << "\nEm movimentos:   " << current.depth;
            cout << "\nNos visitados:   " << visitados;
            cout << "\nTempo:           " << ms << " ms\n" << endl;

            return;
        }

        for(const string& next : generateMoves(current.state)){
            if(!visited[next]){
                parent[next] = current.state;
                pq.push({next, h1_hamming(next), current.depth + 1});
            }
        }
    }

    cout << "\nBusca Gulosa (Hamming) concluida.\n\n";
    printState(s);
    cout << "Esse estado inicial nao possui solucao.\n" << endl;
}