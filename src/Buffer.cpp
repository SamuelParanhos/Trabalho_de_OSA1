#include "Buffer.hpp"
#include <sstream>

Registro Buffer::lerRegistro(ifstream& in)
{
    Registro registro;
    string linha;

    getline(in, linha);
    stringstream ss(linha);
    string nome, idade;

    getline(ss,nome,',');
    getline(ss,idade,'\n');

    registro.nome = nome;
    registro.idade = stoi(idade);
           
    return registro;
    
}
Registro Buffer::lerRegistroFixo(ifstream &in)
{
    Registro registro;
    string linha;

    getline(in,linha);

    while(getline(in, linha)){
        stringstream ss(linha);
        string nome, idade;

        getline(ss,nome,',');
        getline(ss,idade,'\n');

        registro.nome = nome;
        registro.idade = stoi(idade);
           
    }

    return registro;
    
}

void Buffer::escreverRegistroFixo(Registro reg, ofstream& out)
{
    string binario = reg.packFixed();

    out << binario;
}

