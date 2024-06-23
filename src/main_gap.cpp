// main_gap.cpp
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
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

    int m = static_cast<int>(log2(largo_arreglo)); //Largo del array sample
    int b = largo_arreglo/m; //salto entre los elementos del array original que habra en el sample

    // Vector de los resultados(tiempos) de la busqueda
    vector<double> resultados_lineal;   
    vector<double> resultados_normal;   

    string path = crear_file_name();
    crear_archivo_txt(path);

    for (int i = 0; i < iteraciones; i++) {
        int* Arr_lineal = new int[largo_arreglo];
        int* Arr_normal = new int[largo_arreglo];
        int *gap_Arr_lineal = new int[largo_arreglo];
        int *gap_Arr_normal = new int[largo_arreglo];
        int *sample_ArrLineal = new int[m];
        int *sample_ArrNormal = new int[m];

        int epsilon = 10;       // Pasarlo como var de entorno
        crear_ArrLineal(largo_arreglo, Arr_lineal, epsilon);
        double mean = 25.0;     // Pasarlo como var de entorno
        double stddev = 5.0;    // Pasarlo como var de entorno
        crear_ArrNormal(largo_arreglo, Arr_normal, mean, stddev);

        //mostrar arrays lineal y normal
        cout<<"arrayLineal = ";
        print_Arr(largo_arreglo, Arr_lineal);

        cout<<endl;

        //cout<<"arrayNotmal = ";
        //print_Arr(largo_arreglo, Arr_normal);

        //arrays lineal y normal con el gap
        gap_Coding(Arr_lineal, gap_Arr_lineal, largo_arreglo);
        gap_Coding(Arr_normal, gap_Arr_normal, largo_arreglo);

        //array sample lineal
        sample_Array(Arr_lineal,sample_ArrLineal, m, b);
        cout<<"Array lineal sample = ";
        print_Arr(m,sample_ArrLineal);
        
        //array sample normal
        sample_Array(Arr_normal,sample_ArrNormal, m, b);
        


        //mostrar array gap lineal normal
        //cout<<"arrayLinealGap = ";
        //print_Arr(largo_arreglo, gap_Arr_lineal);

        //cout<<endl;
        
        //cout<<"arrayNormalGap";
        //print_Arr(largo_arreglo, gap_Arr_normal);
        

        // Busqueda arreglo lineal
        resultados_lineal.push_back(tiempo_binary_search(largo_arreglo, Arr_lineal, numero_buscado));

        // Busqueda arreglo normal
        resultados_normal.push_back(tiempo_binary_search(largo_arreglo, Arr_normal, numero_buscado));

        delete[] Arr_lineal;
        delete[] Arr_normal;
        delete[] gap_Arr_lineal;
        delete[] gap_Arr_normal;
    }

    escribir_resultados_csv(resultados_lineal,resultados_normal, path, largo_arreglo, numero_buscado);
    return 0;
}