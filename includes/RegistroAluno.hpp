#ifndef REGISTRO_ALUNO.HPP
#include "Registro.hpp"

class RegistroAluno : public Registro
{
public:
    int matricula;
    string nome;
    string curso;
    int tamNome = 50;
    int tamMatricula = 20;
    int tamCurso = 20;

public:
    ~RegistroAluno() = default;
    string pack(Formato formato);
    void unpack(string linha, Formato formato);
    Registro lerRegistro(string linha);
    string const getChave();
    int const getTamanhoFixo(string str);
};

#endif