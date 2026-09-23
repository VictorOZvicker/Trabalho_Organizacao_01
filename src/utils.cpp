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