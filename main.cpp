#include <iostream>
#include <cstdlib>

using namespace std;

bool gameLoop = true;
bool sessionLoop = true;
int gameOption = 0;
int columnInput = 0;
int rowsI = 5;
int columnsI = 7;
int rowAmount, columnAmount;

void fillMatrix(int** matrix, int R, int C) {
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (matrix[r][c] != 0 && matrix[r][c] != 1) {
                matrix[r][c] = 0;
            }
        }
    }
}

void printMatrix(int** matrix, int R, int C) {
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            printf("%i ", matrix[r][c], "   ");
        }
        printf("\n");
    }
}

int** increaseMatrixSize (int** originalMatrix, int rowsOld, int columnsOld) {
    int newRows = rowsOld + 7;
    int newColumns = columnsOld + 7;

    int** auxMatrix = (int**)malloc(newRows * sizeof(int*));
    for (int i = 0; i < newRows; ++i) {
        auxMatrix[i] = (int*)malloc(newColumns * sizeof(int));
    }

    for (int i = 0; i < newRows; ++i) {
        for (int j = 0; j < newColumns; ++j) {
            auxMatrix[i][j] = 0;
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

int main() {
    printf("CONNECT 4 \n");
    while(gameLoop) {
        int** dynamicMatrix = (int**)malloc(rowsI * sizeof(int*));
        for (int i = 0; i < rowsI; ++i) {
            dynamicMatrix[i] = (int*)malloc(columnsI * sizeof(int));
            for (int j = 0; j < columnsI; ++j) {
                dynamicMatrix[i][j] = 0;
            }
        }
        printf("1- Jugar \n");
        printf("0- Salir \n");
        printf("Digite el numero de la opcion que gusta ejecutar: ");
        cin >> gameOption;
    
        if(gameOption == 1) {
            rowAmount = rowsI;
            columnAmount = columnsI;
            fillMatrix(dynamicMatrix, rowAmount, columnAmount);
            while(sessionLoop) {
                printMatrix(dynamicMatrix, rowAmount, columnAmount);
                bool insertToken = false;
                printf("Digite el numero de la columna en la que quiere depositar su ficha: ");
                cin >> columnInput;
                if (dynamicMatrix[0][columnInput] != 0 || columnInput > columnAmount-1) {
                    while (columnInput > columnAmount-1) {
                        dynamicMatrix = increaseMatrixSize(dynamicMatrix, rowAmount, columnAmount);
                        rowAmount = rowAmount + 7;
                        columnAmount = columnAmount + 7;
                    }
                }
                int rowInput = rowAmount - 1;
                while (!insertToken) {
                    if (dynamicMatrix[rowInput][columnInput] == 0) {
                        dynamicMatrix[rowInput][columnInput] = 1;
                        insertToken = true;
                    }
                    else {
                        rowInput--;
                    }
                }
            }
        }

        else if(gameOption == 0) {
            for (int i = 0; i < rowAmount; ++i) {
                free(dynamicMatrix[i]);
            }
            free (dynamicMatrix);
            printf("Hasta luego! \n");
            gameLoop = false;
        }

        else{
            printf("El número digitado no es válido. \n");
        }
    } 

    return 0;
}