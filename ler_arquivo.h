#ifndef LER_ARQUIVO_H
#define LER_ARQUIVO_H

#include <vector>
#include <string>

std::vector<std::vector<std::string>> linhasLidas(std::string path);

std::string conversorHexBin(std::string hex);

std::string instrucaoAssembly(std::string instrucaoBin);

void decodificaTipo(std::string instrucaoBin);
void decodificaTipoR(std::string instrucaoBin);
void decodificaTipoI(std::string instrucaoBin);
void decodificaTipoS(std::string instrucaoBin);
void decodificaTipoB(std::string instrucaoBin);
void decodificaTipoU(std::string instrucaoBin);
void decodificaTipoJ(std::string instrucaoBin);

#endif