#include "hazard_detection.h"

using namespace std;

void hazardDetection(No* atual);
void fullNopInsertion(ListaInstrucoes* lista);
void iniciaReordenacao(ListaInstrucoes* lista);

string resolucaoNop(const std::vector<Instruction> &program) {
    ListaInstrucoes* lista = criarLista(program);

    hazardDetection(lista->inicio);
    fullNopInsertion(lista);

    string output = imprimirLista(lista);
    destruirLista(lista);
    return output;
}

string resolucaoReordenacao(const std::vector<Instruction>& program) {
    ListaInstrucoes* lista = criarLista(program);

    hazardDetection(lista->inicio);

    iniciaReordenacao(lista);

    string output = imprimirLista(lista);
    destruirLista(lista);
    
    return output;
}

int detectHazardAhead(No* atual, string rd = "", int hazardAhead = 1){
    if(atual == NULL || hazardAhead > 2) return 0;
    if((atual->inst.rs1 == rd || atual->inst.rs2 == rd) && (rd != "" && rd != "zero")) return hazardAhead;
    
    return detectHazardAhead(atual->proximo, rd, ++hazardAhead);
}

void hazardDetection(No* atual) {
    if (atual == NULL) return;
    if (atual->proximo == NULL) return;

    atual->nivelHazard = detectHazardAhead(atual->proximo, atual->inst.rd);

    hazardDetection(atual->proximo);
}

void nopInsertion(ListaInstrucoes* lista, No* atual) {
    for(int i = 3 - detectHazardAhead(atual->proximo, atual->inst.rd); i<3&&i>0; i--) inserirDepois(lista, atual, NOP);
}

void fullNopInsertion(ListaInstrucoes* lista) {
    No* atual = lista->fim;

    while (atual != NULL)
    {   
        nopInsertion(lista, atual);
        atual = atual->anterior;
    }
}


No* acharCandidato(No* atual, string rd){

    if(atual == NULL) return NULL;

    if(atual->nivelHazard <= 0 && detectHazardAhead(atual, rd) <= 0 && atual->anterior->nivelHazard <= 0 && atual->anterior->anterior->nivelHazard <= 0) 
        return atual;

    return acharCandidato(atual->proximo, rd);
}   

void reordenar(ListaInstrucoes* lista, No* atual, No* candidato){
    
    desvincularNo(lista, candidato);
    inserirDepois(lista, atual, candidato->inst);
}

void iniciaReordenacao(ListaInstrucoes* lista) {

    No* atual = lista->fim;

    while(atual != NULL){
        if(atual->nivelHazard > 0){
            No* comecoBusca = atual;
            for(int i=3-atual->nivelHazard; i<3&&i>0; i--) comecoBusca = comecoBusca->proximo;
            No* candidato = acharCandidato(comecoBusca, atual->inst.rd);
            if(candidato != NULL){
                reordenar(lista, atual, candidato);
            }
        }
        atual = atual->anterior;
    }

    fullNopInsertion(lista);

}

void recalculoEnderecoSalto() {
    // Andar pra tras da onde a instrução foi inserida e verificar se possui um endereço positivo
    // Andar para frente e vrificar se possui instrução com endereço negativo

    // na frente com endereço positivo -> subtrai
    //
}