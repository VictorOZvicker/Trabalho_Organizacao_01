#include <iostream>
#include "ler_arquivo.h"

using namespace std;


int main()
{
    vector<string> linhas = linhasLidas("arquivo.txt");
    
    for (int i = 0; i < linhas.size(); i++) {
        cout << linhas[i] << endl;
    }
    
    for (string s : linhas){
        cout << conversorHexBin(s) << "\n";
    }

    return 0;
}