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
        ifstream newFile(nomeDoArquivo, ios::bin);
        vector<T> reg;
        Buffer buffer;

        while(buffer.read(newFile)){ 
            T registro;
           
            registro.unpacked(buffer, formato);
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

        for (const T &registro : reg)
        {
            registro.pack(buffer, formato);
            short tamanho_do_registro = buffer.data.size();
            out.write(reinterpret_cast<const char*>(&tamanho_do_registro), sizeof(tamanho_do_registro));
            out.write(buffer.data.data(), buffer.data.size());
        }

        out.close();
    }
};

#endif
