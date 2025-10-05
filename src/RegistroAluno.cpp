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
  int tamanho = 50;
  char delimitador = '&';
  Buffer buffer;

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
void RegistroAluno::unpack(Buffer buffer, Formato formato)
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