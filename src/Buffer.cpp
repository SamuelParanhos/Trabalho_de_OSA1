#include "Buffer.hpp"
#include <iostream>
#include <sstream>

Registro Buffer::lerRegistro(ifstream &in)
{
    Registro registro;
    string linha;

    getline(in, linha);
    stringstream ss(linha);
    string nome_str, idade_str;

    getline(ss, nome_str, ',');
    getline(ss, idade_str, '\n');

    registro.nome = nome_str;
    if (!idade_str.empty())
    {
        registro.idade = stoi(idade_str);
    }

    return registro;
}
Registro Buffer::lerRegistroFixo(ifstream &in)
{
    Registro registro;
    string linha;

    getline(in, linha);
    registro.unpackFixed(linha);

    return registro;
}

void Buffer::escreverRegistroFixo(Registro reg, ofstream &out)
{
    string binario = reg.packFixed();

    out << binario;
}
