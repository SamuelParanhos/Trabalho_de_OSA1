#include "includes/Registro.hpp"
#include "includes/Arquivo.hpp"

#include <iostream>

int main()
{
    Arquivo arquivo;
    Registro registro;
    vector<Registro> pimba;

    arquivo.nomeDoArquivo = "Arquivos_Nomes e Idades/Nomes_Idades_1.csv";
    pimba = arquivo.lerRegistrosCSV();
    arquivo.adicionarRegistroFixo(pimba);
    pimba = arquivo.lerRegistroFixo();
    return 0;
}