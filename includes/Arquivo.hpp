#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <vector>
#include "Registro.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>

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

    /*vector<T> lerRegistroCSV()
    {
        vector<T> regs;
        ifstream csvFile(nomeDoArquivo);

        if (!csvFile.is_open()) {
            cerr << "ERRO: Nao foi possivel abrir o arquivo CSV: " << nomeDoArquivo << endl;
            return regs; // Retorna o vetor vazio se o arquivo não abrir
        }

        string linha;
        // Pula a primeira linha (cabeçalho) do arquivo CSV
        getline(csvFile, linha);

        while (getline(csvFile, linha))
        {
            if (linha.empty()) continue; // Ignora linhas vazias

            T registro;
            // Para esta linha funcionar, sua classe T (ex: RegistroAluno)
            // deve ter um método público: void lerRegistro(const string& linha);
            registro.lerRegistro(linha);
            regs.push_back(registro);
        }
        return regs;
    }*/
    vector<T> lerRegistroCSV()
    {
        ifstream newFile(nomeDoArquivo);
        string linha;
        vector<T> reg;

        if (!newFile.is_open())
        {
            cerr << "ERRO: Nao foi possivel abrir o arquivo CSV: " << nomeDoArquivo << endl;
            return reg; // Retorna o vetor vazio se o arquivo não abrir
        }

        getline(newFile, linha);

        while (getline(newFile, linha))
        {
            if (linha.empty())
                continue;
            T registro;
            registro.lerRegistro(linha);
            reg.push_back(registro);
        }
        return reg;
    }

    vector<T> lerRegistros()
    {
        // Cria um novo arquivo e variáveis para auxiliar na exucação da função.
        ifstream newFile(nomeDoArquivo, ios::binary);
        vector<T> reg;
        short tamanhoDoRegistro;

        // Lê o tamanho do proximo registro, se não tiver sai do loop
        while (newFile.read(reinterpret_cast<char *>(&tamanhoDoRegistro), sizeof(tamanhoDoRegistro)))
        {

            Buffer buffer;
            buffer.data.resize(tamanhoDoRegistro);

            // Vai ler a quantidade de bytes que acabamos de descobrir
            if (newFile.read(buffer.data.data(), tamanhoDoRegistro))
            {
                T registro;
                registro.unpack(buffer, formato);
                reg.push_back(registro);
            }
        }
        return reg;
    }

    void adicionarRegistro(vector<T> &reg)
    {
        filesystem::path nomeBIN = filesystem::path(nomeDoArquivo).replace_extension(".bin");
        string caminhoBinario = nomeBIN.string();
        ofstream out(nomeBIN, ios::binary);
        Buffer buffer;

        for (T &registro : reg)
        {
            registro.pack(buffer, formato);
            short tamanho_do_registro = buffer.data.size();
            out.write(reinterpret_cast<const char *>(&tamanho_do_registro), sizeof(tamanho_do_registro));
            out.write(buffer.data.data(), buffer.data.size());
        }

        out.close();
    }
};

#endif
