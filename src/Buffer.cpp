#include "Buffer.hpp"
#include <iostream>
#include <sstream>
#include <cstring>

// Esta função é responsável por serealizar os campos de registro,
// formatando cada campo e os colocando no buffer
void Buffer::packFixo(const string &str, int tamanho)
{
   string temp = str;
   temp.resize(tamanho, ' ');
   data.insert(data.end(), temp.begin(), temp.end());
}

// Esta função é utilizada para limpar todos os caracteres vazios
void limpaCampo(std::string &s)
{
   s.erase(s.find_last_not_of(' ') + 1);
}
// A função é responsável por retorna um string contendo o campo
// desserealizado que será usado para popular o campo do resgistro
string Buffer::unpackFixo(int tamanho)
{
   const char *inicioDados = &data[ponteiro];

   string campo(inicioDados, tamanho);

   ponteiro += tamanho;

   limpaCampo(campo);

   return campo;
}
// Esta função serealiza os registro de campo delimitado
void Buffer::packDelimitado(const string &str, char delimitador)
{
   data.insert(data.end(), str.begin(), str.end());
   data.push_back(delimitador);
}
// Esta função desserealiza os registro de campo delimitado
string Buffer::unpackDelimitado(char delimitador)
{
   {
      string campo;
      int tamanho = data.size();

      // Pega caractere por caracter e coloca no 'campo'
      while (ponteiro < tamanho && data[ponteiro] != delimitador)
      {
         campo.push_back(data[ponteiro]);
         ponteiro++;
      }
      // Atualiza o ponteiro, caso o elemento atual for o delimitador
      if (ponteiro < tamanho && data[ponteiro] == delimitador)
      {
         ponteiro++;
      }

      return campo;
   }
}
void Buffer::packComprimento(const string &str)
{
   short len = str.length();
   int pos = data.size();

   // Aumentamos o tamanho da vetor para conter o tamanho do campo
   data.resize(pos + sizeof(len));

   // Primeiro gravamos e tamanho e depois os caracteres do campo
   memcpy(&data[pos], &len, sizeof(len));

   data.insert(data.end(), str.begin(), str.end());
}
string Buffer::unpackComprimento()
{
   short tamanho_do_campo;

   // Adicionamos o tamanho do campo na variável 'tamanho_do_campo',
   // que será usada para ler a quantidade de caracteres de cada campo
   memcpy(&tamanho_do_campo, &data[ponteiro], sizeof(short));
   ponteiro += sizeof(short);

   // Adicionamos os caracteres em seu respectivo campo
   string campo(&data[ponteiro], tamanho_do_campo);

   ponteiro += tamanho_do_campo;

   return campo;
}

bool Buffer::read(std::istream &stream)
{
   short tamanho;

   // Tenta ler o tamanho do próximo registro. Se não conseguir retorna false.
   if (!stream.read(reinterpret_cast<char *>(&tamanho), sizeof(tamanho)))
   {
      return false;
   }

   // Prepara o buffer para receber os dados
   data.resize(tamanho);

   // Lê os dados do registro para dentro do buffer. Se falhar, retorna false.
   if (!stream.read(data.data(), tamanho))
   {
      return false;
   }

   return true;
}
void Buffer::write(std::ostream &stream)
{
   // Primeiro, escreve o tamanho do registro
   short tamanho = data.size();
   stream.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));

   // Depois, escreve os dados do buffer
   stream.write(data.data(), tamanho);
}
void Buffer::clear()
{
   // Limpa o buffer
   data.clear();
}