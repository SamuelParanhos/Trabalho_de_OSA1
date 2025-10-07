#include "includes/Registro.hpp"
#include "includes/Arquivo.hpp"
#include "includes/RegistroAluno.hpp"
#include <iostream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

// Função para testar um ciclo completo de escrita e leitura
void testarCicloCompleto(Formato formato, const string& nomeArquivo, vector<RegistroAluno>& dadosOriginais) {
    cout << "--- INICIANDO TESTE PARA O ARQUIVO: " << nomeArquivo << " ---\n";

    // --- ETAPA DE ESCRITA ---
    cout << "1. Escrevendo " << dadosOriginais.size() << " registros...\n";
    Arquivo<RegistroAluno> arquivoEscrita(nomeArquivo, formato);
    arquivoEscrita.adicionarRegistro(dadosOriginais);
    cout << "   Escrita concluida.\n";

    // --- ETAPA DE LEITURA ---
    cout << "2. Lendo registros de volta para verificacao...\n";
    Arquivo<RegistroAluno> arquivoLeitura(nomeArquivo, formato);
    vector<RegistroAluno> dadosLidos = arquivoLeitura.lerRegistros();

    if (dadosLidos.size() != dadosOriginais.size()) {
        cout << "   ERRO: O numero de registros lidos (" << dadosLidos.size() << ") e diferente do original (" << dadosOriginais.size() << ")!\n";
    } else {
        cout << "   Sucesso! " << dadosLidos.size() << " registros lidos corretamente.\n";
    }

    // Imprime os registros lidos para inspeção visual
    for (const auto& aluno : dadosLidos) {
        cout << "     -> Lido: Mat: " << aluno.matricula << ", Nome: '" << aluno.nome << "', Curso: '" << aluno.curso << "'\n";
    }
    cout << "--- FIM DO TESTE: " << nomeArquivo << " ---\n\n";
}

int main() {
    // 1. Define o caminho para o seu arquivo CSV de teste.
    //    Assumindo que o executável está na pasta raiz e o CSV em "data/dados.csv"
    const string caminhoCSV = "data/dados.csv";
    cout << "Lendo dados do arquivo '" << caminhoCSV << "'...\n";

    // 2. Lê os dados originais do CSV para a memória
    Arquivo<RegistroAluno> leitorCSV(caminhoCSV, FIXO); // O formato aqui não importa para a leitura do CSV
    vector<RegistroAluno> alunos = leitorCSV.lerRegistroCSV();

    // Verificação para garantir que o CSV foi lido com sucesso
    if (alunos.empty()) {
        cout << "ERRO: Nenhum registro foi lido do CSV. Verifique o caminho do arquivo ou o seu conteudo.\n";
        return 1; // Termina o programa se não houver dados
    }
    
    cout << alunos.size() << " registros carregados da fonte original.\n\n";
    
    // 3. Executa o teste completo para cada formato, usando os dados lidos do seu arquivo.
    testarCicloCompleto(FIXO, "dados_fixo.dat", alunos);
    testarCicloCompleto(DELIMITADO, "dados_delimitado.dat", alunos);
    // CORREÇÃO: Corrigido o erro de digitação de COMPRIMEMTO para COMPRIMENTO
    testarCicloCompleto(COMPRIMEMTO, "dados_comprimento.dat", alunos);

    cout << "Todos os testes foram finalizados.\n";

    return 0;
}





 /*// Cria um objeto Arquivo para manipulação dos registros
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

    return 0;*/