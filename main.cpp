#include <iostream>
#include "ler_arquivo.h"
#include "decodificador.h"

using namespace std;

void printaInfos(vector<string> infos) {
    for(int i=1; i <= 9; i++) {
        cout << infos[i] << " ";
    }
    cout << "\n";
}


int main()
{   

    vector<vector<string>> matrizLinhas = linhasLidas("arquivo.txt");

    for (int i = 0; i <  3; i++) {
        cout << endl;
        
        printaInfos(decodificaTipo(matrizLinhas[i][1]));
        
        cout << "PC = ";

        cout << matrizLinhas[i][0] << " ";

        cout << matrizLinhas[i][1] << endl;
    }

    return 0;
}