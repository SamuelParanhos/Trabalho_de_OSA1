#include "RegistroAluno.hpp"
#include "fstream"
#include "sstream"
#include <cstring>
#include <iostream>

void RegistroAluno::lerRegistro(string linha)
{
  stringstream ss(linha);
  string nome_str, matricula_str, curso_str;

  getline(ss, nome_str, ';');
  getline(ss, matricula_str, ';');
  getline(ss, curso_str, '\n');

  this->nome = nome_str;
  this->curso = curso_str;

  if (!matricula_str.empty())
  {
    try {
      this->matricula = stoi(matricula_str);
    } catch (const std::invalid_argument& e) {
      cerr << "Erro de conversao de matricula: " << e.what() << " para a string '" << matricula_str << "'" << std::endl;
      this->matricula = 0; // Define um valor padrão em caso de erro.
    }
  }
  else
  {
    this->matricula = 0; // Valor padrão se a matrícula estiver vazia no CSV.
  }
}
void RegistroAluno::pack(Buffer &buffer, Formato formato)
{
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

  case COMPRIMENTO:
  buffer.packComprimento(nome);
    buffer.packComprimento(matricula_str);
    buffer.packComprimento(curso);
    break;
  }
}
void RegistroAluno::unpack(Buffer &buffer, Formato formato)
{
  buffer.ponteiro = 0; 

  string matricula_str;

  switch (formato)
  {
  case FIXO:
    nome = buffer.unpackFixo(tamNome);
    matricula_str = buffer.unpackFixo(tamMatricula);
    curso = buffer.unpackFixo(tamCurso);
    break;

  case DELIMITADO:
    nome = buffer.unpackDelimitado(delimitador);
    matricula_str = buffer.unpackDelimitado(delimitador);
    curso = buffer.unpackDelimitado(delimitador);
    break;

  case COMPRIMENTO:
    nome = buffer.unpackComprimento();
    matricula_str = buffer.unpackComprimento();
    curso = buffer.unpackComprimento();
    break;
  }
  try {
    if (!matricula_str.empty()){
        matricula = stoi(matricula_str);
    } else {
        matricula = 0; // Valor padrão
    }
  } catch(const std::exception& e) {
    std::cerr << "Falha ao converter a matricula durante o unpack: '" << matricula_str << "'. Erro: " << e.what() << '\n';
    matricula = -1; // Usar um valor inválido para indicar erro.
  }

}
/*int RegistroAluno::getTamanhoFixo() const
{
    return tamMatricula + tamNome + tamCurso;
}
*/