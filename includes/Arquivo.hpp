#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <vector>
#include "Registro.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>

template <typename T>
class Arquivo
{
public:
    std::string nomeDoArquivoBase; 
    Formato formato;

public:
    Arquivo(std::string nome, Formato fmt)
    {
        nomeDoArquivoBase = nome;
        formato = fmt;
    };

    std::vector<T> lerRegistroCSV()
    {
        std::ifstream newFile(nomeDoArquivoBase);
        std::string linha;
        std::vector<T> reg;

        if (!newFile.is_open())
        {
            std::cerr << "ERRO: Nao foi possivel abrir o arquivo CSV: " << nomeDoArquivoBase << std::endl;
            return reg;
        }

        getline(newFile, linha); // Pula cabeçalho

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

    std::vector<T> lerRegistros()
    {
  
        std::filesystem::path nomeBIN = std::filesystem::path(nomeDoArquivoBase).replace_extension(".bin");
        
        std::ifstream newFile(nomeBIN, std::ios::binary);
        std::vector<T> reg;
        short tamanhoDoRegistro;

        if (!newFile.is_open()) {
            std::cerr << "ERRO: Nao foi possivel abrir o arquivo binario para leitura: " << nomeBIN << std::endl;
            return reg; 
        }

        while (newFile.read(reinterpret_cast<char *>(&tamanhoDoRegistro), sizeof(tamanhoDoRegistro)))
        {
            Buffer buffer;
            buffer.data.resize(tamanhoDoRegistro);

            if (newFile.read(buffer.data.data(), tamanhoDoRegistro))
            {
                T registro;
                registro.unpack(buffer, formato);
                reg.push_back(registro);
            }
        }
        return reg;
    }

    void adicionarRegistro(std::vector<T> &reg)
    {
        std::filesystem::path nomeBIN = std::filesystem::path(nomeDoArquivoBase).replace_extension(".bin");
        std::ofstream out(nomeBIN, std::ios::binary);
        Buffer buffer;

        if (!out.is_open()) {
            std::cerr << "ERRO: Nao foi possivel criar o arquivo binario para escrita: " << nomeBIN << std::endl;
            return;
        }

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