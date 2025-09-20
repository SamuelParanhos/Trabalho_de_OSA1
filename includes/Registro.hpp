#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <string>

using namespace std;

class Registro
{
public:
    string nome;
    int idade;

public:
    Registro() = default;
    string packFixed();
    void unpackFixed(string buffer);
};

#endif