#include <iostream>
using namespace std;

const int rows = 6, columns = 7;

class Game {
private:

    char** board;
    //  1 = player1
    // -1 = player2
    int player;
    char simbolito;

public:

    Game();
    Game(char** board, int player) { this->board = board; this->player= player; };
    Game(char** board, int player, char simbolito) { this->board = board; this->player= player; this->simbolito = simbolito; };
    
    void next_player() {
        player*= -1;
    }

    void update_simbolito() {
        if (player== 1) {
            simbolito = 'X';
        }
        else {
            simbolito = 'O';
        }
    }

    void lfill_board() {
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                board[i][j] = '.';
            }
        }
    }

    void show_board() {

        // X : player1
        // O : player2
        system("cls");
        cout << "\n   1     2     3     4     5     6     7\n\n";

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << "|  " << board[j][i] << "  ";
            }
            cout << "|" << endl;
        }
        cout << endl;
    }

    void show_winner() {
        cout << "\a¡Felicidades! ¡El player" << player<< " acaba de ganar!" << endl;
    }

    bool play_en_column(int col) {

        int y = 0;

        for (int i = 0; i < rows; i++) {

            if (board[col][i] == '.') {
                if (y < rows - 1) { y++; }
            }
            else {
                if (y > 0) { y--; }
                break;
            }
        }

        update_simbolito();
        board[col][y] = simbolito;

        return check_victory(col, y);
    }

    bool elegir_column() {

        cout << "¡Es el turno del player" << player<< "!\n\n";   // nombre del player
        int col = 0;
        bool hecho = false;

        do {
            cout << "column: ";
            cin >> col;

            if (col > 0 && col <= columns) {
                if (board[col - 1][0] == '.') {
                    hecho = true;
                    col--;
                }
            }

        } while (!hecho);

        return play_en_column(col);
    }

    bool check_column(int col) {

        int contador = 0;

        for (int fila = 0; fila < rows; fila++) {
            if (board[col][fila] == simbolito) {
                contador++;
                if (contador == 4) {
                    return true;
                }
            }
            else {
                contador = 0;
            }
        }
        return false;
    }

    bool check_fila(int fila) {

        int contador = 0;

        for (int col = 0; col < columns; col++) {
            if (board[col][fila] == simbolito) {
                contador++;
                if (contador == 4) {
                    return true;
                }
            }
            else {
                contador = 0;
            }
        }
        return false;
    }

    bool check_diagonal(int col, int fila) {
        
        int indice = 1, contador = 1;

        while ((col+indice) < columns && (fila+indice) < rows) {
            if (board[col + indice][fila + indice] == simbolito) {
                contador++; indice++;
            } else { break; }
        }

        indice = 1;
        while ((col - indice) >= 0 && (fila - indice) >= 0) {
            if (board[col - indice][fila - indice] == simbolito) {
                contador++; indice++;
            }
            else { break; }
        }

        if (contador >= 4) { return true; }
        else { contador = 1; }

        indice = 1;
        while ((col + indice) < columns && (fila - indice) >= 0) {
            if (board[col + indice][fila - indice] == simbolito) {
                contador++; indice++;
            }
            else { break; }
        }

        indice = 1;
        while ((col - indice) >= 0 && (fila + indice) < rows) {
            if (board[col - indice][fila + indice] == simbolito) {
                contador++; indice++;
            }
            else { break; }
        }

        if (contador >= 4) { return true; }
        else { return false; }
    }

    bool check_victory(int col, int fila) {

        return check_column(col) || check_fila(fila) || check_diagonal(col, fila);
    }

    bool play() {

        show_board();
        if (elegir_column()) {
            show_board();
            show_winner();
            return true;
        }
        else {
            next_player();
            return false;
        }
    }
};

Game initialize_board(int player) {

    char** board = new char*[columns];
    for (int i = 0; i < columns; i++) {
        board[i] = new char[rows];
    }

    Game Game(board, player);

    Game.lfill_board();

    return Game;
}

void begin_Game() {

    Game Game = initialize_board(1);   // parámetro: número del que comienza

    bool won = false; 

    while (!won) {

        if (Game.play()) {
            won = true;
        };
    }
}

int main() {
    
    begin_Game();
}
