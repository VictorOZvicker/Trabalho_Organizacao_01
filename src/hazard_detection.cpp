#include "hazard_detection.h"

using namespace std;

void hazardDetection(No* atual);
void fullNopInsertion(ListaInstrucoes* lista);
void iniciaReordenacao(ListaInstrucoes* lista);
void recalculoEnderecoSalto(ListaInstrucoes* lista);

string resolucaoNop(const std::vector<Instruction> &program) {
    ListaInstrucoes* lista = criarLista(program);

    hazardDetection(lista->inicio);
    fullNopInsertion(lista);
    recalculoEnderecoSalto(lista);

    string output = imprimirLista(lista);
    destruirLista(lista);
    return output;
}

string resolucaoReordenacao(const std::vector<Instruction>& program) {
    ListaInstrucoes* lista = criarLista(program);

    hazardDetection(lista->inicio);

    iniciaReordenacao(lista);
    recalculoEnderecoSalto(lista);

    string output = imprimirLista(lista);
    destruirLista(lista);
    
    return output;
}

int detectHazardAhead(No* atual, string rd = "", int hazardAhead = 1, string formato = "") {
    if(atual == NULL || hazardAhead > 2) return 0;
    if (formato == "B" || formato == "J") return 2;
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
    for(int i = 3 - detectHazardAhead(atual->proximo, atual->inst.rd, 1, atual->inst.formato); i<3&&i>0; i--) inserirDepois(lista, atual, NOP);
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

void recalculoEnderecoSalto(ListaInstrucoes* lista) {
    No* atual = lista->inicio;
    while(atual)
    {
        if (atual->inst.formato == "B" || atual->inst.formato == "J")
        {   
            int i = 0, nopCount = 0;
            int imm = stoi(atual->inst.imm);

            if (imm < 0) 
            {
                int n = imm/(-4);
                No* anterior = atual->anterior;
                while (i < n)
                {
                    if (anterior->inst.mnemonico == "nop") nopCount--;
                    else i++;
                    
                    anterior = anterior->anterior;
                }
            }
            else if (imm > 0) 
            {
                int n = imm/4;
                No* proximo = atual->proximo;
                while (i < n)
                {
                    if (proximo->inst.mnemonico == "nop") nopCount++; 
                    else i++; 
                    
                    proximo = proximo->proximo;
                }
            }

            string newimm = to_string(imm + nopCount*4);

            i = atual->inst.assembly.find_last_of(",");
            atual->inst.assembly.erase(i);

            atual->inst.imm = newimm;
            atual->inst.assembly += format(", {}", newimm);
        }

        atual = atual->proximo;
    }
}