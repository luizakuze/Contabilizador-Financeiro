# Contabilizador Financeiro 💼
> Autora: Luiza Kuze <br>
> Data: 01/05/2023 <br>
> Projeto final de [PRG2](https://github.com/luizakuze/PRG2) <br>

## Descrição 📌

O problema abordado envolve o processamento e a análise de dados de transações financeiras, que estão armazenadas em um arquivo. Cada linha do arquivo representa uma transação e contém informações como o número da transação, tipo de cartão utilizado (nacional ou internacional), tipo da transação (venda, transferência, consumo, etc.), valor da transação e data. O programa é capaz de ler e processar esses dados, proporcionando funcionalidades específicas de acordo com os argumentos fornecidos pelo usuário.

## Objetivos 🎯

- [x] Implementar a estrutura de um vetor dinâmico. 
- [x] Implementar a estrutura de uma tabela hash. 
- [x] Ao receber o nome do arquivo como argumento principal, realizará a contabilização de todas as transações presentes no arquivo. 
- [x] Se o usuário especificar um tipo de transação específico, o programa contabilizará apenas as transações correspondentes a esse tipo.
- [x] Tratars o erros: Usuário informando uma transação inexistente e informar arquivo com formato inválido.

## Funcionamento 💻

### Opção 1 - Contabilização de todas as transações 👩🏻‍💻

```Bash
# Clonar o repositório do projeto 
git clone https://github.com/luizakuze/Contabilizador-Financeiro

# Acessar o diretório 
cd Contabilizador-Financeiro

# Compilar o projeto
g++ main.cpp -o projeto

# Executar o projeto (no linux)
./projeto planilha.csv
```
> O arquivo _planilha.csv_ é o arquivo teste contendo transações. Pode ser alterado, desde que os campos sejam compatíveis com os atuais.

### Opção 2 - Contabilização de uma transação específica 👨🏻‍💻

```Bash
# Clonar o repositório do projeto 
git clone https://github.com/luizakuze/Contabilizador-Financeiro

# Acessar o diretório 
cd Contabilizador-Financeiro

# Compilar o projeto
g++ main.cpp -o projeto

# Executar o projeto (no linux)
./projeto planilha.csv 5067
```
> _5067_ é o tipo de transição específica do arquivo, o usuário pode selecionar qualquer outro número presente no arquivo _planilha.csv_ de exemplos. Caso seja selecionado um tipo inexistente, o programa avisa!

## Implementação 📚

O projeto utiliza duas estruturas de dados principais: uma tabela hash e um vetor dinâmico. Essas estruturas foram implementadas do zero ao longo do semestre, visando aprofundar os conhecimentos relacionados as estruturas de dados.

### Tabela Hash 📕

A tabela hash é utilizada para armazenar e gerenciar os dados das transações financeiras. Aqui estão algumas das principais funções e características da implementação da tabela hash:

- **thash_cria():** Essa função cria uma nova tabela hash inicializada com tamanho zero. A tabela é uma coleção de listas, onde cada lista armazena pares chave-valor.
- **thash_adiciona():** Adiciona um novo par chave-valor à tabela hash. Se a tabela atingir um certo fator de carga, ela é automaticamente expandida para acomodar mais elementos.
- **thash_existe():** Verifica se uma chave específica existe na tabela hash.
- **thash_obtem():** Retorna o valor associado a uma chave específica na tabela hash.
- **thash_remove():** Remove um par chave-valor específico da tabela hash.
- **thash_vetor():** Converte a tabela hash em um vetor dinâmico, o que facilita a ordenação e a manipulação dos dados.
- **thash_destroi():** Libera a memória alocada para a tabela hash quando ela não é mais necessária.


### Vetor Dinâmico 📘

O vetor dinâmico é uma estrutura de dados que permite armazenar uma sequência de elementos de tamanho variável. Aqui estão algumas das principais funções e características da implementação do vetor dinâmico:

- **vetor_cria():** Cria um novo vetor dinâmico inicializado com tamanho zero e capacidade mínima.
- **vetor_anexa():** Adiciona um elemento ao final do vetor dinâmico. Se o vetor estiver cheio, ele é automaticamente expandido para acomodar mais elementos.
- **vetor_insere():** Insere um elemento em uma posição específica do vetor dinâmico, empurrando os elementos subsequentes para a direita.
- **vetor_remove():** Remove um elemento de uma posição específica do vetor dinâmico, deslocando os elementos subsequentes para a esquerda.
- **vetor_obtem():** Retorna o elemento em uma posição específica do vetor dinâmico.
- **vetor_tamanho():** Retorna o número de elementos atualmente no vetor dinâmico.
- **vetor_destroi():** Libera a memória alocada para o vetor dinâmico quando ele não é mais necessário.

Essas estruturas de dados são essenciais para a implementação do "Contabilizador Financeiro", pois permitem armazenar, consultar, modificar e manipular eficientemente os dados das transações financeiras conforme necessário.

## Licença 📜

Este projeto é licenciado sob a [MIT License](https://github.com/luizakuze/Contabilizador-Financeiro/blob/main/license)
