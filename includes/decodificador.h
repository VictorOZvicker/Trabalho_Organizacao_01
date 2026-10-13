#ifndef DECODIFICADOR_H
#define DECODIFICADOR_H


#include <global.h>


Instruction decodificaTipo(std::string instrucaoBin);


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


#endif