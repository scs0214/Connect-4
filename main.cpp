// Code created by: Samir Caro C31666 - Roy Urbina C37971

#include <iostream>
#include <cstdlib> // This library is necessary for the malloc() function to work
using namespace std;

bool programLoop = true;
bool gameLoop = true;
int gameOption = 0;
int columnInput = 0;
int rowsI = 6;
int columnsI = 7;
int rowAmount, columnAmount, currentPlayer, winner;
bool player2AI; // Boolean that determines if player 2 was the AI (used when printing the winner message if necessary)

void fillBoard(char** matrix, int R, int C) { // Receives the game board and the amount of rows and columns available, to fill empty spaces in the array (so that these spaces are empty for the program)
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (matrix[i][j] != '-' && matrix[i][j] != 'O' && matrix[i][j] != 'X') {
                matrix[i][j] = '-';
            }
        }
    }
}

void initializeGame(char** matrix) { // Sets the row and column amounts (which will be variables), as well as setting the game loop, current player and filling the game board
    rowAmount = rowsI;
    columnAmount = columnsI;
    gameLoop = true;
    currentPlayer = 1;
    winner = 0;
    fillBoard(matrix, rowAmount, columnAmount);
}

void showBoard(char** matrix, int R, int C) { // Prints the game board
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("| %c ", matrix[i][j]);
        }
        printf("| \n");
    }
}

char** increaseBoardSize (char** originalMatrix, int rowsOld, int columnsOld) { // Receives the old board, row and column values to assign new values (adds 7 to both rows and columns and creates an auxiliar matrix); then, it frees the memory used by the original matrix to then return the auxiliar matrix (which will be the new board)
    int newRows = rowsOld + 7;
    int newColumns = columnsOld + 7;

    char** auxMatrix = (char**)malloc(newRows * sizeof(char*));
    for (int i = 0; i < newRows; ++i) {
        auxMatrix[i] = (char*)malloc(newColumns * sizeof(char));
    }

    for (int i = 0; i < newRows; ++i) {
        for (int j = 0; j < newColumns; ++j) {
            auxMatrix[i][j] = '-';
        }
    }

    for (int i = 0; i < rowsOld; ++i) {
        for (int j = 0; j < columnsOld; ++j) {
            auxMatrix[i+7][j] = originalMatrix[i][j];
        }
    }

    for (int i = 0; i < rowsOld; ++i) {
        free(originalMatrix[i]);
    }
    free (originalMatrix);

    return auxMatrix;
}

char returnSymbol (int player) { // Receives which player does a move, to place the correct symbol and switch to the other player
    if (player == 1) {
        currentPlayer = 2;
        return 'O';
    }
    else {
        currentPlayer = 1;
        return 'X';
    }
}

int whoWinner(char** matrix) { // Receives the board to go through it and check if there are 4 symbols of the same type in a row, resets values between each condition
    char wSymbol = '-';
    int cont, row, column;
    bool continueProcess; // Avoid infinite loops
    bool winnerPlayer = false; // Boolean which makes that if a winner is detected, the rest of the conditions will be ignored
    
    for (int i = 0; i < rowAmount; ++i) { // Checks vertically
        for (int j = 0; j < columnAmount; ++j) {
            char symbol = matrix[i][j];
            if (symbol != '-' && !winnerPlayer) {
                cont = 0;
                row = i;
                continueProcess = true;
                if (row+3 <= rowAmount-1 && !winnerPlayer) {
                    while (row <= rowAmount-1 && continueProcess) {
                        if (matrix[row][j] == symbol) {
                            cont++;
                            row++;
                        }
                        else {
                            continueProcess = false;
                        }

                        if (cont == 4) {
                            winnerPlayer = true;
                            continueProcess = false;
                            wSymbol = symbol;
                        }
                    }
                }
                cont = 0;
                row = i;
                column = j;
                continueProcess = true;
                if (row+3 <= rowAmount-1 && column-3 >= 0 && !winnerPlayer) { // Checks diagonally left down
                    while (row <= rowAmount-1 && column >= 0 && continueProcess) {
                        if (matrix[row][column] == symbol) {
                            cont++;
                            row++;
                            column--;
                        }
                        else {
                            continueProcess = false;
                        }

                        if (cont == 4) {
                            winnerPlayer = true;
                            continueProcess = false;
                            wSymbol = symbol;
                        }
                    }
                }
                cont = 0;
                row = i;
                column = j;
                continueProcess = true;
                if (row+3 <= rowAmount-1 && column+3 <= columnAmount-1 && !winnerPlayer) { // Checks diagonally right down
                    while (row <= rowAmount-1 && column <= columnAmount-1 && continueProcess) {
                        if (matrix[row][column] == symbol) {
                            cont++;
                            row++;
                            column++;
                        }
                        else {
                            continueProcess = false;
                        }

                        if (cont == 4) {
                            winnerPlayer = true;
                            continueProcess = false;
                            wSymbol = symbol;
                        }
                    }
                }
                cont = 0;
                column = j;
                continueProcess = true;
                if (column+3 <= columnAmount-1 && !winnerPlayer) { // Checks horizontally
                    while (column <= columnAmount-1 && continueProcess) {
                        if (matrix[i][column] == symbol) {
                            cont++;
                            column++;
                        }
                        else {
                            continueProcess = false;
                        }
                        
                        if (cont == 4) {
                            winnerPlayer = true;
                            continueProcess = false;
                            wSymbol = symbol;
                        }
                    }
                }
            }
        }
    }

    if (winnerPlayer) { // Checks if there was a winner and returns the player number based on the symbol
        if (wSymbol == 'O') {
            return 1;
        }
        else if (wSymbol == 'X') {
            return 2;
        }
        else {
            return -1;
        }
    }
    else {
        return 0;
    }
}

