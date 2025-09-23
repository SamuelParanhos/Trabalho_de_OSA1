#include "Buffer.hpp"
#include <iostream>
#include <sstream>

Registro Buffer::lerRegistro(string linha)
{
    Registro registro;
    //Variável usada para manipular uma linha.
    stringstream ss(linha);
    string nome_str, idade_str;

    //Separa a linha CSV nos campos nome e idade.
    getline(ss, nome_str, ',');
    getline(ss, idade_str, '\n');

    //atribui o nome a seu respectivo campo no registro.
    registro.nome = nome_str;

    //Verifica se o nome está vazio.
    if (!idade_str.empty())
    {
        //atribui a idade ao seu respectivo campo no registro,
        //fazendo a conversão de char para int.
        registro.idade = stoi(idade_str);
    }

    return registro;
}
Registro Buffer::lerRegistroFixo(char* buffer_leitura)
{
    Registro registro;
    
    //Recebe um registro em formato binario e chama a função desserealizar 
    //para converter os campos em seus respectivos formatos aceitos pela classe Registro.
    registro.unpackFixed(buffer_leitura);

    return registro;
}

void Buffer::escreverRegistroFixo(Registro reg, ofstream &out)
{
    //A string binário recebe o retorno da função de serealizar, que retorna uma única string
    //contendo os campos nome e idade em formato binario.
    string binario = reg.packFixed();

    //A string é salva no arquivo.
    out.write(binario.c_str(), binario.length());
}