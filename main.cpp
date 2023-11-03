/**
 * @authors Guilherme M. Taglietti - 192370
 *          José Paulo R. Pereira - 192445
 * 
 * @file Arquivo principal
*/
#include "src/boards.cpp"
#include "src/sudoku.cpp"
// using namespace UPF; --> Poderia inibir de invocar o namespace toda hora

int main(){
    UPF::Sudoku sdk;
    std::array<char, 81> const sdkboard = UPF::boards::evil; // Aqui pode trocar para outros boards com outras dificuldades (Que estão no boards.cpp)
    // Sudoku sdk(sdkboard) --> Poderia passar o board direto, mas assim mostra que tem como usar um set depois para definir quando quiser...
    sdk.set_board(sdkboard);
    std::cout << "Sudoku original antes do backtracking:\n\n" << sdk << "\n";
    sdk.solve();
    std::cout << "Sudoku após o backtracking:\n\n" << sdk << "\n";
    return 0;
}