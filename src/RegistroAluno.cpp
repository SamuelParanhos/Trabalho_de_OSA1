#include "RegistroAluno.hpp"
#include "fstream"
#include "sstream"
#include <cstring>

void RegistroAluno::lerRegistro(string linha)
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
  registro.curso = curso_str;

  if(!matricula_str.empty()){
    registro.matricula = stoi(matricula_str);
  }


}
void RegistroAluno::pack(Buffer &buffer, Formato formato) 
{
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

  case COMPRIMEMTO:
    buffer.packComprimento(nome);
    buffer.packComprimento(matricula_str);
    buffer.packComprimento(curso);
    break;
  }
}
void RegistroAluno::unpack(Buffer &buffer, Formato formato)
{
  switch (formato)
  {
  case FIXO:
    nome = buffer.unpackFixo(tamNome);
    matricula = stoi(buffer.unpackFixo(tamMatricula));
    curso = buffer.unpackFixo(tamCurso);
    buffer.ponteiro = 0; // Reniciei aqui porque não conseguir pensar em uma maneria melhor
    break;

  case DELIMITADO:
    nome = buffer.unpackDelimitado(delimitador);
    matricula = stoi(buffer.unpackDelimitado(delimitador));
    curso = buffer.unpackDelimitado(delimitador);
    buffer.ponteiro = 0;
    break;

  case COMPRIMEMTO:
    nome = buffer.unpackComprimento();
    matricula = stoi(buffer.unpackComprimento());
    curso = buffer.unpackComprimento();
    buffer.ponteiro = 0;
    break;
  }
}
/*int RegistroAluno::getTamanhoFixo() const
{
    return tamMatricula + tamNome + tamCurso;
}
*/