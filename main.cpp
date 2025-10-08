#include "includes/Registro.hpp"
#include "includes/Arquivo.hpp"
#include "includes/RegistroAluno.hpp"

using namespace std;

void ExecutarTeste(Formato formato, const string &nomeArquivo, vector<RegistroAluno> &dadosOriginais);
void executarTodosTestes(const string &arquivoCSV, vector<RegistroAluno> &alunos);

int main()
{
    filesystem::path caminho_diretorio = "data";
    string arquivoCSV;
    vector<RegistroAluno> alunos;
    int menu_formato;
    
    //Verifica se o diretorio existe
    if (!filesystem::exists(caminho_diretorio))
    {
        cerr << "O diretorio '" << caminho_diretorio.string() << "' nao existe.\n";
        return 1;
    }

    for (const auto &entrada : filesystem::directory_iterator(caminho_diretorio))
    {
        if (filesystem::is_regular_file(entrada) && entrada.path().extension() == ".csv")
        {
            arquivoCSV = entrada.path().string();
            break; 
        }
    }

    //Verifica se tem algum arquico CSV nele
    if (arquivoCSV.empty())
    {
        cerr << "Nenhum arquivo .csv encontrado em '" << caminho_diretorio.string() << "'.\n";
        return 1;
    }

    //Salva o nome do arquivo
    string nomeArquivoCSV = filesystem::path(arquivoCSV).filename().string();
    //Salva o nome do arquivo sem sua exetenção
    //Ex: "dados.csv" salva como "dados"
    string nomeBase = filesystem::path(arquivoCSV).stem().string();
    
    Arquivo<RegistroAluno> leitorCSV(arquivoCSV, FIXO);
    //Faz a leitura dos registros
    alunos = leitorCSV.lerRegistroCSV();

    //Verifica se o arquivo esta vazio
    if (alunos.empty())
    {
        cerr << "O arquivo '" << nomeArquivoCSV << "' esta vazio ou corrompido.\n";
        return 1;
    }

    cout << "Arquivo CSV carregado: " << nomeArquivoCSV << " (" << alunos.size() << " registros).\n";

    // Menu de Seleção 
    while (true)
    {
        cout << "\n----------------------------------------\n";
        cout << "Escolha o Formato de Serializacao para '" << nomeArquivoCSV << "':\n";
        cout << "0 Fixo\n";
        cout << "1 Delimitado\n";
        cout << "2 Comprimento\n";
        cout << "3 Todos os Formatos\n"; 
        cout << "-1 Sair\n";
        cout << "Opcao: ";

        if (!(cin >> menu_formato))
        {
            cerr << "Entrada invalida. Saindo." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        if (menu_formato == -1)
        {
            cout << "Programa finalizado.\n";
            break; 
        }

        if (menu_formato < 0 || menu_formato > 3) 
        {
            cout << "Opcao de formato invalida." << endl;
            continue;
        }
        
        if (menu_formato == 3)
        {
            //Executa todos os formatos de uma vez
            executarTodosTestes(arquivoCSV, alunos);
        }
        else
        {
            Formato formatoSelecionado;
            string formatoStr;
            //Salva o formato do arquivo
            if (menu_formato == 0)      { formatoSelecionado = FIXO;      formatoStr = "fixo"; }
            else if (menu_formato == 1) { formatoSelecionado = DELIMITADO; formatoStr = "delimitado"; }
            else if (menu_formato == 2) { formatoSelecionado = COMPRIMENTO; formatoStr = "comprimento"; }
            string nomeArquivoBinario = nomeBase + "_" + formatoStr + ".bin";
            //Executa o arquivo no formato selecionado
            ExecutarTeste(formatoSelecionado, nomeArquivoBinario, alunos);
        }
    }

    return 0;
}

void ExecutarTeste(Formato formato, const string &nomeArquivo, vector<RegistroAluno> &dadosOriginais)
{
    string formatoStr;
    if (formato == FIXO)
        formatoStr = "Fixo";
    else if (formato == DELIMITADO)
        formatoStr = "Delimitado";
    else if (formato == COMPRIMENTO)
        formatoStr = "Comprimento";

    cout << "--- Iniciando Execução " << formatoStr << " (Arquivo: " << nomeArquivo << ") ---\n";

    //Serialização
    Arquivo<RegistroAluno> arquivoEscrita(nomeArquivo, formato);
    arquivoEscrita.adicionarRegistro(dadosOriginais);
    cout << " Serializacao para '" << nomeArquivo << "' concluida.\n";

    //Desearilização
    Arquivo<RegistroAluno> arquivoLeitura(nomeArquivo, formato);
    vector<RegistroAluno> dadosLidos = arquivoLeitura.lerRegistros();

    //Verificação
    if (dadosLidos.size() != dadosOriginais.size())
    {
        cout << "Erro - Numero de registros lidos (" << dadosLidos.size() << ") difere do original (" << dadosOriginais.size() << ")!\n";
    }
    else
    {
        cout << dadosLidos.size() << " registros desserializados.\n";
    }

    // Mostra alguns registros lidos
    cout << "Amostra de alguns Dados lidos:" << endl;
    for (size_t i = 0; i < dadosLidos.size() && i < 5; ++i)
    {
        const auto &aluno = dadosLidos[i];
        cout << " Mat: " << aluno.matricula << ", Nome: '" << aluno.nome << "', Curso: '" << aluno.curso << "'\n";
    }
}

void executarTodosTestes(const string &arquivoCSV, vector<RegistroAluno> &alunos)
{
    string nomeBase = filesystem::path(arquivoCSV).stem().string();

    cout << "Processando Todos os Formatos para: " << filesystem::path(arquivoCSV).filename().string() << endl;

    ExecutarTeste(FIXO, nomeBase + "_fixo.bin", alunos);
    cout<<'\n';
    ExecutarTeste(DELIMITADO, nomeBase + "_delimitado.bin", alunos);
    cout<<'\n';
    ExecutarTeste(COMPRIMENTO, nomeBase + "_comprimento.bin", alunos);
}
