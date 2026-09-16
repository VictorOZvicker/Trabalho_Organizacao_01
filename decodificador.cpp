#include "decodificador.h"

int conversorBinInt(std::string bin) {
    return std::stoi(bin, nullptr, 2);
}

std::vector<std::string> decodificaTipo(std::string instrucaoBin, std::string opdcode) {
    
    std::string opcode = instrucaoBin.substr(25, 7);

    if (opcode == "0110011") {
        decodificaTipoR(instrucaoBin,opcode);
    }
    else if (opcode == "0010011" || opcode == "0000011" || opcode == "1100111" || opcode == "1110011") {
        decodificaTipoI(instrucaoBin,opcode);
    }
    else if (opcode == "0100011") {
        decodificaTipoS(instrucaoBin,opcode);
    }
    else if (opcode == "1100011") {
        decodificaTipoB(instrucaoBin,opcode);
    }
    else if (opcode == "0110111" || opcode == "0010111") {
        decodificaTipoU(instrucaoBin,opcode);
    }
    else if (opcode == "1101111") {
        decodificaTipoJ(instrucaoBin,opcode);
    }
    else {
        std::cout << "Operacao invalida: Opcode = " << opcode << "\n";
    }
}

std::string achaMnemonico(std::string funct7, std::string opcode, std::string funct3) {

    auto it = mnemonicos.find((funct7 + opcode + funct3));
    if (it != mnemonicos.end()) 
        return it->second;
     else 
        return "<ERRO>";

}

std::string achaRegister(std::string regBin) {
    auto it = registers.find(conversorBinInt(regBin));
    if (it != registers.end()) 
        return it->second;
     else 
        return "<ERRO>";
}

std::string construtorImm(std::vector<std::string> pedacosImm) {
    std::string immCompleto = "";
    for (std::string s : pedacosImm) {
        immCompleto += s;
    }

    return immCompleto;
}


std::vector<std::string> decodificaTipoR(std::string instrucaoBin, std::string opcode) {
    
    std::string funct7      = instrucaoBin.substr(0, 7);
    std::string rs2         = instrucaoBin.substr(7, 5);
    std::string rs1         = instrucaoBin.substr(12, 5);
    std::string funct3      = instrucaoBin.substr(17, 3);
    std::string rd          = instrucaoBin.substr(20, 5);

    std::string mnemonico   = achaMnemonico(funct7, opcode, funct3);

    std::vector<std::string> saida = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };

    return saida;
}

std::vector<std::string> decodificaTipoI(std::string instrucaoBin, std::string opcode) {
    
    std::string imm11_0     = instrucaoBin.substr(0, 12);
    std::string rs1         = instrucaoBin.substr(12, 5);
    std::string funct3      = instrucaoBin.substr(17, 3);
    std::string rd          = instrucaoBin.substr(20, 5);

    std::string mnemonico   = achaMnemonico("0000000", opcode, funct3);

    std::vector<std::string> saida = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };

    return saida;
}

std::vector<std::string> decodificaTipoS(std::string instrucaoBin, std::string opcode) {
    
    std::string imm11_5     = instrucaoBin.substr(0, 7);
    std::string rs2         = instrucaoBin.substr(7, 5);
    std::string rs1         = instrucaoBin.substr(12, 5);
    std::string funct3      = instrucaoBin.substr(17, 3);
    std::string imm4_0      = instrucaoBin.substr(20, 5);

    std::string mnemonico   = achaMnemonico("0000000", opcode, funct3);

    std::string immCompleto = construtorImm({imm11_5, imm4_0});

    std::vector<std::string> saida = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };

    return saida;
}

std::vector<std::string> decodificaTipoB(std::string instrucaoBin, std::string opcode) {
    
    std::string imm12       = instrucaoBin.substr(0, 1);
    std::string imm10_5     = instrucaoBin.substr(1, 5);
    std::string rs2         = instrucaoBin.substr(7, 4);
    std::string rs1         = instrucaoBin.substr(12, 4);
    std::string funct3      = instrucaoBin.substr(17, 3);
    std::string imm4_1      = instrucaoBin.substr(20, 3);
    std::string imm11       = instrucaoBin.substr(24, 1);

    std::string mnemonico   = achaMnemonico("0000000", opcode, funct3);

    std::string immCompleto = construtorImm({imm12, imm11, imm10_5, imm4_1, "0"});

    std::vector<std::string> saida = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };

    return saida;
}

std::vector<std::string> decodificaTipoU(std::string instrucaoBin, std::string opcode) {

    std::string imm         = instrucaoBin.substr(0, 20);
    std::string rd          = instrucaoBin.substr(20, 5);

    std::string mnemonico   = (opcode == "0110111") ? "lui" : "auipc";

    std::vector<std::string> saida = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };
    
    return saida;
}

std::vector<std::string> decodificaTipoJ(std::string instrucaoBin, std::string opcode) {
    
    std::string imm20       = instrucaoBin.substr(0, 1);
    std::string imm10_1     = instrucaoBin.substr(1, 10);
    std::string imm11       = instrucaoBin.substr(11, 1);
    std::string imm19_12    = instrucaoBin.substr(12, 8);
    std::string rd          = instrucaoBin.substr(20, 5);

    std::string mnemonico   ="jal";

    std::string immCompleto = construtorImm({imm20, imm19_12, imm11, imm10_1 , "0"});

    std::vector<std::string> saida = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };

    return saida;
}