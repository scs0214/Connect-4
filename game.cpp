
#include <iostream>
#include <cstdlib> // Para la función rand
using namespace std;

const int filas = 6, columnas = 7;

class Juego {
private:
    char** cuadricula;
    int jugador;
    char caracter;

public:
    Juego();
    Juego(char** cuadricula, int jugador) { this->cuadricula = cuadricula; this->jugador = jugador; };
    Juego(char** cuadricula, int jugador, char caracter) { this->cuadricula = cuadricula; this->jugador = jugador; this->caracter = caracter; };
    
    void siguiente_jugador() {
        jugador *= -1;
    }

    void actualizar_caracter() {
        if (jugador == 1) {
            caracter = '#';
        }
        else {
            caracter = 'O';
        }
    }

    void llenar_cuadricula() {
        cuadricula = new char*[columnas];
        for (int i = 0; i < columnas; i++) {
            cuadricula[i] = new char[filas];
        }
        for (int i = 0; i < columnas; i++) {
            for (int j = 0; j < filas; j++) {
                cuadricula[i][j] = '.';
            }
        }
    }

    void mostrar_cuadricula() {
        system("cls");
        cout << "\n   1     2     3     4     5     6     7\n\n";

        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << "|  " << cuadricula[j][i] << "  ";
            }
            cout << "|" << endl;
        }
        cout << endl;
    }

    void mostrar_ganador() {
        cout << "\a¡Felicidades! ¡El jugador " << jugador << " acaba de ganar!" << endl;
    }

    bool jugar_en_columna(int col) {
        int y = 0;
        for (int i = 0; i < filas; i++) {
            if (cuadricula[col][i] == '.') {
                if (y < filas - 1) { y++; }
            }
            else {
                if (y > 0) { y--; }
                break;
            }
        }
        actualizar_caracter();
        cuadricula[col][y] = caracter;
        return revisar_victoria(col, y);
    }

    bool elegir_columna() {
        cout << "¡Es el turno del jugador " << jugador << "!\n\n";   // nombre del jugador
        int col = 0;
        bool hecho = false;
        do {
            cout << "Columna: ";
            if (jugador == 1) {
                col = elegir_movimiento(); // IA jugando
            } else {
                cin >> col; // Entrada del jugador humano
            }

            if (col > 0 && col <= columnas) {
                if (cuadricula[col - 1][0] == '.') {
                    hecho = true;
                    col--;
                }
            }
        } while (!hecho);
        return jugar_en_columna(col);
    }

    int elegir_movimiento() {
        // Estrategia de la IA:
        // Buscar líneas de tres fichas tanto propias como del enemigo en todas las direcciones.
        // Si encuentra una línea propia, intentará completarla.
        // Si encuentra una línea del enemigo, intentará bloquearla.
        for (int col = 0; col < columnas; col++) {
            for (int fila = 0; fila < filas; fila++) {
                if (cuadricula[col][fila] == '.') {
                    if (es_movimiento_ganador(col, fila, jugador)) {
                        return col;
                    }
                    if (es_movimiento_ganador(col, fila, -jugador)) {
                        return col;
                    }
                }
            }
        }
        // Si no encuentra una jugada estratégica, elige una columna aleatoria.
        return rand() % columnas + 1;
    }

    bool es_movimiento_ganador(int col, int fila, int jugador) {
        char temp = caracter;
        caracter = jugador == 1 ? '#' : 'O'; // Temporalmente asignamos el carácter del jugador para probar el movimiento
        bool resultado = buscar_linea_tres(col, fila, jugador);
        caracter = temp; // Restauramos el carácter original
        return resultado;
    }

    bool buscar_linea_tres(int col, int fila, int jugador) {
        // Definimos las ocho direcciones posibles
        int dir_filas[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
        int dir_columnas[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

        // Buscamos líneas de tres fichas en cada dirección
        for (int d = 0; d < 8; d++) {
            int contador = 0;
            int x = col;
            int y = fila;

            // Recorremos en la dirección d hasta encontrar una ficha diferente a la nuestra
            while (x >= 0 && x < columnas && y >= 0 && y < filas && cuadricula[x][y] == caracter) {
                x += dir_columnas[d];
                y += dir_filas[d];
                contador++;
                if (contador == 3) {
                    // Si encontramos una línea de tres, verificamos si el próximo movimiento es estratégico
                    x += dir_columnas[d];
                    y += dir_filas[d];
                    if (x >= 0 && x < columnas && y >= 0 && y < filas && cuadricula[x][y] == '.') {
                        return true;
                    }
                    break;
                }
            }
        }
        // Si no se encontró una línea de tres en ninguna dirección estratégica, retornamos false
        return false;
    }

    bool revisar_victoria(int col,

 int fila) {
        return revisar_col(col) || revisar_fila(fila) || revisar_diagonal(col, fila);
    }

    bool revisar_col(int col) {
        int contador = 0;
        for (int fila = 0; fila < filas; fila++) {
            if (cuadricula[col][fila] == caracter) {
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

    bool revisar_fila(int fila) {
        int contador = 0;
        for (int col = 0; col < columnas; col++) {
            if (cuadricula[col][fila] == caracter) {
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

    bool revisar_diagonal(int col, int fila) {
        // Implementación de revisión de diagonales
        int dir_filas[] = { -1, -1, 1, 1 };
        int dir_columnas[] = { -1, 1, 1, -1 };

        for (int d = 0; d < 4; d++) {
            int contador = 0;
            int x = col;
            int y = fila;

            while (x >= 0 && x < columnas && y >= 0 && y < filas && cuadricula[x][y] == caracter) {
                x += dir_columnas[d];
                y += dir_filas[d];
                contador++;
                if (contador == 3) {
                    // Si encontramos una línea de tres, verificamos si el próximo movimiento es estratégico
                    x += dir_columnas[d];
                    y += dir_filas[d];
                    if (x >= 0 && x < columnas && y >= 0 && y < filas && cuadricula[x][y] == '.') {
                        return true;
                    }
                    break;
                }
            }
        }
        return false;
    }

    bool jugar() {
        mostrar_cuadricula();
        if (elegir_columna()) {
            mostrar_cuadricula();
            mostrar_ganador();
            return true;
        }
        else {
            siguiente_jugador();
            return false;
        }
    }
};

Juego inicializar_cuadricula(int jugador) {
    char** cuadricula = new char*[columnas];
    for (int i = 0; i < columnas; i++) {
        cuadricula[i] = new char[filas];
    }
    Juego juego(cuadricula, jugador);
    juego.llenar_cuadricula();
    return juego;
}

void comenzar_juego() {
    Juego juego = inicializar_cuadricula(1);   // parámetro: número del que comienza
    bool ganado = false; 
    while (!ganado) {
        if (juego.jugar()) {
            ganado = true;
        };
    }
}

int main() {
    comenzar_juego();
}
