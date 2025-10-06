#include "Buffer.hpp"
#include <iostream>
#include <sstream>

void Buffer::packFixo(const string &str, int tamanho)
{
   string temp = str;
   temp.resize(tamanho, ' ');
   data.insert(data.end(), str.begin(), str.end());
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
   data.insert(data.end(), str.begin(), str.end());
   data.push_back(delimitador);
}
string Buffer::unpackDelimitado(string str, char delimitador)
{
}
void Buffer::packComprimento(const string &str)
{
   short tamanho = str.length();
   binario.append(reinterpret_cast<const char *>(&tamanho), sizeof(int));
   binario.append(str.data(), tamanho);

   // 1. Pega o tamanho da string

   // 2. Escreve os bytes da variável 'tamanho' no buffer
   //    'memcpy' copia sizeof(short) bytes (geralmente 2)
   //    da origem (&tamanho) para o destino (final do nosso vetor 'data').
   //    Primeiro, garantimos que o vetor tenha espaço.
   size_t pos_atual = data.size();
   data.resize(pos_atual + sizeof(tamanho));
   memcpy(&data[pos_atual], &tamanho, sizeof(tamanho));

   // 3. Escreve os bytes da própria string no buffer
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