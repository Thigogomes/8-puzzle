#include <iostream>
using namespace std;
void printTabuleiro(string s);
string recebeEstadoInicial();
void printTutorial();

int main() {
    int pausa = 1;
    string estadoInicial;

    cout << "Bem vindo ao 8-Puzzle!" << endl;
    printTutorial();
    cout << "Escolhendo um estado inicial..." << endl;
    estadoInicial = recebeEstadoInicial();
    printTabuleiro(estadoInicial);

        cin >> pausa;
    return 0;
}

void printTabuleiro(string s) {
    cout << "[";
    for(int i = 0; i < (9); i++){
        cout << s[i];

        if((i+1) % 3 == 0){
            cout << "] \n" << ((i+1) < 8 ? "[" : "");
        }else{
            cout << " ";
        }
    }
    cout << endl;
}

string recebeEstadoInicial() {
    string entrada;
    for(int i=0; i<1; i++){
        cout << "Digite o estado inicial (9 caracteres): ";
        cin >> entrada;
        if(entrada.length() != 9){
            cout << "Entrada inválida. O estado inicial deve conter exatamente 9 caracteres." << endl;
            i--; 
        }
    }
    return entrada;
}

void printTutorial() {
    cout << "Tutorial do 8-Puzzle:" << endl;
    cout << "O objetivo do jogo e organizar os numeros de 1 a 8 em ordem crescente, com o espaço vazio (representado por 0) no final." << endl;
    cout << "Voce pode mover os numeros adjacentes ao espaco vazio para a posicao do espaco vazio." << endl;
    cout << "Exemplo de estado inicial: 564806482" << endl;
    cout << "Neste exemplo, o numero 0 representa o espaco vazio." << endl;
    char c[9] = {'5', '6', '4', '8', '0', '6', '4', '8', '2'};
    printTabuleiro(c);
}