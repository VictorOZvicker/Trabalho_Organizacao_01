#ifndef LER_ARQUIVO_H
#define LER_ARQUIVO_H

#include <vector>
#include <string>

std::vector<std::vector<std::string>> linhasLidas(std::string path);

std::string conversorHexBin(std::string hex);
std::string formatadorInst(std::string str);

#endif