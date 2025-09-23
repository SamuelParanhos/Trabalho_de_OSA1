#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <string>

using namespace std;

class Registro
{
public:
    string nome;
    int idade;

    static const int campoNome = 50;
    static const int campoRegistro = campoNome + sizeof(int);

public:
    Registro() = default;
    string packFixed();
    void unpackFixed(char *buffer);
};

#endif