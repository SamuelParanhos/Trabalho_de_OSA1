#ifndef BUFFER_HPP
#define BUFFER_HPP
#include <vector>

using namespace std;

class Buffer
{
public:
    vector<char> data;
    int ponteiro = 0;

public:
    ~Buffer() = default;
    void packFixo(const string &str, int tamanho);
    string unpackFixo(int tamanho);
    void packDelimitado(const string &str, char delimitador);
    string unpackDelimitado(char delimitador);
    void packComprimento(const string &str);
    string unpackComprimento();
    int pack(int valor);
    bool read(istream &stream);
    void write(ostream &stream);
    void clear();
};

#endif