#include <iostream>
#include "ler_arquivo.h"

using namespace std;


int main()
{   

    vector<vector<string>> matrizLinhas = linhasLidas("arquivo.txt");

    //vector<string> linhas = linhasLidas("arquivo.txt");
    
    for (int i = 0; i < matrizLinhas.size(); i++) {
        cout << "PC = ";
        for (int j = 0; j < matrizLinhas[i].size(); j++) {
            cout << matrizLinhas[i][j] << "  ";
        }
        cout << endl;
    }
    /* 
    for (string s : linhas){
        string instBin = conversorHexBin(s);
        cout << instBin << "\n";
        decodificaTipo(instBin);
    } */

    return 0;
}