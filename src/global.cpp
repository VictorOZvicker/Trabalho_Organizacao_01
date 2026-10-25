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

No *_criarNo(const Instruction& inst) {
    return new No{inst, nullptr, nullptr, 0};
}

ListaInstrucoes* criarLista(const std::vector<Instruction>& program) {
    ListaInstrucoes *lista = new ListaInstrucoes{nullptr, nullptr, 0};

    for (const Instruction& inst : program)
        inserirFim(lista, inst);

    return lista;
}


void inserirFim(ListaInstrucoes* lista, const Instruction& inst) {
    No *novoNo = _criarNo(inst);

    if (lista->inicio == NULL) {
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        lista->fim->proximo = novoNo;
        novoNo->anterior = lista->fim;
        lista->fim = novoNo;
    }

    lista->tamanho++;
}

bool inserirDepois(ListaInstrucoes *lista, No* noAtual, const Instruction& inst) {
    if (lista == NULL) return false;
    if (noAtual == NULL) return false;

    No* novoNo = _criarNo(inst);

    if (noAtual->proximo != NULL) {
        novoNo->proximo = noAtual->proximo;
        noAtual->proximo->anterior = novoNo;
    } else {
        lista->fim = novoNo;
    }
        
    novoNo->anterior = noAtual;
    noAtual->proximo = novoNo;

    lista->tamanho++;

    return true;
}

bool desvincularNo(ListaInstrucoes* lista, No* no){
    if (lista == NULL) return false;

    No* noAtual = lista->inicio;

    while(noAtual != NULL){
        if(noAtual != no){
            noAtual = noAtual->proximo;
            continue;
        }
        noAtual->anterior->proximo = noAtual->proximo;
        noAtual->proximo->anterior = noAtual->anterior;
        if(lista->inicio == noAtual) lista->inicio = noAtual->proximo;
        if(lista->fim == noAtual) lista->fim = noAtual->anterior;
        lista->tamanho--;
        return true;
    }
    return false;
}

void destruirLista(ListaInstrucoes* lista) {
    if (lista == NULL) return;

    No* noAtual = lista->inicio;
    while (noAtual != NULL) {
        No* proximo = noAtual->proximo;
        delete noAtual;
        noAtual = proximo;
    }

    delete lista;
}


std::string imprimirLista(ListaInstrucoes* lista) {
    if (lista == NULL) return "";

    No* noAtual = lista->inicio;

    std::string output;
    while (noAtual != NULL) 
    {   

        output += noAtual->inst.assembly + "  nivel hazard: " + std::to_string(noAtual->nivelHazard) + "\n";

        noAtual = noAtual->proximo;
    }

    return output;
}