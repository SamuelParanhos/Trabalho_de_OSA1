#include "Arquivo.hpp"
#include "Buffer.hpp"
#include "Registro.hpp"
#include <iostream>
#include <cstring>

vector<Registro> Arquivo::lerRegistrosCSV()
{
    //Cria um novo arquivo e variáveis para auxiliar na exucação da função.
    ifstream newFile(nomeDoArquivo);
    Buffer buffer;
    Registro reg;
    string linha;
    vector<Registro> registros;

    //Usa o getline para pular o cabeçalho da função.
    getline(newFile, linha);

    //Comando de repetição usada para ler todas as linhas do arquivo CSV.
    while (getline(newFile, linha))
    {
        reg = buffer.lerRegistro(linha);
        registros.push_back(reg);
    }
    
    //Fecha o arquivo e retorna o vetor de Registro.
    newFile.close();
    return registros;
}

void Arquivo::adicionarRegistroFixo(const vector<Registro> &reg)
{
    //Cria um novo arquino
    ofstream out("ArquivoBinario", ios::binary);
    Buffer buffer;

    //Pega todos os registros coloca em uma variável temporária e escreve em um
    //arquivo binário.
    for (const Registro &registro : reg)
    {
        buffer.escreverRegistroFixo(registro, out);
    }

    //Fechamento do arquivo.
    out.close();
}
vector<Registro> Arquivo::lerRegistroFixo()
{
    //Cria um novo arquivo e variáveis auxiliares.
    ifstream arquivoBinario("ArquivoBinario");
    Buffer buffer;
    Registro reg;

    //Variável usada para armazenar um registro em formato char.
    char buffer_leitura[Registro::campoRegistro];
    vector<Registro> registros;

    //Comando de repetição para passar por todos os registros.
    while (arquivoBinario.read(buffer_leitura, reg.campoRegistro))
    {
        reg = buffer.lerRegistroFixo(buffer_leitura);
        registros.push_back(reg);
        display(reg);
    }

    //Fechamento do arquivo.
    arquivoBinario.close();
    return registros;
}

//Função usada para imprimir na tela os registros desserealizados. 
void Arquivo::display(Registro reg)
{
    cout << reg.nome << "," << reg.idade << endl;
}