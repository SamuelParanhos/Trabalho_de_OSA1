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
    Registro lerRegistroFixo(ifstream& in);
    void escreverRegistroFixo(Registro reg, ofstream& out);
    Registro lerRegistro(ifstream& in);

};

#endif