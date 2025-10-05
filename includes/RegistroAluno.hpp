#ifndef REGISTRO_ALUNO.HPP
#include "Registro.hpp"
#include "Buffer.hpp"

class RegistroAluno : public Registro
{
public:
    int matricula;
    string nome;
    string curso;

public:
    ~RegistroAluno() = default;
    void pack(Buffer buffer, Formato formato);
    void unpack(Buffer buffer, Formato formato);
    string getChave();
    int getTamanhoFixo();
};

#endif