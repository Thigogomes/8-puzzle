#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;

void printTabuleiro(string s);
string recebeEstadoInicial();
void printTutorial();
int menuAlgoritmo();
int menuHeuristica();
int lerOpcao();


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "Bem vindo ao 8-Puzzle!" << endl;
    printTutorial();

    system("pause");

    string estadoInicial = recebeEstadoInicial();

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


    switch(algoritmo){
        case 1:
            // heuristica == 1 → h1: Pecas fora do lugar (Hamming)
            // heuristica == 2 → h2: Distancia de Manhattan
            // heuristica == 3 → h3: Conflito Linear

            // TODO: astar(estadoInicial, heuristica);

            cout << "[A* - heuristica " << heuristica << "] ainda nao implementado\n";
            break;

        case 2:
            // TODO: bfs(estadoInicial);

            cout << "[BFS] ainda nao implementado\n";
            break;

        case 3:
            // TODO: dfs(estadoInicial);

            cout << "[DFS] ainda nao implementado\n";
            break;

        case 4:
            // TODO: custoUniforme(estadoInicial);

            cout << "[Custo Uniforme] ainda nao implementado\n";
            break;

        case 5:
            // heuristica == 1 → h1: Pecas fora do lugar (Hamming)
            // heuristica == 2 → h2: Distancia de Manhattan
            // heuristica == 3 → h3: Conflito Linear

            // TODO: gulosa(estadoInicial, heuristica);

            cout << "[Gulosa - heuristica " << heuristica << "] ainda nao implementado\n";
            break;
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
        cout << "\nOpcao: ";

        opcao = lerOpcao();

        if(opcao >= 1 && opcao <= 5) break;

        cout << "Opcao invalida. Digite um numero entre 1 e 5.\n";
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