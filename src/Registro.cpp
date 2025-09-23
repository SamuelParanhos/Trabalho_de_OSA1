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
void Registro::unpackFixed(string buffer)
{
    char nome_char[campoRegistro + 1];
    strncpy(nome_char, buffer.c_str(), campoRegistro);
    
    for(int i = 0; i < 50; i++)
    {
        nome += nome_char[i];
    }

    memcpy(&idade, buffer.data() + campoNome, sizeof(int));
}