void declareWinner(char** matrix, int winnerP) { // Prints different messages depending on who won
    if (winnerP = 1) {
        printf("¡Felicidades Jugador 1, has ganado el juego! \n");
    }
    else if (winnerP = 2) {
        printf("¡Felicidades Jugador 2, has ganado el juego! \n");
    }
    else if (winnerP = 2 && player2AI) {
        printf("¡Qué lástima %s, la IA ha ganado el juego! \n");
    }
    else if (winnerP = -1) {
        printf("ERROR \n");
    }
    showBoard(matrix, rowAmount, columnAmount);
    gameLoop = false;
}

int main() {
    printf("CONNECT 4 \n");
    while(programLoop) {
        char** board = (char**)malloc(rowsI * sizeof(char*)); // Creates the game board (as a list of lists, which lets it be a dynamic matrix)
        for (int i = 0; i < rowsI; ++i) {
            board[i] = (char*)malloc(columnsI * sizeof(char));
        }
        initializeGame(board);
        printf("1- 1 Jugador \n");
        printf("2- Multijugador \n");
        printf("0- Salir \n");
        printf("Digite el numero de la opcion que gusta ejecutar: ");
        cin >> gameOption;

        if(gameOption == 1) { // Single Player Mode
            player2AI = true;
            while(gameLoop) {
                bool insertToken = false;
                showBoard(board, rowAmount, columnAmount);
                if (currentPlayer == 1) {
                    printf("Digite el numero de la columna en la que quiere depositar su ficha: ");
                    cin >> columnInput;
                }
                else {
                    // AI plays (needs to set columnInput)
                }

                if (board[0][columnInput] != 0 || columnInput > columnAmount-1) { // If structure that checks if the game board's size needs to be increased
                    while (columnInput > columnAmount-1) {
                        board = increaseBoardSize(board, rowAmount, columnAmount);
                        rowAmount = rowAmount + 7;
                        columnAmount = columnAmount + 7;
                    }
                }
                int rowInput = rowAmount - 1;
                while (!insertToken) { // While loop that reduces the value of the row to deposit the token in an empty space
                    if (board[rowInput][columnInput] == '-') {
                        board[rowInput][columnInput] = returnSymbol(currentPlayer);
                        insertToken = true; 
                    }
                    else {
                        rowInput--;
                    }
                }

                winner = whoWinner(board);
                if (winner != 0) {
                    declareWinner(board, winner);
                }
            }
        }
    
        if(gameOption == 2) { // Multiplayer Mode
            player2AI = false; 
            while(gameLoop) {
                bool insertToken = false;
                showBoard(board, rowAmount, columnAmount);
                printf("Jugador %i, digite el numero de la columna en la que quiere depositar su ficha: ", currentPlayer);
                cin >> columnInput;

                if (board[0][columnInput] != 0 || columnInput > columnAmount-1) { // If structure that checks if the game board's size needs to be increased
                    while (columnInput > columnAmount-1) {
                        board = increaseBoardSize(board, rowAmount, columnAmount);
                        rowAmount = rowAmount + 7;
                        columnAmount = columnAmount + 7;
                    }
                }
                int rowInput = rowAmount - 1;
                while (!insertToken) { // While loop that reduces the value of the row to deposit the token in an empty space
                    if (board[rowInput][columnInput] == '-') {
                        board[rowInput][columnInput] = returnSymbol(currentPlayer);
                        insertToken = true; 
                    }
                    else {
                        rowInput--;
                    }
                }

                winner = whoWinner(board);
                if (winner != 0) {
                    declareWinner(board, winner);
                }
            }
        }

        else if (gameOption == 0) { // Exit option
            for (int i = 0; i < rowAmount; ++i) {
                free(board[i]);
            }
            free (board);
            printf("Hasta luego! \n");
            programLoop = false;
        }

        else { // User types a non-existent option
            printf("El número digitado no es válido. \n");
        }
    } 

    return 0;
}