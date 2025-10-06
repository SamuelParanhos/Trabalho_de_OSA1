#ifndef REGISTRO_HPP
#define REGISTRO_HPP
#include "Buffer.hpp"
#include <string>

using namespace std;
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
    virtual void pack(Buffer &buffer, Formato formato) const;
    virtual void unpack(Buffer buffer, Formato formato);
    virtual Registro lerRegistro(string linha);
    virtual string const getChave();
    virtual int const getTamanhoFixo(string str);
};

#endif