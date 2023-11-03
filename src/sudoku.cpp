/**
 * @authors Guilherme M. Taglietti - 192370
 *          José Paulo R. Pereira - 192445
 * 
 * @file Arquivo de implementação das funções membro do header "sudoku.h"
*/
#include "../include/sudoku.h"

namespace UPF{

/**
 * @name get_cell
 * @namespace UPF
 * @brief Obtém o índice do bloco (parte 3x3 do sudoku) que a linha e a coluna pertencem
 * @param row Linha da matriz
 * @param col Coluna da matriz
 * @return Índice do bloco que a linha e a coluna pertencem
*/
inline constexpr std::size_t get_cell(std::size_t row, std::size_t col) noexcept{
    return (row / 3) * 3 + col / 3;
}

/**
 * @name get_next_row
 * @namespace UPF
 * @brief Obtém a próxima linha da matriz (Quando atingir o final de uma linha, assim sabe se já percorreu ou não todos os números de uma linha)
 * @param row Linha da matriz
 * @param col Coluna da matriz
 * @return Próxima linha da matriz que o backtrack irá usar
*/
inline constexpr std::size_t get_next_row(std::size_t row, std::size_t col) noexcept{
    return row + (col + 1) / 9;
}

/**
 * @name get_next_col
 * @namespace UPF
 * @brief Obtém a próxima coluna da matriz (Quando atingir o final de uma coluna, assim sabe se já percorreu ou não todos os números de uma coluna)
 * @param col Coluna da matriz
 * @return Próxima coluna da matriz que o backtrack irá usar
*/
inline constexpr std::size_t get_next_col(std::size_t col) noexcept{
    return (col + 1) % 9;
}

/**
 * @namespace UPF
 * @class Sudoku
 * @brief Construtor padrão da classe
*/
UPF::Sudoku::Sudoku(){}

/**
 * @overload
 * @namespace UPF
 * @class Sudoku
 * @brief Atribui uma matriz para a matriz da classe (Matriz que o backtrack vai usar)
 * @param board Matriz do sudoku
*/
UPF::Sudoku::Sudoku(std::vector<std::vector<char>> &board){
    BOARD = board;
}

/**
 * @overload
 * @namespace UPF
 * @class Sudoku
 * @brief Converte um array para matriz de sudoku e atribui para a matriz da classe (Matriz que o backtrack vai usar)
 * @param board Matriz do sudoku
 * @note O array foi usado pois é mais fácil e menos chato escrever um sudoku em um array, não precisa ficar separando as linhas e colunas...
*/
UPF::Sudoku::Sudoku(std::array<char, 81> const board){
    BOARD = prepare(board);
}

/**
 * @namespace UPF
 * @class Sudoku
 * @brief Destrutor virtual da classe
 * @attention Não precisou ser usado nesse caso (Não tem nada alocado dinamicamente), mas é sempre uma boa prática declarar...
*/
UPF::Sudoku::~Sudoku(){}

/**
 * @name set_board
 * @namespace UPF
 * @class Sudoku
 * @brief Atribui uma matriz para a matriz da classe que o backtrack vai usar
 * @param board Matriz que vai se tornar a matriz da classe
*/
inline void UPF::Sudoku::set_board(std::vector<std::vector<char>> &board){
    BOARD = board;
}

/**
 * @overload
 * @name set_board
 * @namespace UPF
 * @class Sudoku
 * @brief Converte um array para matriz que vai ser usada pelo backtrack
 * @param board Array que vai se tornar a matriz da classe
*/
inline void UPF::Sudoku::set_board(std::array<char, 81> const board){
    BOARD = prepare(board);
}

/**
 * @name solve
 * @namespace UPF
 * @class Sudoku
 * @brief Resolve o sudoku (caso seja um sudoku possível...)
*/
void UPF::Sudoku::solve(){
    std::array<std::bitset<9>, 9> row_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::array<std::bitset<9>, 9> col_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::array<std::bitset<9>, 9> cell_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(std::size_t row = 0; row < 9; row++){
        for(std::size_t col = 0; col < 9; col++){
            char digit;
            if((digit = BOARD[row][col]) != '.'){
                std::size_t digit_idx = digit - '1';
                row_contains[row].set(digit_idx);
                col_contains[col].set(digit_idx);
                std::size_t cell = get_cell(row, col);
                cell_contains[cell].set(digit_idx);
            }
        }
    }
    backtrack(0, 0, row_contains, col_contains, cell_contains);
}

/**
 * @name next_empty_position
 * @namespace UPF
 * @class Sudoku
 * @brief Encontra a próxima posição vazia que um par de linha/coluna fazem parte
 * @param row Linha da matriz
 * @param col Coluna da matriz
 * @return Par contendo os índices (linha/coluna) da próxima posição vazia 
*/
constexpr std::pair<std::size_t, std::size_t> UPF::Sudoku::next_empty_position(std::size_t row, std::size_t col) noexcept{
    while(row != 9){
        if(BOARD[row][col] == '.') return {row, col};
        row = get_next_row(row, col);
        col = get_next_col(col);
    }
    return {9, 0};
}

/**
 * @brief Realiza o backtracking de maneira recursiva para resolver o sudoku
 *
 * A função utiliza o algoritmo de backtracking para encontrar uma solução para o sudoku,
 * começando da posição row_start e col_start, e então, tenta resolver o sudoku
 *
 * @param row_start Linha da matriz em que o backtracking irá iniciar
 * @param col_start Coluna da matriz em que o backtracking irá iniciar
 * @param row_contains Um array de bitsets representando a presença dos números nas linhas
 * @param col_contains Um array de bitsets representando a presença dos números nas colunas
 * @param cell_contains Um array de bitsets representando a presença dos números nos blocos 3x3
 * @return Verdadeiro se encontrar uma solução válida, falso caso contrário
 *
 * A função utiliza uma abordagem de tentativa e erro para preencher os espaços vazios, verificando se um 
 * número de 1 a 9 pode ser colocado em uma posição vazia, respeitando as regras do jogo 
 * (números não podem se repetir em uma linha, coluna ou bloco 3x3). Se um número válido
 * é encontrado, a função faz a recursão para tentar preencher a próxima posição vazia.
 * 
 * @note O uso dos bitsets é pelo fato de como cada linha, coluna e bloco 3x3 poder conter números de 1 a 9, usando um biteset 
 * cada bit representa um número possível no intervalo de 1 a 9, então se um bit está definido em um bitset, 
 * isso indica que o número correspondente está na linha, coluna ou bloco 3x3 associado. Fora isso, as operações normalmente são em O(1),
 * que otimiza MUITO o código
 */
bool UPF::Sudoku::backtrack(std::size_t const row_start, std::size_t const col_start,
                               std::array<std::bitset<9>, 9> &row_contains,
                               std::array<std::bitset<9>, 9> &col_contains,
                               std::array<std::bitset<9>, 9> &cell_contains) noexcept
{
    auto [row, col] = next_empty_position(row_start, col_start);
    if(row == 9) return true;
    std::size_t const cell = get_cell(row, col);
    std::bitset<9> const contains = row_contains[row] | col_contains[col] | cell_contains[cell];
    if(contains.all()) return false;
    for(std::size_t digit_idx = 0; digit_idx < 9; digit_idx++){
        if(!contains[digit_idx]){
            BOARD[row][col] = static_cast<char>(digit_idx + '1');
            row_contains[row].set(digit_idx);
            col_contains[col].set(digit_idx);
            cell_contains[cell].set(digit_idx);
            if(backtrack(row, col, row_contains, col_contains, cell_contains)) return true;
            row_contains[row].reset(digit_idx);
            col_contains[col].reset(digit_idx);
            cell_contains[cell].reset(digit_idx);
        }
    }
    BOARD[row][col] = '.';
    return false;
}

/**
 * @name prepare
 * @namespace UPF
 * @class Sudoku
 * @brief Prepara/converte o array em uma matriz que vai ser usada pelo backtrack
 * @param flat_board Array que simula um tabuleiro de sudoku reto, com 81 de tamanho
 * @return Matriz que vai ser usada pelo backtrack
*/
std::vector<std::vector<char>> UPF::Sudoku::prepare(std::array<char, 81> const flat_board){
    std::vector<std::vector<char>> board;
    board.reserve(9);
    for(std::size_t row = 0; row < 9; ++row){
        std::vector<char> this_row;
        this_row.reserve(9);
        for(std::size_t col = 0; col < 9; ++col)
            this_row.push_back(flat_board[row * 9 + col]);
        board.push_back(this_row);
    }
    return board;
}

/**
 * @overload
 * @namespace UPF
 * @class Sudoku
 * @brief Overload do operador de fluxo para poder usar o cout e evitar de criar uma função membro específica para mostrar a matriz,
 *        além de desacoplar o código da saída padrão
 * @param os Output que vai receber os dados
 * @param sdk Instância da classe Sudoku
 * @return Saída com os dados
*/
std::ostream& operator<<(std::ostream &os, const UPF::Sudoku &sdk){
    for(std::size_t row = 0; row < 9; row++){
        if(row % 3 == 0 && row != 0) os << "---------------------\n";
        for(std::size_t col = 0; col < 9; col++){
            if(col % 3 == 0 && col != 0) os << "| ";
            os << sdk.BOARD[row][col] << " ";
        }
        os << "\n";
    }
    return os;
}

}