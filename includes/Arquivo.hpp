#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <vector>
#include "Registro.hpp"

class Arquivo
{
private:
    std::string nomeDoArquivo;

public:
    Arquivo() = default;
    void SetNomeDoArquivo(std::string nome);
    std::vector<Registro> lerRegistrosCSV();
    void adicionarRegistroFixo(Registro reg);
    std::vector<Registro> lerRegistrosFixo();
};

#endif