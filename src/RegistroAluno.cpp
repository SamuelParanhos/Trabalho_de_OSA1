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
string RegistroAluno::pack(Formato formato)
{
  Buffer buffer;
  int tamanho = 50;
  char delimitador = '&';
  string binario;
  string nome_str = nome ;
  string matricula_str = to_string(matricula);
  string curso_str = curso;

  switch (formato)
  {

  case 1:

    buffer.packFixo(binario, nome_str, tamNome);
    buffer.packFixo(binario, matricula_str, tamMatricula);
    buffer.packFixo(binario, curso_str, tamCurso);
    return binario;
    break;

  case 2:
    buffer.packDelimitado(binario, nome_str, delimitador);
    buffer.packDelimitado(binario, matricula_str, delimitador);
    buffer.packDelimitado(binario, curso_str, delimitador);
    break;

  case 3:
    buffer.packComprimento(binario, nome_str);
    buffer.packComprimento(binario, matricula_str );
    buffer.packComprimento(binario, curso_str);
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
  return .size();
}