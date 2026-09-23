#include <iostream>
#include <format>
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
    float cpi[6] = { 4.0, 3.0, 1.0, 5.0, 2.0, 3.0 };
    vector<vector<string>> matrizLinhas = linhasLidas("arquivo_01.txt");

    for (int i = 0; i <  matrizLinhas.size(); i++) {
        cout << endl;
        
        vector<string> instInfos = decodificaTipo(matrizLinhas[i][1]);
        
        if(instInfos[1] == "B"  || instInfos[1] == "J") {
            int pos = instInfos[9].find_last_of(',');
            instInfos[9].erase(pos);
            instInfos[9] += format(", {:#x}", hexToInt(matrizLinhas[i][0]) + std::stoi(instInfos[6]));
        }
        
        printaInfos(instInfos);

        
        cout << "PC = ";

        cout << matrizLinhas[i][0] << " ";

        cout << matrizLinhas[i][1] << endl;

        contarTipoInst(instInfos[1], contagem);
    }

    int totalInstrucoes = matrizLinhas.size();

    geradorEstatistica(contagem, cpi, totalInstrucoes);
    return 0;
}