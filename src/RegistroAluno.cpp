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
void RegistroAluno::pack(Buffer &buffer, Formato formato)
{
  int tamanho = 50;
  char delimitador = '&';
  string binario;
  string matricula_str = to_string(matricula);
  buffer.clear();

  switch (formato)
  {
  case FIXO:

    buffer.packFixo(nome, tamNome);
    buffer.packFixo(matricula_str, tamMatricula);
    buffer.packFixo(curso, tamCurso);
    break;

  case DELIMITADO:
    buffer.packDelimitado(nome, delimitador);
    buffer.packDelimitado(matricula_str, delimitador);
    buffer.packDelimitado(curso, delimitador);
    break;

  case  COMPRIMEMTO:  
    buffer.packComprimento(nome);
    buffer.packComprimento(matricula_str);
    buffer.packComprimento(curso);
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
    buffer.unpackDelimitado(linha, delimitador);
    break;

  case 3:
    buffer.unpackComprimento(linha);
    break;
  }
}
int const getTamanhoFixo()
{
}