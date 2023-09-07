#ifndef THASH_THASH_IMPL_H
#define THASH_THASH_IMPL_H

#include "vetor.h"
using namespace std;

namespace prg2 {

    inline unsigned int f_hash(const string & chave, int N);
    inline unsigned int f_hash(const int & chave, int N);
    inline unsigned int f_hash(const long & chave, int N);
    inline unsigned int f_hash(const float & chave, int N);
    inline unsigned int f_hash(const double & chave, int N);

    template <typename K, typename V>
    thash<K, V> thash_cria() {
        thash<K, V> tab;

        tab.tamanho = 0;

        tab.tabela.assign(TabSize, list<Par<K, V>>{});
        // mesma coisa que:
        // for (int i = 0; i < tab.tabela.size(); i++ {
        //      tab.tabela.push_back(list<Par<V>>{});
        // }

        return tab;
    }

    template <typename K,typename V>
    void thash_destroi(thash<K, V> &tab) {

        if(tab.tamanho > 0) {
            // Limpa o vector, despois disso ele estará vazio
            tab.tabela.clear();

            // Limpa a memória utilizada pelo vector (ajustar ela)
            tab.tabela.shrink_to_fit();

            tab.tamanho = 0;
        }
    }

    unsigned int f_hash_simples(const uint8_t * ptr, int len, int N) {
        unsigned int soma = 0;

        for (int k = 0; k < len; k++) {
            soma = ((soma << 8) + ptr[k]) % N;
        }

        return soma % N;
    }

    unsigned int f_hash(const string & chave, int N) {
        return f_hash_simples((uint8_t*)chave.c_str(), chave.size(), N);
//        unsigned int soma = 0;
//
//        for (auto & c: chave) {
//            soma = ((soma << 8) + c) % N;
//        }
//        return soma % N;
    }

    inline unsigned int f_hash(const long & chave, int N) {
        return chave % N;
    }

    unsigned int f_hash(const int & chave, int N) {
        return chave % N;
    }

    unsigned int f_hash(const float & chave, int N) {
        return f_hash_simples((uint8_t*)&chave, sizeof(chave), N);
    }

    unsigned int f_hash(const double & chave, int N) {
        return f_hash_simples((uint8_t*)&chave, sizeof(chave), N);
    }

    // Expande a tabela, de fomra que dobre a quantidade de linhas
    // Os áres devem ser redistribuídas na tabela (rehashing)
    template <typename K, typename V>
    void thash_expande (thash<K, V> & tab) {

        // Criar uma tabela com o dobro de tamanho da tabela atual
        vector<list<Par<K, V>>> nova(tab.tabela.size()*2);
        // auto nova = thash_cria<V >();
        // nova.tabela.rezise(2*tab.tabela.size());

        // Para cada linha (lista) da tabela atual
        for (auto & lista: tab.tabela) {

            // Para cada par que encontrar dessa lista
            for (auto & par: lista) {

                // Calcular um novo hash para cada chave
                auto pos = f_hash(par.chave, nova.size());

                // Adiciona o par a nova tabela
                nova[pos].push_back(par);
            }
        }

        // Substituir a tabela anterior pela nova
        tab.tabela = nova;
    }

    template<typename K, typename V>
    void thash_adiciona(thash<K, V> &tab, const K &chave, const V &valor) {
        // Calcula o fator de carga (aqui pra não dar problema de ser float, armazenamos em outra var.)
        float fator = 1 + tab.tamanho; // leva em conta o novo par que está sendo adicionado
        fator /= tab.tabela.size();

        if (fator > FatorCarga) {
            // Expande a tabela. Vai ser uma operação custosa !!
            thash_expande(tab);
        }

        auto pos = f_hash(chave, tab.tabela.size());
        auto &lista = tab.tabela[pos];

        // Caso a lista estiver vazia
        if (lista.empty()) {
            lista.push_back(Par<K, V>{chave,valor});
        } else {
            // Encontra um par que não tenha chave igual a chave a ser acrescentada
            for (auto & par: lista) {
                // Se encontrar, sobrecreve o valor e TERMINA
                if (par.chave == chave) {
                    par.valor = valor;
                    return;
                }
            }
            // Se não encontrar uma chave igual, então acrescenta um novo par
            lista.push_back(Par<K, V>{chave,valor});
        }
        tab.tamanho++;
    }

    template<typename K, typename V>
    bool thash_existe(const thash<K, V> &tab, const K &chave) {
        auto pos = f_hash(chave, tab.tabela.size());

        auto & lista = tab.tabela[pos];
        for (auto & par: lista) {
            if (par.chave == chave) {
                // não pode retornar par.chave == chave, pois em uma coluna tem mais de um chave (testar todas)
                return true;
            }
        }
        return false;
    }

    template<typename K, typename V>
    V thash_obtem(thash<K, V> &tab, const K &chave) {

        // Encontra posição a partir da função hash
        auto pos = f_hash(chave, tab.tabela.size());

        // Acessa o ponteiro para o Par existente na posição calculada
        auto & lista = tab.tabela[pos];

        for (auto & par : lista) {
            // Procura se tem algum par com a chave procurada
            if (par.chave == chave) {
                return par.valor;
            }
        }
        throw invalid_argument("posicao nao esta ocupada");
    }

    template<typename K, typename V>
    void thash_remove(thash<K, V> &tab, const K &chave) {
        // Encontra posição da chave a partir da função hash
        auto pos = f_hash(chave, tab.tabela.size());

        auto & lista = tab.tabela[pos];

        // Percorre a lista para encontrar se há algum dado com a mesma chave p remover
        for (auto it = lista.begin(); it != lista.end(); it++) {
            if (chave == it->chave) {
                lista.erase(it);
                tab.tamanho--;
                return;
            }
        }
        throw invalid_argument("chave nao existe");

    }

    template<typename K, typename V>
    bool thash_vazio(const thash<K, V> &tab) {
        return tab.tamanho == 0;
    }

    template<typename K, typename V>
    uint32_t thash_tamanho(const thash<K, V> &tab) {
        return tab.tamanho;
    }

    template <typename K, typename V>
    VetorDinamico<Par<K, V>> thash_vetor (const thash<K, V> & tab) {

        auto v = vetor_cria<Par<K, V>>();

        // Se a tabela estiver vazia, dispara exceção
        if (tab.tamanho <= 0) {
            throw invalid_argument("tabela vazia");
        }

        for (auto & lista: tab.tabela) {
            for (auto &par: lista) {

                // Adiciona novo par no vetor
                vetor_anexa(v,par);
            }
        }

        return v;
    }

#endif //THASH_THASH_IMPL_H
}