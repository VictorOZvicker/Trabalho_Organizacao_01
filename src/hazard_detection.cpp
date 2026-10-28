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
    if(formato == "B" || formato == "J") return 2;
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


/* bool verificarIndependencia(No* comparador, No* atual){

    if(comparador == NULL || comparador->inst.mnemonico == "nop") return false;

    if(atual->inst.mnemonico == "lw" && comparador->inst.formato == "S") return true;

    if((comparador->inst.rs1 == atual->inst.rd && atual->inst.rd != "") || (comparador->inst.rs2 == atual->inst.rd && atual->inst.rd != "" ) || (comparador->inst.rd == atual->inst.rs1 && atual->inst.rs1 != "") || (comparador->inst.rd == atual->inst.rs2 && atual->inst.rs2 != ""))
    {
        cout << comparador->inst.assembly << " -> comparador" << endl;
        return false;
    } 

    return true;
}   


bool instIndependente(No* comparador, No* atual, int range) {
    if (comparador == NULL || range < 0) return true;

    return verificarIndependencia(comparador, atual) &&
    instIndependente(comparador->anterior, atual, --range);
} */

bool verificarIndependencia(No* atual, No* candidato) {
    
    while (candidato != atual)
    {   
        if(candidato == NULL || candidato->inst.mnemonico == "nop") return false;


        else if((candidato->inst.rd != atual->inst.rs1) && (candidato->inst.rd != atual->inst.rs2)
        && (candidato->inst.rs1 != atual->inst.rd ) && (candidato->inst.rs2 != atual->inst.rd))
        {
            cout << "(" << candidato->inst.assembly << " -> candidato" << endl;
            return true;
        } 

        candidato = candidato->anterior;
    }

    return false;
}

bool instIndependente(No* atual, No* candidato, int range) {
    //if (comparador == NULL || range < 0) return true;

    return verificarIndependencia(atual, candidato);
}

No* acharCandidato(No* atual){

    int range = 0;
    No* candidato = atual->proximo;
    while (candidato)
    {
        if (instIndependente(atual, candidato, range++)) {
            return candidato;
        } 
        candidato = candidato->proximo;
    }

    return NULL;
}
    

void reordenar(ListaInstrucoes* lista, No* atual, No* candidato){
    
    desvincularNo(lista, candidato);
    inserirDepois(lista, atual, candidato->inst);
}

void iniciaReordenacao(ListaInstrucoes* lista) {

    No* atual = lista->inicio;

    while(atual != NULL){
        if(atual->nivelHazard > 0){
            No* comecoBusca = atual->proximo;
            No* candidato   = acharCandidato(comecoBusca);
            if(candidato){
                cout << atual->inst.assembly << " -> ATUAL" << endl << ")" << endl;
                reordenar(lista, atual, candidato);
            }
        }
        atual = atual->proximo;
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