#include <iostream>
#include <fstream>
#include <format>
#include "ler_arquivo.h"

std::vector<std::vector<std::string>> linhasLidas(std::string path) {
    std::ifstream arquivo(path);

    std::string linha;
    std::vector<std::vector<std::string>> linhas;

    int pc = 0;
    while (std::getline(arquivo, linha))
    {   
        
        //falta verificar se instrução é valida e ignorar comentarios e linhas em branco

        if (linha.find("0x") != std::string::npos) { 
            linha.erase(0, 2);
            linhas.push_back({std::format("{:#x}", pc), std::format("{:032b}", std::stoul(linha, nullptr, 16))});            
        }
        else {
            linhas.push_back({std::format("{:#x}", pc), linha});
        }

        pc += 4;
        
    }

    arquivo.close();

    return linhas;
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



void decodificaTipo(std::string instrucaoBin) {
    
    std::string opcode = instrucaoBin.substr(25, 7);

    if (opcode == "0110011") {
        decodificaTipoR(instrucaoBin);
    }
    else if (opcode == "0010011" || opcode == "0000011" || opcode == "1100111") {
        decodificaTipoI(instrucaoBin);
    }
    else if (opcode == "0100011") {
        decodificaTipoS(instrucaoBin);
    }
    else if (opcode == "1100011") {
        decodificaTipoB(instrucaoBin);
    }
    else if (opcode == "0110111" || opcode == "0010111") {
        decodificaTipoU(instrucaoBin);
    }
    else if (opcode == "1101111") {
        decodificaTipoJ(instrucaoBin);
    }
    else {
        std::cout << "Operacao invalida: Opcode = " << opcode << "\n";
    }

}

void decodificaTipoR(std::string instrucaoBin) {
    
    std::string funct7    = instrucaoBin.substr(0, 7);
    std::string rs2       = instrucaoBin.substr(7, 5);
    std::string rs1       = instrucaoBin.substr(12, 5);
    std::string funct3    = instrucaoBin.substr(17, 3);
    std::string rd        = instrucaoBin.substr(20, 5);
    std::string opcode    = instrucaoBin.substr(25, 7);
}

void decodificaTipoI(std::string instrucaoBin) {
    std::string imm11_0   = instrucaoBin.substr(0, 12);
    std::string rs1       = instrucaoBin.substr(12, 5);
    std::string funct3    = instrucaoBin.substr(17, 3);
    std::string rd        = instrucaoBin.substr(20, 5);
    std::string opcode    = instrucaoBin.substr(25, 7);
}

void decodificaTipoS(std::string instrucaoBin) {
    std::string imm11_5   = instrucaoBin.substr(0, 7);
    std::string rs2       = instrucaoBin.substr(7, 5);
    std::string rs1       = instrucaoBin.substr(12, 5);
    std::string funct3    = instrucaoBin.substr(17, 3);
    std::string imm4_0    = instrucaoBin.substr(20, 5);
    std::string opcode    = instrucaoBin.substr(25, 7);
}

void decodificaTipoB(std::string instrucaoBin) {
    
    std::string imm12     = instrucaoBin.substr(0, 1);
    std::string imm10_5   = instrucaoBin.substr(1, 5);
    std::string rs2       = instrucaoBin.substr(7, 4);
    std::string rs1       = instrucaoBin.substr(12, 4);
    std::string funct3    = instrucaoBin.substr(17, 3);
    std::string imm4_1    = instrucaoBin.substr(20, 3);
    std::string imm11     = instrucaoBin.substr(24, 1);
    std::string opcode    = instrucaoBin.substr(25, 7);

}

void decodificaTipoU(std::string instrucaoBin) {

    std::string imm       = instrucaoBin.substr(0, 20);
    std::string rd        = instrucaoBin.substr(20, 5);
    std::string opcode    = instrucaoBin.substr(25, 7);
}

void decodificaTipoJ(std::string instrucaoBin) {
    
    std::string imm20     = instrucaoBin.substr(0, 1);
    std::string imm10_1   = instrucaoBin.substr(1, 10);
    std::string imm11     = instrucaoBin.substr(11, 1);
    std::string imm19_12  = instrucaoBin.substr(12, 8);
    std::string rd        = instrucaoBin.substr(20, 5);
    std::string opcode    = instrucaoBin.substr(25, 7);
}