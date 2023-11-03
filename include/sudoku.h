/**
 * @authors Guilherme M. Taglietti - 192370
 *          José Paulo R. Pereira - 192445
 * 
 * @headerfile Arquivo header de definição das funções e da classe que vão ser usadas
*/

/// Include guard para o compilador (Evita incluir arquivos repitidos e recompilação desnecessária)
#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <vector>
#include <array>
#include <bitset>

namespace UPF{

constexpr std::size_t get_cell(std::size_t row, std::size_t col) noexcept;
constexpr std::size_t get_next_row(std::size_t row, std::size_t col) noexcept;
constexpr std::size_t get_next_col(std::size_t col) noexcept;

class Sudoku{
public:
    Sudoku();
    Sudoku(std::vector<std::vector<char>> &board);
    Sudoku(std::array<char, 81> const board);
    /// Desabilitado o construtor de cópia para evitar instâncias iguais (Evita uns erros desnecessários...)
    Sudoku(const Sudoku &other) = delete; 
    virtual ~Sudoku();
    void set_board(std::vector<std::vector<char>> &board);
    void set_board(std::array<char, 81> const board);
    void solve();
    friend std::ostream& operator<<(std::ostream &os, const Sudoku &sdk);
    /// Desabilitado o operador de atribuição pelo mesmo motivo do construtor de cópia
    Sudoku& operator=(const Sudoku &rhs) = delete;

private:
    std::vector<std::vector<char>> BOARD;
    constexpr std::pair<std::size_t, std::size_t> next_empty_position(std::size_t row, std::size_t col) noexcept;
    bool backtrack(std::size_t const row_start, std::size_t const col_start,
                   std::array<std::bitset<9>, 9> &row_contains,
                   std::array<std::bitset<9>, 9> &col_contains,
                   std::array<std::bitset<9>, 9> &cell_contains) noexcept;
    std::vector<std::vector<char>> prepare(std::array<char, 81> const flat_board);
    
};

} 

#endif