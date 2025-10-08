#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <vector>
#include "Registro.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>

//Criamos uma classe template
template <typename T>
class Arquivo
{
public:
    string nomeDoArquivoBase; 
    Formato formato;

public:
    Arquivo(string nome, Formato fmt)
    {
        nomeDoArquivoBase = nome;
        formato = fmt;
    };

    vector<T> lerRegistroCSV()
    {
        //Criamos esta função para ler primeiramente de um CSV
        ifstream newFile(nomeDoArquivoBase);
        string linha;
        vector<T> reg;
        
        //Verificamos se o arquivo foi aberto corretamente
        if (!newFile.is_open())
        {
            cerr << "ERRO: Nao foi possivel abrir o arquivo CSV: " << nomeDoArquivoBase << std::endl;
            return reg;
        }

        //Pulamos o cabeçalho do arquivo
        getline(newFile, linha); 

        //Comando de repetição usado para ler todas as linhas do CSV
        while (getline(newFile, linha))
        {   
            //Verificamos se a linha esta vazia
            if (linha.empty())
                continue;
            //Criamos um registro e chamados a função lerRegistro, responsável por pegar cada linha,
            //separar os campos do arquivo e colocá-los nos atributos de registro
            T registro;
            registro.lerRegistro(linha);
            
            //Adicionamos o registro em um vector de Registros
            reg.push_back(registro);
        }
        newFile.close();
        return reg;
    }

    vector<T> lerRegistros()
    {
        //Abirmos o arquivo em formato binário
        filesystem::path nomeBIN = filesystem::path(nomeDoArquivoBase).replace_extension(".bin");
        ifstream newFile(nomeBIN, std::ios::binary);
        vector<T> reg;

        //Verificamos se o arquivo foi aberto corretamente
        if (!newFile.is_open()) {
            cerr << "ERRO: Nao foi possivel abrir o arquivo binario para leitura: " << nomeBIN << std::endl;
            return reg; 
        }

        //Criamos um buffer e usamos uma função de leitura para ler todos os registros do arquivo
        Buffer buffer;
        while (buffer.read(newFile))
        {
            T registro;
            
            //Usamos uma função para desserealizar o registro
            registro.unpack(buffer, formato);

            //Ao final da desserealização salvamos o arquivo em um vector de registros
            reg.push_back(registro);
        }
        newFile.close();
        return reg;
    }

    void adicionarRegistro(std::vector<T> &reg)
    {
        //Abrimos o arquivo em formato binário;
        filesystem::path nomeBIN = filesystem::path(nomeDoArquivoBase).replace_extension(".bin");
        ofstream out(nomeBIN, ios::binary);
        Buffer buffer;

        //Verificamos se o arquivo foi aberto corretamente 
        if (!out.is_open()) {
            cerr << "ERRO: Nao foi possivel criar o arquivo binario para escrita: " << nomeBIN << std::endl;
            return;
        }

        //Fazemos um for aprimador para pegar com um dos registros do vector para
        //adicioná-los no arquivo no binário
        for (T &registro : reg)
        {
            //Função de serealizar
            registro.pack(buffer, formato);

            //Escrever os dados do registro(serealizados) no arquivo binário;
            buffer.write(out);
        }

        out.close();
    }
};

#endif