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
   
   if(!data[ponteiro + 1])
   ponteiro = 0;

   return campo;

}
void Buffer::packDelimitado(const string &str, char delimitador)
{
   data.clear();
   data.insert(data.end(), str.begin(), str.end());
   data.push_back(delimitador);
}
string Buffer::unpackDelimitado(char delimitador)
{
}
void Buffer::packComprimento(const string &str)
{
   data.clear();
   short len = str.length();
   int pos = data.size();

   data.resize(pos + sizeof(len));

   memcpy(&data[pos], &len, sizeof(len));

   data.insert(data.end(), str.begin(), str.end());
}
string Buffer::unpackComprimento()
{
}
int pack(int valor)
{
}
bool Buffer::read(istream &stream)
{
   
}
void Buffer::write(ostream &stream)
{
}
void Buffer::clear()
{
   data.clear();
}