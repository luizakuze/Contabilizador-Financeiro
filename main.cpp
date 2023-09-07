#include <iostream>
#include "thash.h"
#include "vetor.h"

using namespace prg2;
using namespace std;

// Função que indica como o vetor deve ser ordenado
bool operator<(const Par<int,float> & p1, const Par<int,float> & p2) {
    return (p1.chave < p2.chave);
}

// Função que imprime o resultado da contabilidade de movimentações
void imprime_resultado (VetorDinamico<Par<int, float>> & v) {

    ofstream resultado("contabilidade.csv");
    if (!resultado.is_open()) {
        cerr << "Erro ao criar arquivo de resultados!" << endl;
        abort();
    }

    // Imprime a contabilidade
    for (int i = 0; i < vetor_tamanho(v); i++) {
        Par p = vetor_obtem(v, i);
        resultado << p.chave << ',' << p.valor << endl;
    }

}

// Função que separa uma string em substrings dado um delimitador "sep"
VetorDinamico<string> separa(const string & caminho, const char & sep) {

    auto sequencia = vetor_cria<string>();
    int pos1 = caminho.find_first_not_of(sep);

    while (pos1 != string::npos) {
        int pos2 = caminho.find(sep, pos1 + 1);
        if (pos2 != string::npos) {
            string trecho = caminho.substr(pos1, pos2 - pos1);
            vetor_anexa(sequencia, trecho);
        } else {
            string trecho = caminho.substr(pos1);
            vetor_anexa(sequencia, trecho);
            break;
        }
        pos1 = caminho.find_first_not_of(sep, pos2 + 1);
    }
    return sequencia;
}

// Função que altera o valor de alguma movimentação já existente
void thash_altera(thash<int, float> &tab, const int &chave, const float & alteracao) {

    auto pos = f_hash(chave, tab.tabela.size());

    // Encontra o valor a ser alterado
    for (auto & par: tab.tabela[pos]) {
        if (par.chave == chave) {

            // Faz a alteração no valor
            par.valor += alteracao;
            return;
        }
    }
}

// Função que analisa a planilha e contabiliza todas as movimentações de todos os tipos
void total_movimentacao (const string & arquivo, thash<int,float> & tabela) {

    ifstream planilha(arquivo);
    if (!planilha.is_open()) {
        cerr << "Arquivo inválido!" << endl;
        abort();
    }

    bool primeira_linha = true;

    string linha;
    while (getline(planilha, linha)){

        // Ignora a primeira linha do arquivo com cabeçalho da planilha
        if (primeira_linha) {
            primeira_linha = false;
            continue;
        }

        // Adiciona os campos da planilha no vetor
        VetorDinamico<string> separador = separa(linha, ',');

        int chave = stoi(vetor_obtem(separador, 0));
        float valor = stof(vetor_obtem(separador, 4));

        // Se já houver um produto com essa chave,
        if (thash_existe(tabela, chave)) {

            // ...adiciona a nova movimentação ao valor que já tinha
            thash_altera(tabela, chave, valor);

        } else {
            // Se não, adiciona essa nova movimentação, ou seja, nova chave
            thash_adiciona(tabela, chave, valor);
        }
    }
}

// Função que analisa a planilha e contabiliza somente as movimentações de um tipo específico
void tipo_movimentacao (const string & arquivo, thash<int,float> & tabela, const int & tipo_especifico) {

    ifstream planilha(arquivo);
    if (!planilha.is_open()) {
        cerr << "Arquivo inválido!" << endl;
        abort();
    }

    bool primeira_linha = true;
    bool tipo_existe = false;

    string linha;
    while (getline(planilha, linha)) {

        // Ignora a primeira linha do arquivo com cabeçalho da planilha
        if (primeira_linha) {
            primeira_linha = false;
            continue;
        }

        // Adiciona os campos da planilha no vetor
        VetorDinamico<string> separador = separa(linha, ',');

        int chave = stoi(vetor_obtem(separador, 0));
        int tipo = stoi(vetor_obtem(separador, 3));
        float valor = stof(vetor_obtem(separador, 4));

        // Analisa somente produtos com o TIPO específico de movimentação
        if (tipo_especifico == tipo) {
            tipo_existe = true;
            // Se já houver um produto com essa chave,
            if (thash_existe(tabela, chave)) {

                // ...adiciona a nova movimentação ao valor que já tinha
                thash_altera(tabela, chave, valor);

            } else {
                // Se não, adiciona essa movimentação
                thash_adiciona(tabela, chave, valor);
            }
        }
    }
    // O usuário selecionou um tipo que não existe para ser analisado
    if (!tipo_existe) {
        cerr << "Tipo de movimentação não existe!" << endl;
        abort();
    }
}

int main(int argc, char *argv[]) {

    // A chave é um "produto" e o valor é a "movimentação"
    auto tab = thash_cria<int, float>();

    // Se o usuário não escolher um tipo,
    if (argc == 2) {
        string arquivo = argv[1];

        //...verifica todas as movimentações
        total_movimentacao(arquivo, tab);
    }

    // Se escolher um tipo específico,
    else if (argc == 3) {
        string arquivo = argv[1];
        int tipo = stoi(argv[2]);

        //...verifica as movimentações somente desse tipo
        tipo_movimentacao(arquivo, tab, tipo);
    }

    // Erro caso não hajam os argumentos necessários
    else {
        cerr << "Erro ao informar tipo de movimentação!" << endl;
        return 1;
    }

    // Transforma a tabela em um vetor
    auto v = vetor_cria<Par<int, float>>();
    v = thash_vetor(tab);

    // Mostra as movimentações ordenadas
    vetor_ordena(v);
    imprime_resultado(v);

    vetor_destroi(v);
    thash_destroi(tab);

    return 0;
}