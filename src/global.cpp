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

No *_criarNo(Instruction *inst) {
    No *no = (No*)calloc(1, sizeof(No));

    no->inst        = inst;
    no->anterior    = NULL;
    no->proximo     = NULL;
    no->nivelHazard = 0;

    return no;
}

ListaInstrucoes* criarLista() {
    ListaInstrucoes *lista = (ListaInstrucoes*)calloc(1, sizeof(ListaInstrucoes));
    lista->inicio          = NULL;
    lista->fim             = NULL;
    lista->tamanho         = 0;

    return lista;
}


void inserirFim(ListaInstrucoes* lista, Instruction* inst) {
    No *novoNo = _criarNo(inst);
    if (novoNo == NULL) return;

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

bool inserirDepois(ListaInstrucoes *lista, No* noAtual, Instruction* inst) {
    if (lista == NULL) return false;
    if (noAtual == NULL) return false;

    No* novoNo = _criarNo(inst);

    if (noAtual->proximo != NULL) {
        novoNo->proximo = noAtual->proximo;
        noAtual->proximo->anterior = novoNo;
    }
        
    novoNo->anterior = noAtual;
    noAtual->proximo = novoNo;

    lista->tamanho++;

    return true;
}


std::string imprimirLista(ListaInstrucoes* lista) {
    No* noAtual = lista->inicio;

    std::string output;
    while (noAtual != NULL) 
    {   

        output += noAtual->inst->assembly + "  nivel hazard: " + std::to_string(noAtual->nivelHazard) + "\n";

        noAtual = noAtual->proximo;
    }

    return output;
}