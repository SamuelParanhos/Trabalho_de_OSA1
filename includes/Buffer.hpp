#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <fstream>
#include "Registro.hpp"

class Buffer
{
public:
    Buffer() = default;
    void escreverRegistro(Registro reg, std::ofstream out);
    Registro lerRefistroFixo(std::ifstream in);
};

#endif