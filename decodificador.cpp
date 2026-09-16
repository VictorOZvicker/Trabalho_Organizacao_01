#include "decodificador.h"
#include <format>

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

std::vector<std::string> criaSaida(std::string instrucaoBin, std::string tipo, std::string mnemonico, 
    std::string rd, std::string rs1, std::string rs2, std::string imm, std::string funct3, std::string funct7) {
    

    std::string rd_out   = achaRegister(rd);
    std::string rs1_out  = achaRegister(rs1);
    std::string rs2_out  = achaRegister(rs2);

    std::string assembly = std::format("{} {}, {}, {}", mnemonico, rd, rs1, rs2);

    if(mnemonico == "add" && rd_out == "zero") assembly = "nop";

    std::vector<std::string> saida = {
        instrucaoBin,
        tipo,
        mnemonico,
        rd_out,
        rs1_out,
        rs2_out,
        imm,
        funct3,
        funct7,
        assembly
    };

    return saida;
}

std::vector<std::string> criaSaidaI(std::string instrucaoBin, std::string tipo, std::string mnemonico, 
    std::string rd, std::string rs1, std::string imm, std::string funct3) {
    

    std::string rd_out  = achaRegister(rd);
    std::string rs1_out = achaRegister(rs1);

    std::string assembly = std::format("{} {}, {}, {}", mnemonico, rd, rs1, conversorBinInt(imm));

    if(mnemonico == "addi" && rd_out == "zero") assembly = "nop";
    if(mnemonico == "jalr" && rd_out == "zero") assembly = "ret";

    std::vector<std::string> saida = {
        instrucaoBin,
        tipo,
        mnemonico,
        rd_out,
        rs1_out,
        "(sem rs2)",
        imm,
        funct3,
        "(sem funct7)",
        assembly
    };

    return saida;
}

std::vector<std::string> criaSaida(std::string instrucaoBin, std::string tipo, std::string mnemonico, 
    std::string rs1, std::string rs2, std::string imm, std::string funct3) {
    

    std::string rs1_out  = achaRegister(rs1);
    std::string rs2_out  = achaRegister(rs2);

    std::vector<std::string> saida = {
        instrucaoBin,
        tipo,
        mnemonico,
        "(sem rd)",
        rs1_out,
        rs2_out,
        imm,
        funct3,
        "(sem funct7)",
        std::format("{} {}, {}, {}", mnemonico, rs1, rs2, construtorImm({imm}))
    };

    return saida;
}

std::vector<std::string> criaSaida(std::string instrucaoBin, std::string tipo, std::string mnemonico, 
    std::string rd, std::string imm) {
    

    std::string rd_out  = achaRegister(rd);

    std::vector<std::string> saida = {
        instrucaoBin,
        tipo,
        mnemonico,
        rd_out,
        "(sem rs1)",
        "(sem rs2)",
        imm,
        "(sem funct3)",
        "(sem funct7)",
        std::format("{} {}, {}", mnemonico, rd, conversorBinInt(imm))
    };

    return saida;
}

std::vector<std::string> decodificaTipoR(std::string instrucaoBin, std::string opcode) {
    
    std::string funct7             = instrucaoBin.substr(0, 7);
    std::string rs2                = instrucaoBin.substr(7, 5);
    std::string rs1                = instrucaoBin.substr(12, 5);
    std::string funct3             = instrucaoBin.substr(17, 3);
    std::string rd                 = instrucaoBin.substr(20, 5);

    std::string mnemonico          = achaMnemonico(funct7, opcode, funct3);

    std::vector<std::string> saida = criaSaida(instrucaoBin, "R", mnemonico, rd, rs1, rs2, "", funct3, funct7);

    return saida;
}

std::vector<std::string> decodificaTipoI(std::string instrucaoBin, std::string opcode) {
    
    std::string imm11_0            = instrucaoBin.substr(0, 12);
    std::string rs1                = instrucaoBin.substr(12, 5);
    std::string funct3             = instrucaoBin.substr(17, 3);
    std::string rd                 = instrucaoBin.substr(20, 5);

    std::string mnemonico          = achaMnemonico("0000000", opcode, funct3);

    std::vector<std::string> saida = criaSaidaI(instrucaoBin, "I", mnemonico, rd, rs1, imm11_0, funct3);

    return saida;
}

std::vector<std::string> decodificaTipoS(std::string instrucaoBin, std::string opcode) {
    
    std::string imm11_5            = instrucaoBin.substr(0, 7);
    std::string rs2                = instrucaoBin.substr(7, 5);
    std::string rs1                = instrucaoBin.substr(12, 5);
    std::string funct3             = instrucaoBin.substr(17, 3);
    std::string imm4_0             = instrucaoBin.substr(20, 5);

    std::string mnemonico          = achaMnemonico("0000000", opcode, funct3);

    std::string immCompleto        = construtorImm({imm11_5, imm4_0});

    std::vector<std::string> saida = criaSaida(instrucaoBin, "S", mnemonico, rs1, rs2, immCompleto, funct3);

    return saida;
}

std::vector<std::string> decodificaTipoB(std::string instrucaoBin, std::string opcode) {
    
    std::string imm12              = instrucaoBin.substr(0, 1);
    std::string imm10_5            = instrucaoBin.substr(1, 5);
    std::string rs2                = instrucaoBin.substr(7, 4);
    std::string rs1                = instrucaoBin.substr(12, 4);
    std::string funct3             = instrucaoBin.substr(17, 3);
    std::string imm4_1             = instrucaoBin.substr(20, 3);
    std::string imm11              = instrucaoBin.substr(24, 1);

    std::string mnemonico          = achaMnemonico("0000000", opcode, funct3);

    std::string immCompleto        = construtorImm({imm12, imm11, imm10_5, imm4_1, "0"});

    std::vector<std::string> saida = criaSaida(instrucaoBin, "B", mnemonico, rs1, rs2, immCompleto, funct3);

    return saida;
}

std::vector<std::string> decodificaTipoU(std::string instrucaoBin, std::string opcode) {

    std::string imm                = instrucaoBin.substr(0, 20);
    std::string rd                 = instrucaoBin.substr(20, 5);

    std::string mnemonico          = (opcode == "0110111") ? "lui" : "auipc";

    std::vector<std::string> saida = criaSaida(instrucaoBin, "U", mnemonico, rd, imm);
    
    return saida;
}

std::vector<std::string> decodificaTipoJ(std::string instrucaoBin, std::string opcode) {
    
    std::string imm20              = instrucaoBin.substr(0, 1);
    std::string imm10_1            = instrucaoBin.substr(1, 10);
    std::string imm11              = instrucaoBin.substr(11, 1);
    std::string imm19_12           = instrucaoBin.substr(12, 8);
    std::string rd                 = instrucaoBin.substr(20, 5);

    std::string mnemonico          = "jal";

    std::string immCompleto        = construtorImm({imm20, imm19_12, imm11, imm10_1 , "0"});

    std::vector<std::string> saida = criaSaida(instrucaoBin, "J", mnemonico, rd, immCompleto);

    return saida;
}