#ifndef UTILS_H
#define UTILS_H

#include "string"
#include <vector>

void contarTipoInst(std::string instTipo, float *contagem);
void geradorEstatistica(float *contagem, float *cpi, int totalInstrucoes);

#endif