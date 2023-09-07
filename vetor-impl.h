#include "vetor.h"
#include <iostream>
#include <stdexcept>

using std::invalid_argument;

namespace prg2 {

    // Faz a soma circular de pos e offset, conseiderando que a capacidade é dada por cap (incremento circular)
    // Retorna a posição calculada
    // Se quando chamar a função não dar o parâmetro offset, inicializa como 1
    uint32_t soma_circular (uint32_t pos, uint32_t cap, uint32_t offset = 1) {
        pos += offset;
        if (pos >= cap) return pos - cap;
        return pos;
    }

    // Faz a subtração circular de pos e offset, conseiderando que a capacidade é dada por cap (incremento circular)
    // Retorna a posição calculada
    uint32_t subtracao_circular (uint32_t pos, uint32_t cap, uint32_t offset = 1) {
        // uint32_t não preve números negativos!!
        if (offset > pos) return cap + pos - offset;
        return pos - offset;
    }

    template <typename T>
    VetorDinamico<T> vetor_cria() {
        VetorDinamico<T> v;

        v.len = 0;
        v.capacidade = MinSize;
        v.mem = new T[MinSize];
        v.inicio = 0;
        v.fim = 0;

        return v;
    }

    template <typename T>
    void vetor_destroi(VetorDinamico<T> &v) {
        // Libera área de memória para não ocorrer vazamento de memória
        delete[] v.mem;

        // Vetor não pode ser reutilizado
        v.mem = nullptr;
        v.len = 0;
        v.capacidade = 0;
    }

    template <typename T>
    void vetor_expande(VetorDinamico<T> & v) {
        // alocar nova área de memória (auto == int *)
        auto ptr = new T[v.capacidade + MinSize];

        // copiar os dados da área anterior para a nova área
        for (int pos = 0; pos < v.len; pos++) {
            int k = soma_circular(pos, v.capacidade, v.inicio);
            ptr[pos] = v.mem[k];
        }

        // liberar a área anterior
        delete[] v.mem;

        // usar nova área (atribuí-la a v.mem)
        v.mem = ptr;

        // ajusta os indicadores de inicio e fim
        v.inicio = 0;
        v.fim = v.len;

        // alterar v.capacidade
        v.capacidade += MinSize;
    }

    template <typename T>
    void vetor_anexa(VetorDinamico<T> &v, const T& valor) {
        // O vetor deve ser expandido, caso esteja cheio
        if (v.len == v.capacidade) vetor_expande(v);

        // Armazena dado na primeira posição livre (fim)
        v.mem[v.fim] = valor;
        v.fim = soma_circular(v.fim, v.capacidade);
        v.len++;
    }

    template <typename T>
    void vetor_insere(VetorDinamico<T> &v, const T& valor) {
        vetor_insere(v, 0, valor);
    }

    template <typename T>
    void vetor_insere(VetorDinamico<T> &v, int pos, const T& valor) {
        // Teste de consistência
        if(pos > v.len) {
            throw invalid_argument("posicao invalida");
        }

        // Se a última posição "livre" for igual a posição inicial
        if (v.fim == v.inicio) vetor_expande(v);

        for (int j = v.len; j > pos; j--) {
            int k = soma_circular(j, v.capacidade, v.inicio);
            int m = soma_circular(j-1, v.capacidade, v.inicio);
            v.mem[k] = v.mem[m];
        }

        // Coloca o novo valor na pos
        pos = soma_circular(pos, v.capacidade, v.inicio);
        v.mem[pos] = valor;
        v.len++;
        v.fim = soma_circular(v.fim, v.capacidade);
    }

    template <typename T>
    T &vetor_frente(VetorDinamico<T> &v) {
        if (v.len == 0) {
            throw invalid_argument("vetor vazio");
        }
        return v.mem[v.inicio];
    }

    template <typename T>
    T &vetor_atras(VetorDinamico<T> &v) {
        if (v.len == 0) {
            throw invalid_argument("vetor vazio");
        }
        uint32_t ultimo = subtracao_circular(v.fim, v.capacidade); // pos ultimo dado

        return v.mem[ultimo];
    }

    template <typename T>
    void vetor_remove_inicio(VetorDinamico<T> &v) {
        if (v.len == 0) {
            throw invalid_argument("posicao invalida");
        }

        v.inicio = soma_circular(v.inicio, v.capacidade);
        v.len--;
    }

    template <typename T>
    void vetor_remove_fim(VetorDinamico<T> &v) {
        if (v.len == 0) {
            throw invalid_argument("vetor vazio");
        }
        // "dado removido"
        v.fim = subtracao_circular(v.fim, v.capacidade);
        v.len--;
    }

    template <typename T>
    void vetor_remove(VetorDinamico<T> &v, int pos) {
        if (pos >= v.len) {
            throw invalid_argument("posicao invalida");
        }

        // Move os dados da frente da posicao
        for (int j = pos+1; j < v.len; j++) {
            int k = soma_circular(j, v.capacidade, v.inicio);
            int m = soma_circular(j-1, v.capacidade, v.inicio);
            v.mem[m] = v.mem[k];
        }

        v.len--;
        v.fim = subtracao_circular(v.fim, v.capacidade);
    }

    template <typename T>
    bool vetor_vazio(const VetorDinamico<T> &v) {
        return v.len == 0;
    }

    template <typename T>
    T &vetor_obtem(VetorDinamico<T> &v, int pos) {
        // Testa se pos é válida, e dispara exceção
        if (v.len <= pos) {
            throw invalid_argument("posicao invalida");
        }
        // Ajustar pos de acordo com o deslocamento
        pos = soma_circular(pos, v.capacidade, v.inicio);

        return v.mem[pos];
    }

    template <typename T>
    const T & vetor_obtem(const VetorDinamico<T> &v, int pos) {

    }

    template <typename T>
    int vetor_tamanho(const VetorDinamico<T> &v) {
        return v.len;
    }

    template <typename T>
    int vetor_capacidade(const VetorDinamico<T> &v) {
        return v.capacidade;
    }

    template <typename T>
    void vetor_limpa(VetorDinamico<T> &v) {
        v.len = 0;
        v.inicio = 0;
        v.fim = 0;
    }

    template <typename T>
    void vetor_ordena(VetorDinamico<T> &v) {

        // Para j do fim até a segunda nodo da sequência
        for (int j = v.len; j >= soma_circular(v.inicio+1, v.capacidade, v.inicio); j--) {

            // Para k do inicio da sequência até o antecessor da posição j
            for (int k = v.inicio; k < j-1; k++) {

                //Se valor na posição k+1 < valor na posição k então troca os valores das posições k e k+1
                if (vetor_obtem(v, k+1) < vetor_obtem(v, k)) {
                    T aux = v.mem[k+1];
                    v.mem[k+1] = v.mem[k];
                    v.mem[k] = aux;
                }
            }
        }

    }


}