#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <string>

using namespace std;

// Función para leer datos desde un archivo
vector<int> leerDatosDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<int> datos;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return datos;
    }

    int n;
    archivo >> n;  // Leer el tamaño del dataset

    int numero;
    while (archivo >> numero) {
        datos.push_back(numero);
    }

    archivo.close();
    return datos;
}

// Función para imprimir el tiempo en la consola
void imprimirTiempo(const string& archivo, double tiempo) {
    cout << "Tiempo para ordenar " << archivo << ": " << tiempo << " segundos." << endl;
}

int main() {
    vector<string> archivos = {
        "archivos_input/dataset_10000.txt",
        "archivos_input/dataset_20000.txt",
        "archivos_input/dataset_40000.txt",
        "archivos_input/dataset_60000.txt",
        "archivos_input/dataset_80000.txt",
        "archivos_input/dataset_100000.txt",
        "archivos_input/dataset_200000.txt",
        "archivos_input/dataset_400000.txt",
        "archivos_input/dataset_600000.txt",
        "archivos_input/dataset_1000000.txt"
    };

    for (const string& archivo : archivos) {
        // Leer datos desde el archivo
        vector<int> datos = leerDatosDesdeArchivo(archivo);
        if (datos.empty()) continue;

        // Iniciar tiempo
        auto inicio = chrono::high_resolution_clock::now();

        // Ordenar los datos usando std::sort
        sort(datos.begin(), datos.end());

        // Terminar tiempo
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = fin - inicio;

        // Mostrar tiempo en consola
        imprimirTiempo(archivo, duracion.count());
    }

    return 0;
}
