#include "RegistroAluno.hpp"
#include "fstream"
#include "sstream"
#include <cstring>
#include <iostream>

void RegistroAluno::lerRegistro(string linha)
{
  //Criamos as variáveis que irão auxiliar o nosso programa
  stringstream ss(linha);
  string nome_str, matricula_str, curso_str;

  //A função getline é responsável por delimitador os campos
  getline(ss, nome_str, ';');
  getline(ss, matricula_str, ';');
  getline(ss, curso_str, '\n');

  //Alteramos os campos do registro
  this->nome = nome_str;
  this->curso = curso_str;

  //Verificamos se a matrícula é válida para adicionarmos ela ao registro
  if (!matricula_str.empty())
  {
    try {
      this->matricula = stoi(matricula_str);
    } catch (const invalid_argument& e) {
      cerr << "Erro de conversao de matricula: " << e.what() << " para a string '" << matricula_str << "'" << endl;
      this->matricula = 0;
    }
  }
  else
  {
    this->matricula = 0; 
  }
}
void RegistroAluno::pack(Buffer &buffer, Formato formato)
{
  //Convertemos a matricula para uma string
  string matricula_str = to_string(matricula);
  
  //Limpamos o buffer
  buffer.clear();

  //Descobrir qual é o tipo de registro por meio do formato e chamamos a função pack
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
  //Setamos o ponteiro como 0
  buffer.ponteiro = 0; 

  //Criamos uma string auxiliar
  string matricula_str;

  //Descobrir qual é o tipo de registro por meio do formato e chamamos a função unpack
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
        matricula = 0; 
    }
  } catch(const std::exception& e) {
    std::cerr << "Falha ao converter a matricula durante o unpack: '" << matricula_str << "'. Erro: " << e.what() << '\n';
    matricula = -1; 
  }

}