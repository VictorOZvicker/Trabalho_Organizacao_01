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

    No* inst1 = atual->proximo;
    No* inst2 = NULL;
    if (inst1->proximo != NULL) inst2 = inst1->proximo;
       
    if (inst1->inst->rs1 == atual->inst->rd || inst1->inst->rs2 == atual->inst->rd)
    {   
        if (atual->inst->formato == "B")
            atual->nivelHazard += 1;
        else
            atual->nivelHazard += 2;
    }

    if (inst2 != NULL) {
        if (inst2->inst->rs1 == atual->inst->rd || inst2->inst->rs2 == atual->inst->rd)
            atual->nivelHazard++;
    }
}

void nopInsertion(ListaInstrucoes* lista) {
    No* atual = lista->inicio;

    while (atual != NULL)
    {   
        if (atual->nivelHazard == 1) inserirDepois(lista, atual, &NOP);
            
        if (atual->nivelHazard >= 2) {
            inserirDepois(lista, atual, &NOP);
            inserirDepois(lista, atual, &NOP);
        }    
        
        atual = atual->proximo;
    }
}
