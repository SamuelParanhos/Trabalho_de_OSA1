#include "Registro.hpp"
#include "fstream"
#include "sstream"
#include <cstring>

string Registro::packFixed()
{
    string binario(campoRegistro, '\0');

    strncpy(&binario[0], nome.c_str(), campoNome);

    memcpy(&binario[0] + campoNome, &idade, sizeof(int));

    return binario;
}
void Registro::unpackFixed(char *buffer)
{
    char nome_char[campoRegistro + 1];

    memcpy(nome_char, buffer, campoRegistro);
    nome_char[campoRegistro] = '\0';

    nome = std::string(nome_char);

    memcpy(&idade, buffer + campoNome, sizeof(int));
}