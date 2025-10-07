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
    char delimitador = '&';

public:
    ~RegistroAluno() = default;
    void pack(Buffer &buffer, Formato formato);
    void unpack(Buffer &buffer, Formato formato);
    Registro lerRegistro(string linha);
    string const getChave();
    int const getTamanhoFixo(string str);
};

#endif