#ifndef REGISTRO_ALUNO.HPP
#include "Registro.hpp"

class RegistroAluno : public Registro
{
public:
    int matricula;
    string nome;
    string curso;

public:
    ~RegistroAluno() = default;
    void pack(string linha, Formato formato);
    void unpack(string linha, Formato formato);
    Registro lerRegistro(string linha);
    string const getChave();
    int const getTamanhoFixo();
};

#endif