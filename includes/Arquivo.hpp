#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <vector>
#include "Registro.hpp"
#include <sstream>

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

    vector<T> lerRegistroCSV()
    {
        ifstream newFile(nomeDoArquivo);
        vector<T> reg;

        getline(newFile, linha);

        while (getline(newFile, linha))
        {
            T registro;
            registro.lerRegistro(linha);
            reg.push_back(registro);
        }
        return reg;
    }
    vector<T> lerRegistros()
    {
        // Cria um novo arquivo e variáveis para auxiliar na exucação da função.
        ifstream newFile(nomeDoArquivo,ios::bin);
        vector<T> reg;

        getline(newFile, linha);

        while (getline(newFile, linha))
        {
            T registro;
            registro.unpacked(linha, formato);
            reg.push_back(registro);
        }
        return reg;
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
