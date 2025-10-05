#ifndef REGISTRO_HPP
#define REGISTRO_HPP
#include "Buffer.hpp"

enum Formato
{
    FIXO,
    DELIMITADO,
    COMPRIMEMTO
};

class Registro
{
public:
    virtual ~Registro() = default;
    virtual void pack(Buffer buffer, Formato formato);
    virtual void unpack(Buffer buffer, Formato formato);
    virtual string getChave();
    virtual int getTamanhoFixo();
};

#endif