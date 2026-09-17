#ifndef DECODIFICADOR_H
#define DECODIFICADOR_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

std::vector<std::string> decodificaTipo(std::string instrucaoBin);
std::vector<std::string> decodificaTipoR(std::string instrucaoBin, std::string opcode = "");
std::vector<std::string> decodificaTipoI(std::string instrucaoBin, std::string opcode = "");
std::vector<std::string> decodificaTipoS(std::string instrucaoBin, std::string opcode = "");
std::vector<std::string> decodificaTipoB(std::string instrucaoBin, std::string opcode = "");
std::vector<std::string> decodificaTipoU(std::string instrucaoBin, std::string opcode = "");
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
9 -> assembly
*/


/*
Para fazer a detecção de mnemonicos vamos usar o map para organizar todos eles.
Ele usa uma combinação do funct7 + opcode + funct3
para instruções sem o funct7 serão concatenados 7 0's
*/
inline std::map<std::string, std::string> mnemonicos = {
    {"00000000110011000","add"   },  // Tipos R ---
    {"01000000110011000","sub"   },
    {"00000000110011001","sll"   },
    {"00000000110011010","slt"   },
    {"00000000110011011","sltu"  },
    {"00000000110011100","xor"   },
    {"00000000110011101","srl"   },
    {"01000000110011101","sra"   },
    {"00000000110011110","or"    },
    {"00000000110011111","and"   },  // -----------
    {"00000001100011000","beq"   },  // Tipos B ---
    {"00000001100011001","bne"   },
    {"00000001100011100","blt"   },
    {"00000001100011101","bge"   },
    {"00000001100011110","bltu"  },
    {"00000001100011111","bgeu"  },  // -----------
    {"00000000000011000","lb"    },  // Tipos I ---
    {"00000000000011001","lh"    },
    {"00000000000011010","lw"    },
    {"00000000000011100","lbu"   },
    {"00000000000011101","lhu"   },
    {"00000000010011000","addi"  },
    {"00000000010011010","slti"  },
    {"00000000010011011","sltiu" },
    {"00000000010011100","xori"  },
    {"00000000010011110","ori"   },
    {"00000000010011111","andi"  },
    {"00000000010011001","slli"  },
    {"00000000010011101","srli"  },
    {"01000000010011101","srai"  },  
    {"00000001110011001","csrrw" },
    {"00000001110011010","csrrs" },
    {"00000001110011011","csrrc" },
    {"00000001110011101","csrrwi"},
    {"00000001110011110","csrrsi"},
    {"00000001110011111","csrrci"},  // -----------
    {"00000000100011000", "sb"   },  // Tipos S ---
    {"00000000100011001", "sh"   },
    {"00000000100011010", "sw"   }   // -----------
};

inline std::map<int, std::string> registers = {
    {0,  "zero"},
    {1,  "ra"  },
    {2,  "sp"  },
    {3,  "gp"  },
    {4,  "tp"  },
    {5,  "t0"  },
    {6,  "t1"  },
    {7,  "t2"  },
    {8,  "s0"  },
    {9,  "s1"  },
    {10, "a0"  },
    {11, "a1"  },
    {12, "a2"  },
    {13, "a3"  },
    {14, "a4"  },
    {15, "a5"  },
    {16, "a6"  },
    {17, "a7"  },
    {18, "s2"  },
    {19, "s3"  },
    {20, "s4"  },
    {21, "s5"  },
    {22, "s6"  },
    {23, "s7"  },
    {24, "s8"  },
    {25, "s9"  },
    {26, "s10" },
    {27, "s11" },
    {28, "t3"  },
    {29, "t4"  },
    {30, "t5"  },
    {31, "t6"  }
};

#endif