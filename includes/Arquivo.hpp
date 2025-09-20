#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <vector>
#include "Registro.hpp"

using namespace std;

class Arquivo
{
public:
    string nomeDoArquivo;

public:
    Arquivo() = default;

    vector<Registro> lerRegistrosCSV();
    void adicionarRegistroFixo(const vector<Registro>& reg);
    vector<Registro> lerRegistroFixo();
    void display(vector<Registro>& reg);
};

#endif