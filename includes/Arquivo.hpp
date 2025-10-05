#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <vector>
#include "Registro.hpp"

using namespace std;
template <typename T>
class Arquivo
{
public:
    string nomeDoArquivo;
    Formato formato;

public:
    Arquivo(string nome, Formato fmt)
    {
        this.nome = nome;
        this.formato = formato;
    };

    vector<T> lerRegistros()
    {
        // Cria um novo arquivo e variáveis para auxiliar na exucação da função.
        ifstream newFile(nomeDoArquivo);
        RegistroAluno registroAluno;

        Buffer buffer;
        Registro reg;
        string linha;
        vector<Registro> registros;

        // Usa o getline para pular o cabeçalho da função.
        getline(newFile, linha);

        // Comando de repetição usada para ler todas as linhas do arquivo CSV.
        while (getline(newFile, linha))
        {
            reg = buffer.lerRegistro(linha);
            registros.push_back(reg);
        }

        // Fecha o arquivo e retorna o vetor de Registro.
        newFile.close();
        return registros;
    }

    void Arquivo::adicionarRegistroFixo(const vector<Registro> &reg)
    {
        filesystem::path nomeBIN = filesystem::path(nomeDoArquivo).replace_extension(".bin");
        string caminhoBinario = nomeBIN.string();
        ofstream out(nomeBIN, ios::binary);
        Buffer buffer;

        // Pega todos os registros coloca em uma variável temporária e escreve em um
        // arquivo binário.
        for (const Registro &registro : reg)
        {
            buffer.escreverRegistroFixo(registro, out);
        }

        // Fechamento do arquivo.
        out.close();
    }
};

#endif
