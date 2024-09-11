#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>  // Para medir el tiempo
#include <sstream>  // Para std::ostringstream
#include <cstdlib>  // Para EXIT_FAILURE

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
    vector<int> dimensiones = {50, 100, 150, 200};  // Tamaños de matrices
    
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

        // Verificar que las dimensiones sean compatibles para la multiplicación
        if (columnas1 != filas2) {
            cerr << "Las dimensiones de las matrices no son compatibles para la multiplicación en el archivo " 
                 << numArchivo << endl;
            continue;
        }

        clock_t start = clock();  // Empezar a medir el tiempo

        auto rslt = mulMat(mat1, mat2);

        clock_t end = clock();  // Terminar de medir el tiempo

        double duration = double(end - start) / CLOCKS_PER_SEC;  // Calcular duración en segundos

        // Imprimir el tiempo de ejecución
        cout << "Tiempo de ejecución para el archivo " << numArchivo << ": " << duration << " segundos." << endl;
    }

    return 0;
}


//https://www.geeksforgeeks.org/cpp-matrix-multiplication/