#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>  // Para medir el tiempo
#include <iomanip> // Para la salida de tiempo
#include <sstream> // Para ostringstream

using namespace std;
using namespace std::chrono;

typedef vector<vector<int>> Matrix;

// Función para multiplicar dos matrices usando Strassen
Matrix strassen(const Matrix& A, const Matrix& B) {
    int n = A.size();
    
    if (n == 1) {
        Matrix C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    Matrix A11(newSize, vector<int>(newSize));
    Matrix A12(newSize, vector<int>(newSize));
    Matrix A21(newSize, vector<int>(newSize));
    Matrix A22(newSize, vector<int>(newSize));
    Matrix B11(newSize, vector<int>(newSize));
    Matrix B12(newSize, vector<int>(newSize));
    Matrix B21(newSize, vector<int>(newSize));
    Matrix B22(newSize, vector<int>(newSize));
    Matrix C11(newSize, vector<int>(newSize));
    Matrix C12(newSize, vector<int>(newSize));
    Matrix C21(newSize, vector<int>(newSize));
    Matrix C22(newSize, vector<int>(newSize));
    Matrix M1(newSize, vector<int>(newSize));
    Matrix M2(newSize, vector<int>(newSize));
    Matrix M3(newSize, vector<int>(newSize));
    Matrix M4(newSize, vector<int>(newSize));
    Matrix M5(newSize, vector<int>(newSize));
    Matrix M6(newSize, vector<int>(newSize));
    Matrix M7(newSize, vector<int>(newSize));

    // Dividir matrices A y B en submatrices
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular M1 a M7
    Matrix temp1(newSize, vector<int>(newSize));
    Matrix temp2(newSize, vector<int>(newSize));

    // M1 = (A11 + A22) * (B11 + B22)
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            temp1[i][j] = A11[i][j] + A22[i][j];
            temp2[i][j] = B11[i][j] + B22[i][j];
        }
    }
    M1 = strassen(temp1, temp2);

    // M2 = (A21 + A22) * B11
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            temp1[i][j] = A21[i][j] + A22[i][j];
        }
    }
    M2 = strassen(temp1, B11);

    // M3 = A11 * (B12 - B22)
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            temp2[i][j] = B12[i][j] - B22[i][j];
        }
    }
    M3 = strassen(A11, temp2);

    // M4 = A22 * (B21 - B11)
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            temp2[i][j] = B21[i][j] - B11[i][j];
        }
    }
    M4 = strassen(A22, temp2);

    // M5 = (A11 + A12) * B22
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            temp1[i][j] = A11[i][j] + A12[i][j];
        }
    }
    M5 = strassen(temp1, B22);

    // M6 = (A21 - A11) * (B11 + B12)
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            temp1[i][j] = A21[i][j] - A11[i][j];
            temp2[i][j] = B11[i][j] + B12[i][j];
        }
    }
    M6 = strassen(temp1, temp2);

    // M7 = (A12 - A22) * (B21 + B22)
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            temp1[i][j] = A12[i][j] - A22[i][j];
            temp2[i][j] = B21[i][j] + B22[i][j];
        }
    }
    M7 = strassen(temp1, temp2);

    // Calcular C11, C12, C21, C22
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + newSize] = M3[i][j] + M5[i][j];
            C[i + newSize][j] = M2[i][j] + M4[i][j];
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    return C;
}

// Función para leer una matriz desde un archivo
Matrix leerMatrizDesdeArchivo(const string& nombreArchivo, int& filas, int& columnas) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        exit(EXIT_FAILURE);
    }

    archivo >> filas >> columnas;
    Matrix matriz(filas, vector<int>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            archivo >> matriz[i][j];
        }
    }
    archivo.close();
    return matriz;
}

// Función principal
int main() {
    for (int numArchivo = 1; numArchivo <= 10; ++numArchivo) {
        ostringstream nombreArchivoStream;
        nombreArchivoStream << "archivos_input/matrices_" << numArchivo << ".txt";
        string nombreArchivo = nombreArchivoStream.str();

        int filas1, columnas1, filas2, columnas2;
        Matrix A = leerMatrizDesdeArchivo(nombreArchivo, filas1, columnas1);
        Matrix B = leerMatrizDesdeArchivo(nombreArchivo, filas2, columnas2);

        if (columnas1 != filas2) {
            cerr << "Las dimensiones de las matrices no son válidas para la multiplicación." << endl;
            continue;
        }

        // Medir tiempo de ejecución
        auto inicio = high_resolution_clock::now();
        Matrix C = strassen(A, B);
        auto fin = high_resolution_clock::now();
        auto duracion = duration_cast<duration<double>>(fin - inicio);

        // Mostrar el tiempo de ejecución con 5 decimales
        cout << "Tiempo de ejecución para el archivo " << nombreArchivo << ": "
             << fixed << setprecision(5) << duracion.count() << " segundos" << endl;
    }

    return 0;
}
