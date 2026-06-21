#include "headers/BFS.h"
#include "headers/puzzle.h"
#include <iostream>
#include <queue>
#include <unordered_map> 
#include <vector>
#include <string>

using namespace std;

void showPathCaminhoUniforme(const string& s, const string& ini, int weight){
    if(s == ini){
        cout << "Estado inicial:\n";
        printState(s);
        return;
    }
    showPathCaminhoUniforme(parent[s], ini, weight - 1);
    cout << "Distancia: " << weight << "\n";
    printState(s);
}

//como o peso no 8puzzle vai ser sempre 1, não é necessario retornar peso ao gerar os caminhos pois todos vão ter o mesmo peso.
vector<string> generateMovesCaminhoUniforme(const string& s){
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

struct NodeCustoUniforme {
    string state;
    int weight; //peso acumulado

    NodeCustoUniforme(string state, int weight){
        this->state = state;
        this->weight = weight;
    }
};
    
//struct para conter a função utilizada para definir o heap do menor para o maior (precisa ser struct devido a como a priority_queue funciona)
struct comparador {
    bool operator()(NodeCustoUniforme a, NodeCustoUniforme b) {
        return a.weight > b.weight;
            
    };
};

void custoUniforme(const string& s){

        
    //heap que ordena os estados do menor peso para o maior
    priority_queue<NodeCustoUniforme, vector<NodeCustoUniforme>, comparador>  heap;

    //define o peso necessario para chegar em um determinado estado
    unordered_map<string, int> dist; 
    
    
    //insere o estado inicial na fila com peso 0
    heap.push({s,0});
    dist.insert({s,0});


    //enquanto tiver nós na fila, remove o proximo nó e trabalha com ele
    while(!heap.empty()){
        
        NodeCustoUniforme current = heap.top();
        heap.pop();

        //caso tenha sido encontrado um mesmo estado porem com um peso mais alto (antigo) ele é desconsiderado
        if(current.weight > dist[current.state]){
        continue;
        }

        if(isGoal(current.state)){
            cout << "\nObjetivo encontrado!";
            cout << "\nPeso final: " << current.weight << "\n" << endl;
            showPathCaminhoUniforme(current.state, inicial, current.weight);
            return;
        }

        for(const string& next : generateMovesCaminhoUniforme(current.state)){
            int novoPeso = current.weight + 1;
            
            //caso o movimento atual não tenha sido ja mapeado, ou resulte em um peso menor do que o mapeado anteriormente, o insere/atualiza
            if(dist.find(next) == dist.end() || novoPeso < dist[next]){

                dist[next] = novoPeso;
                parent[next] = current.state;
                heap.push({next, novoPeso});
            }
        }
    }

    cout << "\nBusca de Custo Uniforme (Dijkstra) concluída.\n\n";
    printState(s);
    cout << "Esse estado inicial não possui solução.\n" << endl;
}