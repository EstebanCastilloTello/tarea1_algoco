#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

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

// Función para fusionar dos subarreglos de vec
void merge(vector<int>& vec, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear vectores temporales
    vector<int> leftVec(n1), rightVec(n2);

    // Copiar datos a vectores temporales
    for (i = 0; i < n1; i++)
        leftVec[i] = vec[left + i];
    for (j = 0; j < n2; j++)
        rightVec[j] = vec[mid + 1 + j];

    // Fusionar los vectores temporales de vuelta en vec[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftVec[i] <= rightVec[j]) {
            vec[k] = leftVec[i];
            i++;
        } else {
            vec[k] = rightVec[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de leftVec[], si hay
    while (i < n1) {
        vec[k] = leftVec[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de rightVec[], si hay
    while (j < n2) {
        vec[k] = rightVec[j];
        j++;
        k++;
    }
}

// Función de Merge Sort
void mergeSort(vector<int>& vec, int left, int right) {
    if (left < right) {
        // Calcular el punto medio
        int mid = left + (right - left) / 2;

        // Ordenar las dos mitades
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        // Fusionar las mitades ordenadas
        merge(vec, left, mid, right);
    }
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

        // Ordenar los datos
        mergeSort(datos, 0, datos.size() - 1);

        // Terminar tiempo
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double> duracion = fin - inicio;

        // Mostrar tiempo en consola
        imprimirTiempo(archivo, duracion.count());
    }

    return 0;
}


//https://www.geeksforgeeks.org/cpp-program-for-merge-sort/