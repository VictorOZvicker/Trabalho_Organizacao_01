#include <iostream>
#include "utils.h"


void geradorEstatistica(std::string instTipo, float *contagem) {
    
    switch(instTipo.at(0)) {
        case 'R': contagem[0]++; break;
        case 'I': contagem[1]++; break;
        case 'S': contagem[2]++; break;
        case 'B': contagem[3]++; break;
        case 'U': contagem[4]++; break;
        case 'J': contagem[5]++; break;
    }
    
}