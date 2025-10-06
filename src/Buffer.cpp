#include "Buffer.hpp"
#include <iostream>
#include <sstream>
#include <cstring>

void Buffer::packFixo(const string &str, int tamanho)
{
   data.clear();
   string temp = str;
   temp.resize(tamanho, ' ');
   data.insert(data.end(), temp.begin(), temp.end());
}
string Buffer::unpackFixo(string str, int tamanho)
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
void Buffer::packDelimitado(const string &str, char delimitador)
{
   data.clear();
   data.insert(data.end(), str.begin(), str.end());
   data.push_back(delimitador);
}
string Buffer::unpackDelimitado(string str, char delimitador)
{
}
void Buffer::packComprimento(const string &str)
{
   data.clear();
   short len = str.length();
   ponteiro = data.size();

   data.resize(ponteiro + sizeof(len));

   memcpy(&data[ponteiro], &len, sizeof(len));

   data.insert(data.end(), str.begin(), str.end());
}
string Buffer::unpackComprimento(string str)
{
}
int pack(int valor)
{
}
bool Buffer::read(istream &strem, int tamanho)
{
}
void Buffer::write(ostream &stream)
{
}
void Buffer::clear()
{
   data.clear();
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