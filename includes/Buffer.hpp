#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <fstream>
#include "Registro.hpp"

using namespace std;

class Buffer
{
public:
    Buffer() = default;
    void escreverRegistro(Registro &reg, ofstream& out);
    Registro lerRegistroFixo(char* buffer_leitura);
    void escreverRegistroFixo(Registro reg, ofstream& out);
    Registro lerRegistro(string linha);

};

#endif