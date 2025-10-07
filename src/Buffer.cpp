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

   const char *inicioDados = &data[ponteiro];

   memcpy(&tamanho_do_campo, &data[ponteiro], sizeof(short));
   ponteiro += sizeof(short);

   string campo(inicioDados, tamanho_do_campo);

   ponteiro += tamanho_do_campo;

   return campo;
}
int pack(int valor)
{
   valor = 1;
   return valor;
}
/*bool Buffer::read(istream &stream)
{
   return false;
}
void Buffer::write(ostream &stream)
{
}
*/
void Buffer::clear()
{
   data.clear();
}