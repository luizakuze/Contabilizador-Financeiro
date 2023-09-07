#ifndef THASH_THASH_H
#define THASH_THASH_H

#include <string>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <list>
#include "vetor.h"
#include <fstream>

using std::string;
using std::vector;
using std::list;

namespace prg2 {

    const uint32_t TabSize = 32;
    const float FatorCarga = 1.0;

    template <typename K, typename V>
    struct Par {
        K chave;
        V valor;
    };

    // Uma tabela hash com chaves do tipo string, e valores so tipo genérico
    template <typename K, typename V>
    struct thash {
        // Quantidade de chaves armazenadas
        uint32_t tamanho;

        // A área de armazenamento da tabela. Posições livres estão com nullptr
        // O vector vai ser a quantidade de linhas da tabela!!!
        vector<list<Par<K, V>>> tabela;
    };

    // Cria uma tabela hash
    template <typename K, typename V>
    thash<K, V> thash_cria();

    // Destroi uma tabela hash
    template <typename K, typename V>
    void thash_destroi(thash<K, V> & tab);

    template <typename K>
    unsigned int f_hash(const K & chave, int N);

    // Adiciona à tabela um par formado por valor e chave
    template <typename K, typename V>
    void thash_adiciona(thash<K, V> & tab, const K & chave, const V & valor);

    // Verifica se uma chave existe na tabela
    template <typename K, typename V>
    bool thash_existe(const thash<K, V> & tab, const K & chave);

    // Obtem o valor associado à chave
    // Se chave não existir, dispara uma exceção std::invalid_argument
    template <typename K, typename V>
    V thash_obtem(thash<K, V> & tab, const K & chave);

    // Remove da tabela uma chave e seu valor asdociado
    // Se chave não existir, dispara uma exceção std::invalid_argument
    template <typename K, typename V>
    void thash_remove(thash<K, V> & tab, const K & chave);

    // Verifica se a tabela está vazia
    template <typename K, typename V>
    bool thash_vazio(const thash<K, V> & tab);

    // Retorna a quantidade de chaves armazenadas na tabela
    template <typename K, typename V>
    uint32_t thash_tamanho(const thash<K, V> & tab);

    // Transforma a tabela hash em um vetor dinâmico
    template <typename K, typename V>
    VetorDinamico<Par<K, V>> thash_vetor (const thash<K, V> & tab);
}

#include "thash-impl.h"
#endif //THASH_THASH_H
