#include "includes/Registro.hpp"
#include "includes/Arquivo.hpp"
#include "includes/RegistroAluno.hpp"
#include <iostream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

// Função para testar um ciclo completo de escrita e leitura
void testarCicloCompleto(Formato formato, const string &nomeArquivo, vector<RegistroAluno> &dadosOriginais)
{
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

    if (dadosLidos.size() != dadosOriginais.size())
    {
        cout << "   ERRO: O numero de registros lidos (" << dadosLidos.size() << ") e diferente do original (" << dadosOriginais.size() << ")!\n";
    }
    else
    {
        cout << "   Sucesso! " << dadosLidos.size() << " registros lidos corretamente.\n";
    }

    // Imprime os registros lidos para inspeção visual
    for (const auto &aluno : dadosLidos)
    {
        cout << "     -> Lido: Mat: " << aluno.matricula << ", Nome: '" << aluno.nome << "', Curso: '" << aluno.curso << "'\n";
    }
    cout << "--- FIM DO TESTE: " << nomeArquivo << " ---\n\n";
}

int main()
{
    // 1. Define o caminho para o seu arquivo CSV de teste.
    //    Assumindo que o executável está na pasta raiz e o CSV em "data/dados.csv"
    const string caminhoCSV = "data/dados.csv";
    cout << "Lendo dados do arquivo '" << caminhoCSV << "'...\n";

    // 2. Lê os dados originais do CSV para a memória
    Arquivo<RegistroAluno> leitorCSV(caminhoCSV, FIXO); // O formato aqui não importa para a leitura do CSV
    vector<RegistroAluno> alunos = leitorCSV.lerRegistroCSV();

    // Verificação para garantir que o CSV foi lido com sucesso
    if (alunos.empty())
    {
        cout << "ERRO: Nenhum registro foi lido do CSV. Verifique o caminho do arquivo ou o seu conteudo.\n";
        return 1; // Termina o programa se não houver dados
    }

    cout << alunos.size() << " registros carregados da fonte original.\n\n";

    // 3. Executa o teste completo para cada formato, usando os dados lidos do seu arquivo.
    testarCicloCompleto(FIXO, "dados_fixo.dat", alunos);
    testarCicloCompleto(DELIMITADO, "dados_delimitado.dat", alunos);
    // CORREÇÃO: Corrigido o erro de digitação de COMPRIMEMTO para COMPRIMENTO
    testarCicloCompleto(COMPRIMENTO, "dados_comprimento.dat", alunos);

    cout << "Todos os testes foram finalizados.\n";

    return 0;
}
