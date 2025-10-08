#ifndef REGISTRO_ALUNO_HPP
#include "Registro.hpp"

class RegistroAluno : public Registro
{
public:
    int matricula;
    string nome;
    string curso;
    int tamNome = 50;
    int tamMatricula = 8;
    int tamCurso = 5;
    char delimitador = '&';

public:
    void pack(Buffer &buffer, Formato formato);
    void unpack(Buffer &buffer, Formato formato);
    void lerRegistro(string linha);
    ~RegistroAluno() = default;
};

#endif