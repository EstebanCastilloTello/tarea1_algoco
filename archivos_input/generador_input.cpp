#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>  // Para generar números aleatorios
#include <random>     // Para el generador de números aleatorios
#include <sstream>    // Para std::ostringstream

// Función para convertir un entero a una cadena
std::string intToString(int num) {
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

// Función para generar números aleatorios y guardar el dataset en un archivo de texto
void generarDataset(const std::string& nombreArchivo, int n) {
    std::vector<int> datos(n);

    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 generador(rd());
    std::uniform_int_distribution<int> distribucion(1, 1000000);

    // Llenar el vector con números aleatorios
    for (int i = 0; i < n; ++i) {
        datos[i] = distribucion(generador);
    }

    // Crear y abrir el archivo
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {  // Verificar si el archivo se abrió correctamente
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    // Escribir el tamaño del dataset como la primera línea
    archivo << n << std::endl;
    
    // Escribir los números en el archivo
    for (int numero : datos) {
        archivo << numero << " ";
    }
    archivo << std::endl;

    archivo.close();
    std::cout << "Archivo " << nombreArchivo << " generado con éxito." << std::endl;
}

int main() {
    // Generar 10 datasets para tamaños entre 10^4 y 10^6
    int tamanos[] = {10000, 20000, 40000, 60000, 80000, 100000, 200000, 400000, 600000, 1000000};

    for (int i = 0; i < 10; ++i) {
        std::string nombreArchivo = "dataset_" + intToString(tamanos[i]) + ".txt";
        generarDataset(nombreArchivo, tamanos[i]);
    }

    return 0;
}
