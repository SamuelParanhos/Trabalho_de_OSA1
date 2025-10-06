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
        nomeDoArquivo = nome;
        formato = fmt;
    };

    vector<T> lerRegistroCSV()
    {
        ifstream newFile(nomeDoArquivo);
        string linha;
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

    void adicionarRegistro(const vector<T> &reg)
    {
        filesystem::path nomeBIN = filesystem::path(nomeDoArquivo).replace_extension(".bin");
        string caminhoBinario = nomeBIN.string();
        ofstream out(nomeBIN, ios::binary);
        Buffer buffer;
        string binario;

        // Pega todos os registros coloca em uma variável temporária e escreve em um
        // arquivo binário.
        for (const T &registro : reg)
        {
            binario = registro.pack(formato);
            out.write(binario.c_str(), binario.size());
        }

        // Fechamento do arquivo.
        out.close();
    }
};

#endif
