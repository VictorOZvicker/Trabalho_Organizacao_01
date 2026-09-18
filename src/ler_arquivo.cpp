#include <iostream>
#include <fstream>
#include <format>
#include "ler_arquivo.h"

std::vector<std::vector<std::string>> linhasLidas(std::string path) {
    std::ifstream arquivo(path);

    std::string linha;
    std::vector<std::vector<std::string>> instrucoes;

    int pc = 0;
    while (std::getline(arquivo, linha))
    {   
        int i = 0;
        while (i < linha.size())
        {
            if (linha[i] == ' ') {
                linha = linha.erase(i, 1);
            }
            else if (linha[i] == '#') {
                linha = linha.substr(0, i);
                break;
            }
            else {
                i++;
            }
        }
        linha = formatadorInst(linha);

        if (!linha.empty()) { 
            instrucoes.push_back({std::format("{:#x}", pc), linha});
            pc += 4;
        }    
    }

    arquivo.close();

    return instrucoes;
}

std::string confereBin(std::string bin) {
    if (bin.size() == 34) { 
        bin.erase(0, 2);
    }

    if (bin.find_first_not_of("01") != std::string::npos)
        return "";
    else
        return bin;
}

std::string confereHexa(std::string hex) {
    if (hex.size() == 10) {
        hex.erase(0, 2);
    }

    std::string validos = "0123456789abcdefABCDEF";
    if (hex.find_first_not_of(validos) != std::string::npos)
        return "";
    else 
        return conversorHexBin(hex);    
}

std::string formatadorInst(std::string str) {
    if (str.size() == 8 || str.size() == 10) {
        return confereHexa(str);
    }
    else if (str.size() == 32 || str.size() == 34) {
        return confereBin(str);
    }
    else {
        return "";
    }
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
