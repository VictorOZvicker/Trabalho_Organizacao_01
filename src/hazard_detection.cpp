#include "hazard_detection.h"

using namespace std;

void hazardDetection(No* atual);
void fullNopInsertion(ListaInstrucoes* lista);
void iniciaReordenacao(ListaInstrucoes* lista);
void recalculoEnderecoSalto(ListaInstrucoes* lista);

void gerarRelatorioDeCusto(float original, float solucaoNop, float solucaoReordenacao);

string resolucaoNop(const std::vector<Instruction> &program, int &numInstrucoes) {
    ListaInstrucoes* lista = criarLista(program);

    hazardDetection(lista->inicio);

    fullNopInsertion(lista);
    recalculoEnderecoSalto(lista);

    numInstrucoes = lista->tamanho;

    string output = imprimirLista(lista);
    destruirLista(lista);
    return output;
}

string resolucaoReordenacao(const std::vector<Instruction>& program, int &numInstrucoes) {
    ListaInstrucoes* lista = criarLista(program);

    hazardDetection(lista->inicio);

    iniciaReordenacao(lista);
    recalculoEnderecoSalto(lista);

    numInstrucoes = lista->tamanho;

    string output = imprimirLista(lista);
    destruirLista(lista);
    
    return output;
}

void gerarSaida(const std::vector<Instruction>& program, std::string &outputNop, std::string &outputReordenacao) {
    int numeroInstNop, numeroInstReordenacao;
    int original = program.size();

    outputNop = resolucaoNop(program, numeroInstNop);
    outputReordenacao = resolucaoReordenacao(program, numeroInstReordenacao);

    cout << original << " " << numeroInstNop << " " << numeroInstReordenacao << endl; 

    gerarRelatorioDeCusto(original, numeroInstNop, numeroInstReordenacao);
}


void gerarRelatorioDeCusto(float original, float solucaoNop, float solucaoReordenacao) {

    int difNopOriginal = solucaoNop - original;
    int difReordenacaoOriginal = solucaoReordenacao - original;

    float desempenhoNopOriginal = ((solucaoNop/original) - 1) * 100;
    float desempenhoReordenacaoNop = ((solucaoReordenacao/original) - 1) * 100;

    cout << "CUSTO" << endl;
    cout << "Original .............. " << original << " Instrucoes." << endl;
    cout << "Somente nops .......... " << solucaoNop << " Instrucoes." << "(" << "+" << difNopOriginal << ", +" << desempenhoNopOriginal << "%)" << endl;
    cout << "nops + reordenacao .... " << solucaoReordenacao << " Instrucoes." << "(" << "+" << difReordenacaoOriginal << ", +" << desempenhoReordenacaoNop << "%)" << endl;
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


bool verificaIndependenciaDeBranches(No* atual, No* candidato) {
    if (atual == NULL || candidato == NULL) return false;  

    // ESSE AQUI PEGA O INICIO DA LISTA, PODERIA SER PASSADO O LISTA->INICIO TBM, MAS DAI TEM QUE PASSAR PELOS PARAMETROS TUDO.
    No* inicio = atual;
    while (inicio->anterior != NULL) inicio = inicio->anterior;

    // ESSES AQUI COMEÇAM EM -1 PQ O ENDEREÇO MINIMO É O 0...
    int indiceAtual = -1;
    int indiceCandidato = -1;
    int indice = 0;

    // DAI NO CASO A GENTE TEM QUE VER SE ELE PODE PEGAR INSTRUÇÕES DE ANTES DO PROGRAMA

    No* noIterador = inicio;

    // ESSE AQUI É PRA ACHAR O INDICE DOS NOS, JÁ QUE A GENTE COLOCA OS ENDEREÇOS DPS
    while(noIterador){
        if(noIterador == atual) indiceAtual = indice;
        if(noIterador == candidato) indiceCandidato = indice;
        indice++;

        noIterador = noIterador->proximo;
    }

    // NÃO ACHOU O COMEÇO DA BUSCA OU O CANDIDATO TA ANTES
    //if (indiceAtual < 0 || indiceCandidato <= indiceAtual) return false;

    indice = 0;
    No* no = inicio;
    while(no != NULL) { // TEM QUE COMPLEMENTAR ESSE LOOP CERTINHO
    // NÃO PODE ESQUECER DE IR INCREMENTANDO O INDICE
        if (no->inst.formato == "B" || no->inst.formato == "J") {
            int destino = stoi(no->inst.imm)/4 + indice; // TEM QUE PEGAR O IMEDIATO

             if (destino < indice) {
                if (indiceCandidato >= destino && indiceCandidato < indice)
                    return false;
            } else if (destino > indice) {
                if (indiceCandidato > indice && indiceCandidato < destino)
                    return false;
            }

        }
        if (indice >= indiceAtual && indice < indiceCandidato &&
            (no->inst.formato == "B" || no->inst.formato == "J" ||
             no->inst.mnemonico == "jalr")) {
            return false;
        }
        no = no->proximo;
        indice++;
    }

    return true;
}


bool verificarIndependencia(No* atual, No* candidato) {

    bool independente = true;
    string candMnemonico = candidato->inst.mnemonico;

    if (verificaIndependenciaDeBranches(atual, candidato))
    {
    
    if (candMnemonico == "lw" || candMnemonico == "lh" || candMnemonico == "lb" || candMnemonico == "lhu" || candMnemonico == "lbu") {
        if (candidato->inst.rs1 == atual->inst.rd || candidato->inst.rd == atual->inst.rs1 || candidato->inst.rd == atual->inst.rs2)
            independente = false;
    }

    else if (candidato->inst.formato == "S") {
        if (candidato->inst.rs1 == atual->inst.rd || candidato->inst.rd == atual->inst.rd)
            independente = false;
    }

    else if((candidato->inst.rd == atual->inst.rs1) || (candidato->inst.rd == atual->inst.rs2) ||
            (candidato->inst.rs1 == atual->inst.rd ) || (candidato->inst.rs2 == atual->inst.rd)) independente = false;
            
    }    
    return independente;
}

bool instIndependente(No* atual, No* candidato) {

    if (!verificarIndependencia(atual, candidato)) return false;

    No* comparar = candidato->anterior;
    while (comparar != atual)
    {   
        if(comparar->inst.rd == "zero") {
            comparar = comparar->anterior;
            continue;
        }

        if (!verificarIndependencia(candidato, comparar)) return false;

        comparar = comparar->anterior;
    }

    return true;
}

No* acharCandidato(No* atual){

    int range = 0;
    No* candidato = atual->proximo;
    while (candidato)
    {
        if (instIndependente(atual, candidato)) return candidato;
        
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
            No* comecoBusca = atual;
            No* candidato   = acharCandidato(comecoBusca);

            if(candidato) reordenar(lista, atual, candidato);
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