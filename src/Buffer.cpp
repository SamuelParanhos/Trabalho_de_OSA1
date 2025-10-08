#include "Buffer.hpp"
#include <iostream>
#include <sstream>
#include <cstring>

void Buffer::packFixo(const string &str, int tamanho)
{
   string temp = str;
   temp.resize(tamanho, ' ');
   data.insert(data.end(), temp.begin(), temp.end());
}
void limpaCampo(std::string &s)
{
   s.erase(s.find_last_not_of(' ') + 1);
}
string Buffer::unpackFixo(int tamanho)
{
   const char *inicioDados = &data[ponteiro];

   string campo(inicioDados, tamanho);

   ponteiro += tamanho;

   limpaCampo(campo);

   return campo;
}
void Buffer::packDelimitado(const string &str, char delimitador)
{
   data.insert(data.end(), str.begin(), str.end());
   data.push_back(delimitador);
}
string Buffer::unpackDelimitado(char delimitador)
{
   {
      string campo;
      int tamanho = data.size();

      while (ponteiro < tamanho && data[ponteiro] != delimitador)
      {
         campo.push_back(data[ponteiro]);
         ponteiro++;
      }

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

   data.resize(pos + sizeof(len));

   memcpy(&data[pos], &len, sizeof(len));

   data.insert(data.end(), str.begin(), str.end());
}
string Buffer::unpackComprimento()
{
   short tamanho_do_campo;


   memcpy(&tamanho_do_campo, &data[ponteiro], sizeof(short));
   ponteiro += sizeof(short);

   string campo(&data[ponteiro], tamanho_do_campo);

   ponteiro += tamanho_do_campo;

   return campo;
}
int pack(int valor)
{
   valor = 1;
   return valor;
}
bool Buffer::read(std::istream &stream)
{
    short tamanho;

    // Tenta ler o tamanho do próximo registro. Se não conseguir (fim do arquivo), retorna false.
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
    // Primeiro, escreve o tamanho do registro (o "cabeçalho")
    short tamanho = data.size();
    stream.write(reinterpret_cast<const char *>(&tamanho), sizeof(tamanho));

    // Depois, escreve os dados do buffer
    stream.write(data.data(), tamanho);
}
void Buffer::clear()
{
   data.clear();
}