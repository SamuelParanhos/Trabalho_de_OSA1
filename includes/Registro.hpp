#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <string>

class Registro
{
private:
    std::string nome;
    int idade;

public:
    Registro() = default;
    std::string GetNome();
    int GetIdade();
    std::string packWithLength();
    void unpackWithLength(std::string data);
    std::string packFixed();
    void unpackFixed(std::string buffer);
};

#endif