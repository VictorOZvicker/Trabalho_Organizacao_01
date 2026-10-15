#include "hazard_detection.h"

using namespace std;


int hazardDetection(vector<Instruction> program, int currInst, int psize);

vector<Instruction> resolucaoNop(vector<Instruction> program) {

    int psize = program.size();

    vector<Instruction> newOrder;

    for(int pc=0; pc < psize; pc++){
        if(program.at(pc).rd == "zero") {continue;}
        
        newOrder.push_back(program.at(pc));

        for(int e = 3 - hazardDetection(program, pc, psize); e > 0; e--){ 
            newOrder.push_back(nop());
        }

    }
    
    return newOrder;
}

int hazardDetection(vector<Instruction> program, int currInst, int psize) {
    
    if(program.at(currInst).formato == "B" || program.at(currInst).formato == "J") return 1;

    for(int i=1; i < 3; i++) {
        if(currInst + i >= psize) break;

        if(program.at(currInst + i).rs1 == program.at(currInst).rd || program.at(currInst + i).rs2 == program.at(currInst).rd) 
            return i;
    }

    return 3;
}
