#ifndef DECODIFICADOR_H
#define DECODIFICADOR_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

std::vector<std::string> decodificaTipo(std::string instrucaoBin);
std::vector<std::string> decodificaTipoR(std::string instrucaoBin);
std::vector<std::string> decodificaTipoI(std::string instrucaoBin);
std::vector<std::string> decodificaTipoS(std::string instrucaoBin);
std::vector<std::string> decodificaTipoB(std::string instrucaoBin);
std::vector<std::string> decodificaTipoU(std::string instrucaoBin);
std::vector<std::string> decodificaTipoJ(std::string instrucaoBin);

/*
Saidas:
0 -> Binario
1 -> Formato (Tipo R, I, S, B, U, J)
2 -> mnemonico (add, sub, sll, sli, addi)
3 -> rd
4 -> rs1
5 -> rs2
6 -> imm
7 -> funct3
8 -> funct7
*/

inline std::map<std::string, std::string> mnemonicoTipoR = {
    {"000000000", "add"},
    {"000010000", "sub"},
    {"001000000", "sll"},
    {"000000010", "slt"},
    {"000000011", "sltu"},
    {"000000100", "xor"},
    {"000000101", "srl"},
    {"010000101", "sra"},
    {"000000110", "or"},
    {"000000111", "and"}
};



#endif