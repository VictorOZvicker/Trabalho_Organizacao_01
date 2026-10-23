#include "hazard_detection.h"

using namespace std;

void hazardDetection(ListaInstrucoes* lista, No* atual);
void nopInsertion(ListaInstrucoes* lista);

string resolucaoNop(std::vector<Instruction> program) {
    ListaInstrucoes* lista = criarLista();

    for (int i = 0; i < program.size(); i++)
        inserirFim(lista, &program[i]);

    hazardDetection(lista, lista->inicio);
    nopInsertion(lista);
    
    return imprimirLista(lista);
}

void hazardDetection(ListaInstrucoes* lista, No* atual) {
    if (atual->proximo == NULL) return;
    hazardDetection(lista, atual->proximo);

    No* inst1 = atual->proximo;
    No* inst2 = NULL;
    if (inst1->proximo != NULL) inst2 = inst1->proximo;
    
    if (atual->inst->formato == "S") return;

    if (inst1->inst->rs1 == atual->inst->rd || inst1->inst->rs2 == atual->inst->rd)
    {   
        if (atual->inst->formato == "B" || atual->inst->formato == "J") {
            atual->nivelHazard += 2;
            return;
        }
        else {
            atual->nivelHazard++;
            return;
        }
    }

    if (inst2 != NULL) {
        if (inst2->inst->rs1 == atual->inst->rd || inst2->inst->rs2 == atual->inst->rd) {
            atual->nivelHazard += 2;
            return;
        }
            
    }
}

void nopInsertion(ListaInstrucoes* lista) {
    No* atual = lista->inicio;

    while (atual != NULL)
    {   
        for(int i = 3 - atual->nivelHazard; i<3&&i>0; i--) inserirDepois(lista, atual, &NOP);
        
        atual = atual->proximo;
    }
}
