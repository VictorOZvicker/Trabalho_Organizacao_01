#ifndef HAZARD_DETECTION_H
#define HAZARD_DETECTION_H

#include "global.h"

std::string resolucaoNop(const std::vector<Instruction> &program);
std::string resolucaoReordenacao(const std::vector<Instruction>& program);

#endif