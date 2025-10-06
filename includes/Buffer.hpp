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
    void packFixo(string &binario, string& str, int tamanho);
    string unpackFixo(string str, int tamanho);
    void packDelimitado(string &binario, string &str,char delimitador);
    string unpackDelimitado(string str, char delimitador);
    void packComprimento(string &binario, string &str);
    string unpackComprimento(string str);
    int pack(int valor);
    bool read(istream &stream, int tamanho);
    void write(ostream &stream);
    void clear();
};

#endif