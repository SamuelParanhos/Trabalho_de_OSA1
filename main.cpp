#include "includes/Registro.hpp"
#include "includes/Arquivo.hpp"
#include <filesystem>
#include <iostream>

int main()
{
    // Cria um objeto Arquivo para manipulação dos registros
    Arquivo arquivo;

    filesystem::path caminho_diretorio = "Arquivos_Nomes e Idades";
    //Vetores para armazenar os nomes dos arquivos e os registros lidos
    vector<string> arquivos_csv;
    vector<Registro> reg;
    int count = 0;
    int menu;

    cout << "Verificando arquivos .csv no diretorio: " << caminho_diretorio << std::endl;


    //Verifica se o diretorio existe
    if (!filesystem::exists(caminho_diretorio) || !filesystem::is_directory(caminho_diretorio))
    {
        cerr << "Erro: O diretorio  nao existe ou nao e um diretorio." << endl;
        return 1;
    }

    cout << "Arquivo .csv encontrado: " << endl;
    // Itera sobre todos os arquivos do diretório e seleciona apenas os .csv
    for (const auto &entrada : filesystem::directory_iterator(caminho_diretorio))
    {
        if (filesystem::is_regular_file(entrada) && entrada.path().extension() == ".csv")
        {

            arquivos_csv.push_back(entrada.path().string());

            cout << "[" << count << "]" << entrada.path().filename() << endl;
            count++;
        }
    }

    cout << "[" << count << "]" << "Todas as opcoes" << endl;

    // Menu de seleção: permite ao usuário escolher um arquivo ou sair
    while (true)
    {
        cout << "\nEscolha um arquivo para processar ou digite -1 para sair: ";
        cin >> menu;

        if (menu == -1)
        {
            cout << "Saindo" << endl;
            break;
        }

        if (menu < 0 || menu > count)
        {
            cout << "Opcao invalida. Tente novamente." << endl;
            continue;
        }

        if (menu == count)
        {
            for (int i = 0; i < count; i++)
            {
                arquivo.nomeDoArquivo = arquivos_csv[i];
                reg = arquivo.lerRegistrosCSV();
                arquivo.adicionarRegistroFixo(reg);
                reg = arquivo.lerRegistroFixo();
                cout<<"Arquivo processado com sucesso!"<<endl;
                cout<<endl;
            }
        }

        else
        {
            // Seleciona o arquivo escolhido
            arquivo.nomeDoArquivo = arquivos_csv[menu];
            // Processa os registros
            reg = arquivo.lerRegistrosCSV();
            arquivo.adicionarRegistroFixo(reg);
            reg = arquivo.lerRegistroFixo();
            cout << "Arquivo processado com sucesso!" << endl;
        }
    }

    return 0;
}