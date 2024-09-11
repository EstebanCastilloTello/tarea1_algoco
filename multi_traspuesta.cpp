#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>  // Para medir el tiempo
#include <sstream>  // Para std::ostringstream
#include <cstdlib>  // Para EXIT_FAILURE
#include <iomanip>  // Para std::fixed y std::setprecision

using namespace std;

// Función para leer una matriz desde un archivo
vector<vector<int>> leerMatriz(ifstream& archivo, int& filas, int& columnas) {
    archivo >> filas >> columnas;
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            archivo >> matriz[i][j];
        }
    }
    
    return matriz;
}

// Función para transponer una matriz
vector<vector<int>> transponerMatriz(const vector<vector<int>>& matriz) {
    int filas = matriz.size();
    int columnas = matriz[0].size();
    vector<vector<int>> transpuesta(columnas, vector<int>(filas));
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            transpuesta[j][i] = matriz[i][j];
        }
    }
    
    return transpuesta;
}

// Función para multiplicar dos matrices
vector<vector<int>> mulMat(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2) {
    int R1 = mat1.size();
    int C1 = mat1[0].size();
    int R2 = mat2.size();
    int C2 = mat2[0].size();

    vector<vector<int>> rslt(R1, vector<int>(C2, 0));

    for (int i = 0; i < R1; ++i) {
        for (int j = 0; j < C2; ++j) {
            for (int k = 0; k < C1; ++k) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return rslt;
}

// Función principal
int main() {
    vector<int> dimensiones = {100, 200, 300, 400, 500};  // Tamaños de matrices

    // Crear 10 archivos y medir el tiempo de ejecución
    for (int numArchivo = 1; numArchivo <= 10; ++numArchivo) {
        ostringstream nombreArchivoStream1, nombreArchivoStream2;
        nombreArchivoStream1 << "archivos_input/matrices_" << numArchivo << ".txt";
        nombreArchivoStream2 << "archivos_input/matrices_" << numArchivo << ".txt";
        string nombreArchivo1 = nombreArchivoStream1.str();
        string nombreArchivo2 = nombreArchivoStream2.str();

        ifstream archivo1(nombreArchivo1);
        ifstream archivo2(nombreArchivo2);

        if (!archivo1.is_open()) {
            cerr << "No se pudo abrir el archivo " << nombreArchivo1 << endl;
            continue;
        }

        if (!archivo2.is_open()) {
            cerr << "No se pudo abrir el archivo " << nombreArchivo2 << endl;
            continue;
        }

        int filas1, columnas1, filas2, columnas2;
        auto mat1 = leerMatriz(archivo1, filas1, columnas1);
        auto mat2 = leerMatriz(archivo2, filas2, columnas2);

        archivo1.close();
        archivo2.close();

        // Transponer la segunda matriz
        auto mat2_transpuesta = transponerMatriz(mat2);

        // Verificar que las dimensiones sean compatibles para la multiplicación
        if (columnas1 != filas2) {
            cerr << "Las dimensiones de las matrices no son compatibles para la multiplicación en el archivo " 
                 << numArchivo << endl;
            continue;
        }

        clock_t start = clock();  // Empezar a medir el tiempo

        auto rslt = mulMat(mat1, mat2_transpuesta);

        clock_t end = clock();  // Terminar de medir el tiempo

        double duration = double(end - start) / CLOCKS_PER_SEC;  // Calcular duración en segundos

        // Imprimir el tiempo de ejecución con 5 decimales
        cout << fixed << setprecision(5);
        cout << "Tiempo de ejecución para el archivo " << numArchivo << ": " << duration << " segundos." << endl;
    }

    return 0;
}
