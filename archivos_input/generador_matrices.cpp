#include <iostream>
#include <fstream>
#include <vector>    // Necesario para std::vector
#include <cstdlib>  // Para rand()
#include <ctime>    // Para srand(time(0))
#include <sstream>  // Para ostringstream

using namespace std;

void generarMatriz(int filas, int columnas, ofstream& archivo) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            archivo << rand() % 10 + 1 << " "; // Números aleatorios entre 1 y 10
        }
        archivo << endl;
    }
}

int main() {
    srand(time(0));  // Inicializar la semilla para generar números aleatorios

    // Crear 10 archivos con tamaños de matrices crecientes
    for (int numArchivo = 1; numArchivo <= 10; ++numArchivo) {
        ostringstream nombreArchivoStream;
        nombreArchivoStream << "matrices_" << numArchivo << ".txt";
        string nombreArchivo = nombreArchivoStream.str();

        ofstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
            continue;
        }

        // Calcular el tamaño de las matrices para cada archivo
        int tamaño = 100 + (numArchivo - 1) * 50;  // Tamaño de 100 a 500

        int filas1 = tamaño;
        int columnas1 = tamaño;
        int columnas2 = tamaño;

        // Escribir las dimensiones y matrices en el archivo
        archivo << filas1 << " " << columnas1 << endl;  // Dimensiones de la primera matriz
        generarMatriz(filas1, columnas1, archivo);      // Generar la primera matriz

        archivo << columnas1 << " " << columnas2 << endl;  // Dimensiones de la segunda matriz
        generarMatriz(columnas1, columnas2, archivo);      // Generar la segunda matriz

        archivo.close();
        cout << "Archivo " << nombreArchivo << " generado con éxito." << endl;
    }

    return 0;
}
