#include "hazard_detection.h"

using namespace std;

void hazardDetection(No* atual);
void nopInsertion(ListaInstrucoes* lista);


string resolucaoNop(const std::vector<Instruction> &program) {
    ListaInstrucoes* lista = criarLista(program);

    hazardDetection(lista->inicio);
    nopInsertion(lista);

    string output = imprimirLista(lista);
    destruirLista(lista);
    return output;
}

string resolucaoReordenacao(const std::vector<Instruction>& program) {
    ListaInstrucoes* lista = criarLista(program);

    hazardDetection(lista->inicio);

    destruirLista(lista);
    return "";
}

int detectHazardAhead(No* atual, int ahead, int hazardAhead = 0, string rd = ""){
    if(atual->proximo == NULL) return hazardAhead;
    if((atual->inst.rs1 == rd || atual->inst.rs2 == rd) && (rd != "" && rd != "zero")) return hazardAhead;
    
    return detectHazardAhead(atual->proximo, ahead-1, hazardAhead+1, rd);
}

void hazardDetection(No* atual) {
    if (atual == NULL) return;
    if (atual->proximo == NULL) return;

    atual->nivelHazard = detectHazardAhead(atual, 2, 0, atual->inst.rd);

    hazardDetection(atual->proximo);
}

void nopInsertion(ListaInstrucoes* lista) {
    No* atual = lista->fim;

    while (atual != NULL)
    {   
        for(int i = 3 - detectHazardAhead(atual, 2, 0, atual->inst.rd); i<3&&i>0; i--) inserirDepois(lista, atual, NOP);
        
        atual = atual->anterior;
    }
}

void iniciaReordenacao() {
    
    // buscar hazard
        // Buscar Candidato -> não gera hazard pra frente, não gera hazard se for realocado
            // Reordenar -> tira instrução apta e joga pra frenta da instrução com hazard.
        // NOP

    
}

void recalculoEnderecoSalto() {
    // Andar pra tras da onde a instrução foi inserida e verificar se possui um endereço positivo
    // Andar para frente e vrificar se possui instrução com endereço negativo

    // na frente com endereço positivo -> subtrai
    //
}