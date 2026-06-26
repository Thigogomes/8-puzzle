#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "headers/puzzle.h"
#include "headers/BFS.h"
#include "headers/aEstrela.h"
#include "headers/greedy.h"
#include "headers/custoUniforme.h"
#include "headers/DFS.h"

using namespace std;

void printTabuleiro(string s);
string recebeEstadoInicial();
void printTutorial();
int menuAlgoritmo();
int menuHeuristica();
int lerOpcao();

vector<string> estadosPossiveis = {
    "123456780",
    "123456708",
    "123450786",
    "123405678",
    "103425678",
    "120453786",
    "125340678",
    "724506831",
    "867254301"
};

void banchMark(){

    for(const string& estado : estadosPossiveis) {
        cout << "Estado: " << estado << "\n";
        cout << endl;

        cout << "Executando BFS...\n";
        bfs(estado);

        cout << "Executando DFS...\n";
        dfs(estado);

        cout << "Executando Custo Uniforme...\n";
        custoUniforme(estado);

        cout << "Executando A* com heurística Hamming...\n";
        aStarHamming(estado);

        cout << "Executando A* com heurística Manhattan...\n";
        aStarManhattan(estado);

        cout << "Executando A* com heurística Conflito Linear...\n";
        aStarLinearConflict(estado);

        cout << "Executando Gulosa com heurística Hamming...\n";
        greedyHamming(estado);

        cout << "Executando Gulosa com heurística Manhattan...\n";
        greedyManhattan(estado);

        cout << "Executando Gulosa com heurística Conflito Linear...\n";
        greedyLinearConflict(estado);
    }

    return;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "Bem vindo ao 8-Puzzle!" << endl;
    printTutorial();

    system("pause");

    while(true){

        string estadoInicial = recebeEstadoInicial();
        inicial = estadoInicial;

        cout << "Estado inicial:\n";
        printTabuleiro(estadoInicial);
        cout << endl;

        int algoritmo = menuAlgoritmo();

        int heuristica = -1;
        if(algoritmo == 1 || algoritmo == 5)
            heuristica = menuHeuristica();

        system("cls");
        cout << "Estado inicial:\n";
        printTabuleiro(estadoInicial);
        cout << endl;

        int saida = 0;

        switch(algoritmo){
            case 1:
                if(heuristica == 1) {
                    cout << "Executando A* com heurística Hamming...\n";
                    aStarHamming(estadoInicial);
                } else if(heuristica == 2) {
                    cout << "Executando A* com heurística Manhattan...\n";
                    aStarManhattan(estadoInicial);
                } else if(heuristica == 3) {
                    cout << "Executando A* com heurística Conflito Linear...\n";
                    aStarLinearConflict(estadoInicial);
                }
            break;

        case 2:
            bfs(estadoInicial);
            break;

        case 3:
            system("cls");

            cout << "Escolha o tipo de DFS: \n\n";
            cout << "1. DFS com profundidade máxima " << endl;
            cout << "2. DFS sem limite de profundidade" << endl;
            int resposta;
            cout << "\nOpção: ";
            cin >> resposta;
            if(resposta == 1) {
                limitDepth = true;
                cout << "Digite a profundidade máxima: ";
                maxDepth = lerOpcao();
            } else {
                limitDepth = false;
            }
            dfs(estadoInicial);
            break;

        case 4:
            custoUniforme(estadoInicial);
            break;

        case 5:

            if(heuristica == 1) {
                cout << "Executando Gulosa com heurística Hamming...\n";
                greedyHamming(estadoInicial);
            } else if(heuristica == 2) {
                cout << "Executando Gulosa com heurística Manhattan...\n";
                greedyManhattan(estadoInicial);
            } else if(heuristica == 3) {
                cout << "Executando Gulosa com heurística Conflito Linear...\n";
                greedyLinearConflict(estadoInicial);
            }
            break;

        case 6:
            cout << "Saindo do programa...\n";
            saida = 1;
            break;
        }
        
        if(saida != 1){
        cout << "Deseja resolver outro estado? (Digite 's' para continuar): ";
        char resposta; 
        cin >> resposta;
        if(resposta != 's' && resposta != 'S') {
            cout << "Encerrando o programa. Obrigado por jogar!\n";
            break;
        }
        }else{
            break;
        }
        
    }

    return 0;
}


void printTabuleiro(string s) {
    while((int)s.size() < 9) s += ' ';

    cout << "[";
    for(int i = 0; i < 9; i++){
        cout << s[i];
        if((i+1) % 3 == 0){
            cout << "] \n" << ((i+1) < 8 ? "[" : "");
        } else {
            cout << " ";
        }
    }
    cout << endl;
}

string recebeEstadoInicial() {
    string entrada = "";

    system("cls");
    cout << "Digite 9 digitos unicos de 0 a 8:\n\n";
    cout << "Digitado: \n\n";
    printTabuleiro(entrada);

    while((int)entrada.size() < 9){
        char c = _getch();

        if(c < '0' || c > '8') continue;           // ignora fora do intervalo
        if(entrada.find(c) != string::npos) continue; // ignora repetido

        entrada += c;

        system("cls");
        cout << "Digite 9 digitos unicos de 0 a 8:\n\n";
        cout << "Digitado: " << entrada << "\n\n";
        printTabuleiro(entrada);
    }

    return entrada;
}

void printTutorial() {
    system("cls");
    cout << "=== 8-Puzzle ===" << endl;
    cout << "\nObjetivo: organize os numeros de 1 a 8 em ordem crescente." << endl;
    cout << "O 0 representa o espaco vazio." << endl;
    cout << "A cada passo, mova uma peca adjacente ao espaco vazio." << endl;
    cout << "\nEstado objetivo:\n" << endl;
    printTabuleiro("012345678");
}

int menuAlgoritmo() {
    int opcao = 0;

    while(true){
        system("cls");
        cout << "Selecione o algoritmo de busca:\n\n";
        cout << "  1. A* (com heuristica)\n";
        cout << "  2. BFS (Busca em Largura)\n";
        cout << "  3. DFS (Busca em Profundidade)\n";
        cout << "  4. Custo Uniforme (Dijkstra)\n";
        cout << "  5. Gulosa (com heuristica)\n";
        cout << "  6. Sair.";
        cout << "\nOpcao: ";

        opcao = lerOpcao();

        if(opcao >= 1 && opcao <= 6) break;

        cout << "Opcao invalida. Digite um numero entre 1 e 6.\n";
        system("pause");
    }

    return opcao;
}

int lerOpcao() {
    string entrada;
    cin >> entrada;

    // verifica se todos os caracteres são dígitos
    for(char c : entrada)
        if(c < '0' || c > '9')
            return -1;

    // verifica se não está vazio
    if(entrada.empty()) return -1;

    return stoi(entrada);
}

int menuHeuristica() {
    int opcao = 0;

    while(true){
        system("cls");
        cout << "Selecione a heuristica:\n\n";
        cout << "  1. Pecas fora do lugar (Hamming)\n";
        cout << "  2. Distancia de Manhattan\n";
        cout << "  3. Conflito Linear\n";
        cout << "\nOpcao: ";

        opcao = lerOpcao();

        if(opcao >= 1 && opcao <= 3) break;

        cout << "Opcao invalida. Digite um numero entre 1 e 3.\n";
        system("pause");
    }

    return opcao;
}