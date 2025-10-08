#ifndef REGISTRO_HPP
#define REGISTRO_HPP
#include "Buffer.hpp"
#include <string>

using namespace std;
enum Formato
{
  FIXO,
  DELIMITADO,
  COMPRIMENTO
};

class Registro
{
public:
  virtual void pack(Buffer &buffer, Formato formato) = 0;
  virtual void unpack(Buffer &buffer, Formato formato) = 0;
  virtual void lerRegistro(string linha) = 0;
  virtual ~Registro() = default;
};

#endif