#include <iostream>
#include <fstream>
#include "ler_arquivo.h"

std::vector<std::string> linhasLidas(std::string path) {
    std::ifstream arquivo(path);
    
    std::string linha;
    std::vector<std::string> linhas;
    while (std::getline(arquivo, linha))
    {
        linhas.push_back(linha);
    }

    arquivo.close();

    return linhas;
}

std::string conversorHexBin(std::string hex) {
    if (hex.find("0x") == -1) { return ""; }
    
    std::string hexCru = hex.erase(0, 1);
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
