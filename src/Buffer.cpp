#include "Buffer.hpp"
#include <iostream>
#include <sstream>

void packFixo(string str, int tamanho)
{

    /*// Cria uma string para armazenar os campos nome e idade
    // em formato binário.
    string binario(campoRegistro, '\0');

    // Coloca o nome na string em formato binário.
    strncpy(&binario[0], nome.c_str(), campoNome);

    // Coloca a idade na string em formato binário.
    memcpy(&binario[0] + campoNome, &idade, sizeof(int));

    return binario;
     */
}
string unpackFixo(string str, int tamanho)
{

    /*// Cria uma variável auxiliar para receber o nome.
char nome_char[campoRegistro + 1];

// O nome em formato binário é colocado na variável auxiliar
// e convertido para o tipo char*.
memcpy(nome_char, buffer, campoRegistro);

nome_char[campoRegistro] = '\0';

// O nome é convertido para string e armazenado no campo nome do Registro.
nome = std::string(nome_char);

// O nome em formato binário é colocado no campo idade de Registro.
memcpy(&idade, buffer + campoNome, sizeof(int));
*/
}
void packDelimitado(string str, char delimitador)
{
}
string unpackDelimitado(string str, char delimitador)
{
}
void packComprimento(string str)
{
}
string unpackComprimento(string str)
{
}
int pack(int valor)
{
}
bool read(istream strem, int tamanho)
{
}
void write(ostream stream)
{
}
void clear()
{
}

/*Registro Buffer::lerRegistro(string linha)
{
   Registro registro;
   // Variável usada para manipular uma linha.
   stringstream ss(linha);
   string nome_str, idade_str;

   // Separa a linha CSV nos campos nome e idade.
   getline(ss, nome_str, ',');
   getline(ss, idade_str, '\n');

   // atribui o nome a seu respectivo campo no registro.
   registro.nome = nome_str;

   // Verifica se o nome está vazio.
   if (!idade_str.empty())
   {
       // atribui a idade ao seu respectivo campo no registro,
       // fazendo a conversão de char para int.
       registro.idade = stoi(idade_str);
   }

   return registro;
}

Registro Buffer::lerRegistroFixo(char *buffer_leitura)
{
   Registro registro;

   // Recebe um registro em formato binario e chama a função desserealizar
   // para converter os campos em seus respectivos formatos aceitos pela classe Registro.
   registro.unpackFixed(buffer_leitura);

   return registro;
}

void Buffer::escreverRegistroFixo(Registro reg, ofstream &out)
{
   // A string binário recebe o retorno da função de serealizar, que retorna uma única string
   // contendo os campos nome e idade em formato binario.
   string binario = reg.packFixed();

   // A string é salva no arquivo.
   out.write(binario.c_str(), binario.length());
}*/