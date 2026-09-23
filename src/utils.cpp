#include <iostream>
#include "utils.h"


void contarTipoInst(std::string instTipo, float *contagem) {
    
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

void geradorEstatistica(float *contagem, float *cpi, int totalInstrucoes) {
    float cpiMedioPrograma = 0;
    for (int i = 0; i < 6; i++) {
        cpiMedioPrograma += calculoCpiMedio(totalInstrucoes, contagem[i], cpi[i]);
    }
    
    std::cout << std::endl;
    std::cout << "Numero inst. Tipo R: " << contagem[0] << " Percentual: " << ((contagem[0]/totalInstrucoes)*100) << " %" << std::endl;
    std::cout << "Numero inst. Tipo I: " << contagem[1] << " Percentual: " << ((contagem[1]/totalInstrucoes)*100) << " %" << std::endl;
    std::cout << "Numero inst. Tipo S: " << contagem[2] << " Percentual: " << ((contagem[2]/totalInstrucoes)*100) << " %" << std::endl;
    std::cout << "Numero inst. Tipo B: " << contagem[3] << " Percentual: " << ((contagem[3]/totalInstrucoes)*100) << " %" << std::endl;
    std::cout << "Numero inst. Tipo U: " << contagem[4] << " Percentual: " << ((contagem[4]/totalInstrucoes)*100) << " %" << std::endl;
    std::cout << "Numero inst. Tipo J: " << contagem[5] << " Percentual: " << ((contagem[5]/totalInstrucoes)*100) << " %" << std::endl;
    std::cout << "Contagem total de instrucoes: " << totalInstrucoes << std::endl;
    std::cout << "CPI medio programa: " << cpiMedioPrograma << std::endl;

}

int conversorBinUnsignedInt(std::string bin){
    return std::stoi(bin, nullptr, 2);
}

int conversorBinSignedInt(std::string bin) {
    int contador = 0;
    int size = bin.size();
    for(int i = 0; i < size; i++) {
        int p = bin.at(i) - '0';
        if(i == 0) p *= -1;
        contador += p * std::pow(2, size-i-1);
    }
    return contador;
}

std::string conversorHexBin(std::string hex) {

    std::string bin = "";

    for (char c : hex) {
        switch (std::toupper(c)) 
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

int hexToInt(std::string hex){
    return std::stoi(hex, nullptr, 16);
}