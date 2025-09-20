#include "Arquivo.hpp"
#include "Buffer.hpp"
#include "Registro.hpp"
#include <fstream>
#include <sstream>
#include <cstring>

vector<Registro> Arquivo::lerRegistrosCSV()
{
    ifstream newFile(nomeDoArquivo);
    Buffer buffer;
    Registro reg;
    string linha;
    vector<Registro> registros;

    getline(newFile, linha);

    while (!newFile.eof())
    {
        reg = buffer.lerRegistroFixo(newFile);
        registros.push_back(reg);
    }

    newFile.close();

    return registros;
}

void Arquivo::adicionarRegistroFixo(const vector<Registro>& reg)
{
    ofstream out(nomeDoArquivo, ios::binary);
    Buffer buffer;
    
    
    for(const auto registro : reg)
    {
        buffer.escreverRegistroFixo(registro, out);
        
    }

    out.close();
}
vector<Registro> Arquivo::lerRegistroFixo()
{

}

void display(vector<Registro>& reg)
{

}