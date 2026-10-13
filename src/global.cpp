#include <global.h>

Instruction nop() {
    Instruction nop;
    
    nop.bin       = "00000000000000000000000000010011";
    nop.formato   = "R";
    nop.mnemonico = "nop";
    nop.rd        = "zero";
    nop.rs1       = "zero";
    nop.rs2       = "zero";
    nop.imm       = "";
    nop.funct3    = "000";
    nop.funct7    = "0010011";
    nop.assembly  = "\nAssembly: nop";

    return nop;
}