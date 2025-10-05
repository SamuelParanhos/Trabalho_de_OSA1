#ifndef BUFFER_HPP
#define BUFFER_HPP
#include <vector>

using namespace std;

class Buffer
{
public:
    vector<char> data;
    int ponteiro;

public:
    ~Buffer() = default;
    void packFixo(string str, int tamanho);
    string unpackFixo(int tamanho);
    void packDelimitado(string str, char delimitador);
    string unpackDelimitado(char delimitador);
    void packComprimento(string str);
    string unpackComprimento();
    int pack(int valor);
    bool read(istream strem, int tamanho);
    void write(ostream stream);
    void clear();
};

#endif