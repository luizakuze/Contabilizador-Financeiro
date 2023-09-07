#ifndef DYNARRAY_VETOR_H
#define DYNARRAY_VETOR_H


#include <cstdint>

namespace prg2 {

    // tamanho de cada expansão de capacidade do vetor, em posições
    const int MinSize = 8;

    // O tipo VetorDinamico
    template <typename T>
    struct VetorDinamico {
        // como definir a área de memória de armazenamento ??
        T* mem;

        uint32_t len; // quantos dados estão armazenados
        uint32_t capacidade; // qual a capacidade

        // posição do primeiro dado armazenado e da primeira posição livre (FILA CIRCULAR)
        uint32_t inicio, fim;
    };

    // operações do VetorDinamico

    // cria um VetorDinamico com capacidade inicial dada por
    // MinSize
    template <typename T>
    VetorDinamico<T> vetor_cria();

    // Destroi um vetor (destrutor)
    template <typename T>
    void vetor_destroi(VetorDinamico<T> &v);

    // Acrescenta um valor ao final do vetor
    // Expande o vetor, caso necessário. A expansão
    // aloca uma capacidade adicional dada por MinSize
    template <typename T>
    void vetor_anexa(VetorDinamico<T> &v, const T& valor);

    // Insere um valor no início do vetor
    // Expande o vetor, caso necessário. A expansão
    // aloca uma capacidade adicional dada por MinSize
    template <typename T>
    void vetor_insere(VetorDinamico<T> &v, const T& valor);

    // Insere um valor na posição pos do vetor
    // Expande o vetor, caso necessário. A expansão
    // aloca uma capacidade adicional dada por MinSize
    // Dispara exceção se pos > tamanho do vetor
    template <typename T>
    void vetor_insere(VetorDinamico<T> &v, int pos, const T& valor);

    // Acessa o dado da frente da vetor
    // se vetor vazia: o que acontece ????
    // DISPARA EXCEÇÃO do tipo invalid_argument]
    template <typename T>
    T & vetor_frente(VetorDinamico<T> & v);

    // Acessa o dado do final do vetor
    // se vetor vazia: o que acontece ????
    // DISPARA EXCEÇÃO do tipo invalid_argument
    template <typename T>
    T & vetor_atras(VetorDinamico<T> & v);

    // remove o dado do início
    // se vetor vazia: DISPARA EXCEÇÃO do tipo invalid_argument
    template <typename T>
    void vetor_remove_inicio(VetorDinamico<T> & v);

    // remove o dado do fim
    // se vetor vazia: DISPARA EXCEÇÃO do tipo invalid_argument
    template <typename T>
    void vetor_remove_fim(VetorDinamico<T> & v);

    // retorna true se vetor estiver vazio
    template <typename T>
    bool vetor_vazio(const VetorDinamico<T> & v);

    // Acessa um dado que está na posição pos do vetor
    // Obtém uma referência mutável ao dado
    // Se pos > tamanho-1, dispara exceção
    template <typename T>
    T & vetor_obtem(VetorDinamico<T> &v, int pos);

    // Acessa um dado que está na posição pos do vetor
    // Obtém uma referência somente-leitura ao dado
    // Se pos > tamanho-1, dispara exceção
    template <typename T>
    const T & vetor_obtem(const VetorDinamico<T> &v, int pos);

    // Remove um dado da posição pos do vetor
    // Se pos > tamanho-1, dispara exceção
    template <typename T>
    void vetor_remove(VetorDinamico<T> &v, int pos);

    // Obtem o tamanho do vetor
    template <typename T>
    int vetor_tamanho(const VetorDinamico<T> &v);

    // Obtem a capacidade do vetor (quantos dados cabem no total com a memória atualmente alocada)
    template <typename T>
    int vetor_capacidade(const VetorDinamico<T> & v);

    // Esvazia o vetor
    template <typename T>
    void vetor_limpa(VetorDinamico<T> &v);

    // Expande a capacidade do vetor
    // A nova capacidade será >= capacidade solicitada
    // capacidade deve ser maior que capacidade atual, senão dispara exceção
    template <typename T>
    void vetor_expande(VetorDinamico<T> &v, int capacidade);

    // Ordena o vetor
    template <typename T>
    void vetor_ordena(VetorDinamico<T> &v);
}

#include "vetor-impl.h" // para dividir os arquivos .h

#endif //DYNARRAY_VETOR_H