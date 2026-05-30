#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>

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

string escolherEstado()
{
    return estadosPossiveis[rand() % estadosPossiveis.size()];
}

string inicial;  // Estado inicial aleatório

unordered_map<string, string> parent;  // <Child, Parent>

struct Node{
    string state;
    int depth;
};

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

void showPath(string s, string inicial, int depth){
    if(s == inicial){
        cout << "Estado inicial:\n";
        printState(s);
        return;
    }

    showPath(parent[s], inicial, depth - 1);
    cout << "Profundidade: " << depth << "\n";
    printState(s);
}

vector<string> generateMoves(string s){
    vector<string> children;

    int blanck = findBlanck(s);

    for(int i = 0; i < 4; i++){
        
        if(i == 0 && blanck > 2){ // up
            string child = s;
            swap(child[blanck], child[blanck - 3]);
            children.push_back(child);
        }
        else if(i == 1 && blanck < 6){ // down
            string child = s;
            swap(child[blanck], child[blanck + 3]);
            children.push_back(child);
        }
        else if(i == 2 && blanck % 3 != 0){ // left
            string child = s;
            swap(child[blanck], child[blanck - 1]);
            children.push_back(child);
        }
        else if(i == 3 && blanck % 3 != 2){ // right
            string child = s;
            swap(child[blanck], child[blanck + 1]);
            children.push_back(child);
        }
    }

    return children;
}

void bfs(string s){
    queue<Node> q;

    unordered_set<string> visited;

    q.push({s, 0});

    visited.insert(s);

    while(!q.empty()){
        Node current = q.front();
        q.pop();

        if(isGoal(current.state)){
            cout << "\nObjetivo encontrado!";
            cout << "\nEm movimentos: " << current.depth << "\n" <<endl;

            showPath(current.state, inicial, current.depth);

            return;
        }

        vector<string> children = generateMoves(current.state);

        for (string next : children){
            if (visited.find(next) == visited.end()){
                visited.insert(next);
                parent[next] = current.state;
                q.push({next, current.depth + 1});
            }
        }
    }

    cout << "\nBusca em Largura (BFS) concluída.\n\n";
    printState(s);
    cout << "Esse estado inicial não possui solução.\n" << endl;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand(time(nullptr));
    inicial = estadosPossiveis[rand() % estadosPossiveis.size()];

    bfs(inicial);
    return 0;
}