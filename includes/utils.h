#ifndef UTILS_H
#define UTILS_H

#include "string"
#include <vector>
#include <cmath>

void contarTipoInst(std::string instTipo, float *contagem);
void geradorEstatistica(float *contagem, float *cpi, int totalInstrucoes);


int conversorBinSignedInt(std::string bin);
int conversorBinUnsignedInt(std::string bin);
std::string conversorHexBin(std::string hex);
int hexToInt(std::string hex);

#endif