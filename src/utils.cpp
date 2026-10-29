#include <fstream>
#include "utils.h"
#include "ler_arquivo.h"
#include "decodificador.h"
#include "hazard_detection.h"

using namespace std;

void contarTipoInst(string instTipo, float *contagem) {
    
    switch(instTipo.at(0)) {
        case 'R': contagem[0]++; break;
        case 'I': contagem[1]++; break;
        case 'S': contagem[2]++; break;
        case 'B': contagem[3]++; break;
        case 'U': contagem[4]++; break;
        case 'J': contagem[5]++; break;
    }
    
}

float calculoCpiMedio(int numeroTotalInst, float quantidade, float cpi) {
    return ((quantidade / numeroTotalInst) * cpi);
    
}

vector<string> geradorEstatistica(float *contagem, float *cpi, int totalInstrucoes) {
    vector<string> saida;
    float cpiMedioPrograma = 0;
    for (int i = 0; i < 6; i++) {
        cpiMedioPrograma += calculoCpiMedio(totalInstrucoes, contagem[i], cpi[i]);
    }
    
    saida.push_back(format("Numero inst. Tipo R: {} Percentual: {}% \n",contagem[0], (contagem[0]/totalInstrucoes)*100));
    saida.push_back(format("Numero inst. Tipo I: {} Percentual: {}% \n",contagem[1], (contagem[1]/totalInstrucoes)*100));
    saida.push_back(format("Numero inst. Tipo S: {} Percentual: {}% \n",contagem[2], (contagem[2]/totalInstrucoes)*100));
    saida.push_back(format("Numero inst. Tipo B: {} Percentual: {}% \n",contagem[3], (contagem[3]/totalInstrucoes)*100));
    saida.push_back(format("Numero inst. Tipo U: {} Percentual: {}% \n",contagem[4], (contagem[4]/totalInstrucoes)*100));
    saida.push_back(format("Numero inst. Tipo J: {} Percentual: {}% \n",contagem[5], (contagem[5]/totalInstrucoes)*100));
    saida.push_back(format("Contagem total de instrucoes: {}\n",totalInstrucoes));
    saida.push_back(format("CPI medio do programa: {}\n",cpiMedioPrograma));

    return saida;
}

int conversorBinUnsignedInt(string bin){
    return stoi(bin, nullptr, 2);
}

int conversorBinSignedInt(string bin) {
    int contador = 0;
    int size = bin.size();
    for(int i = 0; i < size; i++) {
        int p = bin.at(i) - '0';
        if(i == 0) p *= -1;
        contador += p * pow(2, size-i-1);
    }
    return contador;
}

string conversorHexBin(string hex) {

    string bin = "";

    for (char c : hex) {
        switch (toupper(c)) 
        {
            case '0': bin += "0000"; break; case '1': bin += "0001"; break;
            case '2': bin += "0010"; break; case '3': bin += "0011"; break;
            case '4': bin += "0100"; break; case '5': bin += "0101"; break;
            case '6': bin += "0110"; break; case '7': bin += "0111"; break;
            case '8': bin += "1000"; break; case '9': bin += "1001"; break;
            case 'A': bin += "1010"; break; case 'B': bin += "1011"; break;
            case 'C': bin += "1100"; break; case 'D': bin += "1101"; break;
            case 'E': bin += "1110"; break; case 'F': bin += "1111"; break;
            default: bin += "";
        }
    }

    return bin;
}

int hexToInt(string hex){
    return stoi(hex, nullptr, 16);
}

vector<Instruction> extrairInstInfos(string path){

    vector<string> instLidas = linhasLidas(path);

    if(instLidas.empty()){ 
        cerr << "Arquivo não encontrado" << endl;
        return {};
    }
    vector<Instruction> instInfos;

    for(int i=0; i < instLidas.size(); i++)
    {
        instInfos.push_back(decodificaTipo(instLidas[i]));

        // DEPOIS TEM QUE AJUSTAR O CAMINHO ABSOLUTO DOS JUMPS/BRANCHS
    }

    return instInfos;
}

string outputString(vector<Instruction> insts){

    float* contagem = (float*)calloc(6, sizeof(float));
    float cpi[6] = { 4.0, 3.0, 1.0, 5.0, 2.0, 3.0 };

    string output;
    for (int i = 0; i <  insts.size(); i++) {

        output += "tipo mnemonico rd rs1 rs2 imm funct3 funct7\n";
        output += insts[i].formato   + " ";
        output += insts[i].mnemonico + " ";
        output += insts[i].rd        + " ";
        output += insts[i].rs1       + " ";
        output += insts[i].rs2       + " ";
        output += insts[i].imm       + " ";
        output += insts[i].funct3    + " ";
        output += insts[i].funct7    + " ";
        output += insts[i].assembly  + "\n";

        output += "PC = ";

        output += to_string(i*4) += " ";

        output += insts[i].bin += "\n";

        contarTipoInst(insts[i].formato, contagem);

        output += "\n";
    }

    int totalInstrucoes = insts.size();

    vector<string> estatisticas = geradorEstatistica(contagem, cpi, totalInstrucoes);
    output += "\n";
    for(int i=0; i < estatisticas.size(); i++){
        output += estatisticas[i];
    }
    return output;
}


bool gerarOutput(string text){

    ofstream output("output.txt");
    if(!output) {
        cerr << "Erro ao escrever o output." << endl;
        return false;
    }
    output << text;

    output.close();

    return true;
}

bool gerarOutputNop (string text) {
    ofstream output("solucao_nop.txt");
    if(!output) {
        cerr << "Erro ao escrever o output para Nop." << endl;
        return false;
    }
    output << text;

    output.close();

    return true;
}

bool gerarOutputReordenacao (string text) {
    ofstream output("solucao_reordenacao.txt");
    if(!output) {
        cerr << "Erro ao escrever o output para reordenacao." << endl;
        return false;
    }
    output << text;

    output.close();

    return true;
}

bool menu(string inputPath) {

    cout << "\tMenu" << endl;
    cout << "1.Etapa M1" << endl;
    cout << "2.Etapa M2" << endl;
    cout << "0.sair" << endl;
    char opc;
    cout << "Escolha uma opcao: ";
    cin >> opc;
    switch (opc)
    {
    case '1':
        return gerarOutput(outputString(extrairInstInfos(inputPath)));
    case '2':
        gerarOutputNop(resolucaoNop(extrairInstInfos(inputPath)));
        gerarOutputReordenacao(resolucaoReordenacao(extrairInstInfos(inputPath)));
        return true;
    case '0':
        cout << "Saindo...";
        break;
    default:
        cout << "Opcao inválida.";
        break;
    }
    return false;
}
