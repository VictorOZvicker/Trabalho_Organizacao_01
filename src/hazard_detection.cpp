#include "hazard_detection.h"

using namespace std;

void hazardDetection(No* atual);
void nopInsertion(ListaInstrucoes* lista);

vector<Instruction> resolucaoNop(std::vector<Instruction> program) {
    ListaInstrucoes* lista = criarLista();

    for (int i = 0; i < program.size(); i++)
        inserirFim(lista, &program[i]);

    hazardDetection(lista->inicio);
    nopInsertion(lista);
    imprimirLista(lista);
    
    return program;
}

void hazardDetection(No* atual) {
    if (atual->proximo == NULL) return;
    hazardDetection(atual->proximo);

    if (atual->inst->formato == "S") return;

    No* inst1 = atual->proximo;
    No* inst2 = NULL;
    if (inst1->proximo != NULL) inst2 = inst1->proximo;
       
    if (inst1->inst->rs1 == atual->inst->rd || inst1->inst->rs2 == atual->inst->rd)
    {   
        if (atual->inst->formato == "B")
            atual->nivelHazard += 1;
        else
            atual->nivelHazard += 2;

        if (inst2 != NULL) {
             if (inst2->inst->rs1 == atual->inst->rd || inst2->inst->rs2 == atual->inst->rd)
                atual->nivelHazard++;
        }
    }
}

void nopInsertion(ListaInstrucoes* lista) {
    No* atual = lista->inicio;

    while (atual != NULL)
    {   
        if (atual->nivelHazard == 1){   
            Instruction* nopInstruction = new Instruction(nop());  
            inserirDepois(lista, atual, nopInstruction);
        } 

        if (atual->nivelHazard >= 2) {
            Instruction* nopInstruction1 = new Instruction(nop());
            Instruction* nopInstruction2 = new Instruction(nop()); 
            inserirDepois(lista, atual, nopInstruction1);
            inserirDepois(lista, atual, nopInstruction2);
        }    
        
        atual = atual->proximo;
    }
}
