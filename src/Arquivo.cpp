#include "Arquivo.hpp"
#include "Buffer.hpp"
#include "Registro.hpp"
#include <iostream>
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
        reg = buffer.lerRegistro(newFile);
        registros.push_back(reg);
    }

    newFile.close();

    return registros;
}

void Arquivo::adicionarRegistroFixo(const vector<Registro>& reg)
{
    ofstream out("ArquivoBinario", ios::binary);
    Buffer buffer;
    
    
    for(const Registro &registro : reg)
    {
        buffer.escreverRegistroFixo(registro, out);
        
    }

    out.close();
}
vector<Registro> Arquivo::lerRegistroFixo()
{
    ifstream arquivoBinario("ArquivoBinario");
    Buffer buffer;
    Registro reg;
    string linha;
    vector<Registro> registros;

    while (arquivoBinario.peek() != EOF)
    {
        reg = buffer.lerRegistroFixo(arquivoBinario);
        registros.push_back(reg);
        cout<<"Chegou aqui"<<endl;
        display(reg);
    }

    arquivoBinario.close();

    return registros;
}

void Arquivo::display(Registro reg)
{
    cout << reg.nome << "," << reg.idade <<endl;
}