// main_normal.cpp
#include <iostream>
#include <chrono>
#include <iomanip>
#include "../include/funciones.h"

using namespace std;

// Main
int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Entrada debe ser ./binaryS largo_arreglo numero_buscado" << endl;
        exit(1);
    }
    srand(time(nullptr));  

    int largo_arreglo = atoi(argv[1]);
    int numero_buscado = atoi(argv[2]);

    int iteraciones = 1;  // Pasarlo como var de entorno

    // Vector de los resultados(tiempos) de la busqueda
    vector<double> resultados_lineal;   
    vector<double> resultados_normal;   

    string path = crear_file_name();
    crear_archivo_txt(path);

    for (int i = 0; i < iteraciones; i++) {
        int* Arr_lineal = new int[largo_arreglo];
        int* Arr_normal = new int[largo_arreglo];

        int epsilon = 10;       // Pasarlo como var de entorno
        crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);
        double mean = 25.0;     // Pasarlo como var de entorno
        double stddev = 5.0;    // Pasarlo como var de entorno
        crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);

        print_Arr(largo_arreglo,Arr_lineal);

        cout << endl;

        pair<int,int> intervalo = binary_Search_Intervalos(Arr_lineal,largo_arreglo,-1);

        cout << Arr_lineal[intervalo.first] << " " << Arr_lineal[intervalo.second] << endl;

        // Busqueda arreglo lineal
        resultados_lineal.push_back(tiempo_binary_search(largo_arreglo, Arr_lineal, numero_buscado));

        // Busqueda arreglo normal
        resultados_normal.push_back(tiempo_binary_search(largo_arreglo, Arr_normal, numero_buscado));

        delete[] Arr_lineal;
        delete[] Arr_normal;
    }

    escribir_resultados_csv(resultados_lineal,resultados_normal, path, largo_arreglo);
    return 0;
}
