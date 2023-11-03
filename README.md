# Sudoku++

Projeto desenvolvido com o objetivo de resolver sudoku usando um backtracking recursivo e uma implementação eficiente.

## Compilação e Execução

### Usando o Makefile

1. Navegue até o diretório do projeto no terminal.
2. Execute `make` para compilar o projeto.
3. Após compilar, execute `./main` para rodar o solver.
4. Em caso de erros, execute `make clean` e repita os passos acima.
5. Caso não tenha o `make` instalado, execute os seguintes comandos:

`sudo apt install build-essential`
`sudo apt install make`

### Compilação Manual

1. Navegue até o diretório do projeto no terminal.
2. Compile usando `g++ main.cpp -o main -Wall`.
3. Após compilar, execute `./main` para rodar o solver.

## Linguagem de Programação e Compilador

- **Linguagem:** C++
- **Compilador:** G++17 (Padrão C++17)

## Descrição do Algoritmo

O algoritmo foi implementado usando a técnica de backtracking para resolver Sudoku. O Sudoku é um quebra-cabeça de números onde o objetivo é preencher uma grade 9x9 com dígitos de 1 a 9, garantindo que cada coluna, cada linha e cada um dos nove subgrids 3x3 contenham todos os dígitos de 1 a 9.

## Detalhes Específicos da Implementação

- **Estruturas de Dados:** A grade Sudoku é representada por um vetor 2D de caracteres. Além disso, um array de tamanho 81 é usado para facilitar a entrada dos tabuleiros Sudoku. Bitsets são empregados para uma rápida validação de atribuições de números em linhas, colunas e blocos 3x3.
- **Heurísticas:** O algoritmo utiliza heurísticas simples para otimizar a busca, incluindo a escolha da próxima célula vazia e uma validação rápida das atribuições.
- **Bitsets para Validação Rápida:** Para verificar a validade de uma atribuição de número em linhas, colunas e blocos 3x3, são utilizados bitsets. Cada linha, coluna e bloco 3x3 possui um bitset correspondente, onde cada bit representa a presença de um número, permitindo operações de O(1).
