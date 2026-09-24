#include <iostream>
#include "utils.h"

using namespace std;

int main()
{

    string path;

    cout << "Digite o nome do arquivo (com extensao)." << endl;
    cin >> path;

    if(!gerarOutput(path)) return 0;
    
    cout << "Arquivo de saida gerado com sucesso. (output.txt)";

    return 0;
}