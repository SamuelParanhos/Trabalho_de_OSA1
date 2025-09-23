#include "Registro.hpp"
#include "fstream"
#include "sstream"
#include <cstring>

string Registro::packFixed()
{
    //Cria uma string para armazenar os campos nome e idade
    //em formato binário.
    string binario(campoRegistro, '\0');

    //Coloca o nome na string em formato binário.
    strncpy(&binario[0], nome.c_str(), campoNome);

    //Coloca a idade na string em formato binário.
    memcpy(&binario[0] + campoNome, &idade, sizeof(int));

    return binario;
}
void Registro::unpackFixed(char *buffer)
{
    //Cria uma variável auxiliar para receber o nome.
    char nome_char[campoRegistro + 1];

    //O nome em formato binário é colocado na variável auxiliar 
    //e convertido para o tipo char*.
    memcpy(nome_char, buffer, campoRegistro);
    
    nome_char[campoRegistro] = '\0';

    //O nome é convertido para string e armazenado no campo nome do Registro.
    nome = std::string(nome_char);
    
    //O nome em formato binário é colocado no campo idade de Registro.
    memcpy(&idade, buffer + campoNome, sizeof(int));
}