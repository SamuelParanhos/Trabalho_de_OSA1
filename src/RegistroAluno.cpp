#include "RegistroAluno.hpp"
#include "fstream"
#include "sstream"
#include <cstring>

Registro RegistroAluno::lerRegistro(string linha)
{
  RegistroAluno registro;
  stringstream ss(linha);
  string nome_str, matricula_str, curso_str;

  // Separa a linha CSV nos campos nome e idade.
  getline(ss, nome_str, ',');
  getline(ss, matricula_str, ',');
  getline(ss, curso_str, '\n');

  // atribui o nome a seu respectivo campo no registro.
  registro.nome = nome_str;
  registro.matricula = stoi(matricula_str);
  registro.curso = curso_str;
}
void RegistroAluno::pack(string linha, Formato formato)
{
  Buffer buffer;
  int tamanho = 50;
  char delimitador = '&';

  switch (formato)
  {
  case 1:
    buffer.packFixo(linha, tamanho);
    break;

  case 2:
    buffer.packDelimitado(linha, delimitador);
    break;

  case 3:
    buffer.packComprimento(linha);
    break;
  }
}
void RegistroAluno::unpack(string linha, Formato formato)
{
  Buffer buffer;
  int tamanho = 50;
  char delimitador = '&';
  switch (formato)
  {

  case 1:
    buffer.unpackFixo(linha, tamanho);
    break;

  case 2:
    buffer.packDelimitado(linha, delimitador);
    break;

  case 3:
    buffer.unpackComprimento(linha);
    break;
  }
}