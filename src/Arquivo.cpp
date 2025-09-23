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

    getline(newFile, linha); // Lê o cabeçalho

    // Este loop lê uma linha, mas a função chamada dentro dele lê OUTRA
    while (getline(newFile, linha))
    {
        reg = buffer.lerRegistro(newFile);
        registros.push_back(reg);
    }

    newFile.close();
    return registros;
}

void Arquivo::adicionarRegistroFixo(const vector<Registro> &reg)
{
    ofstream out("ArquivoBinario", ios::binary);
    Buffer buffer;

    for (const Registro &registro : reg)
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
    // A declaração do buffer aqui é problemática, mas o erro principal é o salto
    char buffer_leitura[reg.campoRegistro + 1];
    vector<Registro> registros;

    // Este loop lê um registro, mas a função chamada dentro dele lê OUTRO
    while (arquivoBinario.read(buffer_leitura, reg.campoRegistro))
    {
        reg = buffer.lerRegistroFixo(arquivoBinario);
        registros.push_back(reg);
        display(reg);
    }

    arquivoBinario.close();
    return registros;
}

void Arquivo::display(Registro reg)
{
    cout << reg.nome << "," << reg.idade << endl;
}