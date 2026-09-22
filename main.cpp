#include <iostream>
#include "ler_arquivo.h"
#include "decodificador.h"
#include "utils.h"

using namespace std;

void printaInfos(vector<string> infos) {
    cout << "tipo mnemonico rd rs1 rs2 imm funct3 funct7" << endl;
    for(int i=1; i <= 9; i++) {
        cout << infos[i] << " ";
    }
    cout << "\n";
}

int main()
{   
    float* contagem = (float*)calloc(6, sizeof(float));
    vector<vector<string>> matrizLinhas = linhasLidas("arquivo_02.txt");

    for (int i = 0; i <  matrizLinhas.size(); i++) {
        cout << endl;
        
        vector<string> instInfos = decodificaTipo(matrizLinhas[i][1]);
        printaInfos(instInfos);
        
        cout << "PC = ";

        cout << matrizLinhas[i][0] << " ";

        cout << matrizLinhas[i][1] << endl;

        geradorEstatistica(instInfos[1], contagem);
    }

    int totalInstrucoes = matrizLinhas.size();

    cout << "Numero Tipo R: " << contagem[0] << " Numero em % total: " << ((contagem[0]/totalInstrucoes)*100) << endl;
    cout << "Numero Tipo I: " << contagem[1] << " Numero em % total: " << ((contagem[1]/totalInstrucoes)*100) << endl;
    cout << "Numero Tipo S: " << contagem[2] << " Numero em % total: " << ((contagem[2]/totalInstrucoes)*100) << endl;
    cout << "Numero Tipo B: " << contagem[3] << " Numero em % total: " << ((contagem[3]/totalInstrucoes)*100) << endl;
    cout << "Numero Tipo U: " << contagem[4] << " Numero em % total: " << ((contagem[4]/totalInstrucoes)*100) << endl;
    cout << "Numero Tipo J: " << contagem[5] << " Numero em % total: " << ((contagem[5]/totalInstrucoes)*100) << endl;
    

    return 0;
}